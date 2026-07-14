#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "config.h"
#include "LaserHarpCore.h"

#if ENABLE_HEIGHT_SENSOR
#include <VL53L4CD.h>
#endif

using laserharp::BeamGate;
using laserharp::GateEvent;

namespace {

enum class RunState : uint8_t { SafeOff, Armed, Fault };

struct BeamRuntime {
  BeamGate gate;
  int16_t baseline = 0;
  int16_t lastDelta = 0;
  uint8_t activeNote = 0;
};

BeamRuntime beams[laserharp::kBeamCount];
RunState runState = RunState::SafeOff;
uint16_t warmupFramesRemaining = cfg::BASELINE_WARMUP_FRAMES;
uint32_t frameCounter = 0;
#if ENABLE_DIAGNOSTICS
uint32_t lastDiagnosticMs = 0;
#endif
int8_t currentOctaveSemitones = 0;
bool previousArmPressed = false;
uint32_t armChangeMs = 0;
SPISettings dacSpi(cfg::DAC_SPI_HZ, MSBFIRST, SPI_MODE0);

laserharp::OctaveQuantizer4 octaveQuantizer(
    cfg::HEIGHT_BOUNDARIES_MM,
    cfg::HEIGHT_OCTAVE_SEMITONES,
    cfg::HEIGHT_HYSTERESIS_MM);

#if ENABLE_HEIGHT_SENSOR
VL53L4CD heightSensor;
bool heightSensorAvailable = false;
uint32_t lastHeightValidMs = 0;
uint32_t lastHeightPollUs = 0;
#endif

inline void laserOff() {
  digitalWriteFast(cfg::PIN_LASER_TTL, cfg::LASER_ACTIVE_HIGH ? LOW : HIGH);
}

inline bool interlockClosed() {
  return digitalReadFast(cfg::PIN_INTERLOCK_MON) == HIGH;
}

inline void laserOn() {
  if (runState == RunState::Armed && interlockClosed()) {
    digitalWriteFast(cfg::PIN_LASER_TTL, cfg::LASER_ACTIVE_HIGH ? HIGH : LOW);
  }
}

void writeDac(uint8_t channel, uint16_t value) {
  if (value > 4095) value = 4095;
  const uint16_t channelBit = channel ? 0x8000U : 0x0000U;
  const uint16_t command = static_cast<uint16_t>(channelBit | 0x3000U | value);
  SPI.beginTransaction(dacSpi);
  digitalWriteFast(cfg::PIN_DAC_CS, LOW);
  SPI.transfer16(command);
  digitalWriteFast(cfg::PIN_DAC_CS, HIGH);
  SPI.endTransaction();
}

uint16_t readPhotoAverage(uint8_t samples) {
  uint32_t total = 0;
  for (uint8_t i = 0; i < samples; ++i) total += analogRead(cfg::PIN_PHOTO);
  return static_cast<uint16_t>(total / samples);
}

int16_t measureReflection() {
  laserOff();
  const uint16_t ambient = readPhotoAverage(cfg::ADC_SAMPLES_AMBIENT);
  laserOn();
  delayMicroseconds(cfg::LASER_RISE_US);
  const uint16_t lit = readPhotoAverage(cfg::ADC_SAMPLES_LIT);
  if (cfg::VISIBLE_DWELL_US) delayMicroseconds(cfg::VISIBLE_DWELL_US);
  laserOff();
  return static_cast<int16_t>(static_cast<int32_t>(lit) - static_cast<int32_t>(ambient));
}

void sendNoteOn(uint8_t note) {
  usbMIDI.sendNoteOn(note, cfg::MIDI_VELOCITY, cfg::MIDI_CHANNEL);
  usbMIDI.send_now();
}

void sendNoteOff(uint8_t note) {
  usbMIDI.sendNoteOff(note, 0, cfg::MIDI_CHANNEL);
  usbMIDI.send_now();
}

void allNotesOff() {
  for (auto &beam : beams) {
    if (beam.gate.active()) sendNoteOff(beam.activeNote);
    beam.gate.reset();
    beam.activeNote = 0;
  }
  usbMIDI.sendControlChange(123, 0, cfg::MIDI_CHANNEL);
  usbMIDI.send_now();
}

void resetDetection() {
  allNotesOff();
  for (auto &beam : beams) {
    beam.baseline = 0;
    beam.lastDelta = 0;
  }
  warmupFramesRemaining = cfg::BASELINE_WARMUP_FRAMES;
  frameCounter = 0;
}

void centerGalvos() {
  writeDac(0, cfg::DAC_CENTER);
  writeDac(1, cfg::DAC_Y_CENTER);
}

void enterSafeOff() {
  laserOff();
  centerGalvos();
  if (runState == RunState::Armed) allNotesOff();
  runState = RunState::SafeOff;
  digitalWriteFast(cfg::PIN_STATUS_LED, LOW);
}

void enterFault() {
  laserOff();
  centerGalvos();
  allNotesOff();
  runState = RunState::Fault;
  digitalWriteFast(cfg::PIN_STATUS_LED, HIGH);
}

bool heightReadyForArm() {
#if ENABLE_HEIGHT_SENSOR
  return !cfg::HEIGHT_SENSOR_REQUIRED || heightSensorAvailable;
#else
  return !cfg::HEIGHT_SENSOR_REQUIRED;
#endif
}

void armIfAllowed() {
  if (!interlockClosed() || !heightReadyForArm()) {
    enterFault();
    return;
  }
  resetDetection();
  runState = RunState::Armed;
  digitalWriteFast(cfg::PIN_STATUS_LED, HIGH);
}

void serviceArmButton() {
  const bool pressed = digitalReadFast(cfg::PIN_ARM) == LOW;
  const uint32_t now = millis();
  if (pressed != previousArmPressed && now - armChangeMs >= cfg::CONTROL_DEBOUNCE_MS) {
    armChangeMs = now;
    previousArmPressed = pressed;
    if (pressed) {
      if (runState == RunState::Armed) enterSafeOff();
      else armIfAllowed();
    }
  }
}

#if ENABLE_HEIGHT_SENSOR
void setupHeightSensor() {
  Wire.begin();
  Wire.setClock(400000);
  heightSensor.setBus(&Wire);
  heightSensor.setTimeout(0);
  heightSensorAvailable = heightSensor.init(true, false);
  if (heightSensorAvailable) {
    heightSensor.setRangeTiming(10, 0);
    heightSensor.startContinuous();
    lastHeightValidMs = millis();
  }
}

void serviceHeightSensor() {
  if (!heightSensorAvailable) return;
  const uint32_t nowUs = micros();
  if (static_cast<uint32_t>(nowUs - lastHeightPollUs) < cfg::HEIGHT_POLL_INTERVAL_US) return;
  lastHeightPollUs = nowUs;

  if (heightSensor.dataReady()) {
    const uint16_t distance = heightSensor.read(false);
    const bool valid = heightSensor.ranging_data.range_status == 0 &&
                       distance >= cfg::HEIGHT_MIN_MM && distance <= cfg::HEIGHT_MAX_MM;
    if (valid) {
      currentOctaveSemitones = octaveQuantizer.update(distance);
      lastHeightValidMs = millis();
    }
  }

  if (millis() - lastHeightValidMs > cfg::HEIGHT_TIMEOUT_MS) {
    octaveQuantizer.resetToBase();
    currentOctaveSemitones = 0;
    lastHeightValidMs = millis();
  }
}
#else
void setupHeightSensor() {}
void serviceHeightSensor() {}
#endif

void processBeam(uint8_t index) {
  const uint16_t position = laserharp::evenlySpacedPosition(index, cfg::DAC_MIN, cfg::DAC_MAX);
  laserOff();
  writeDac(0, position);
  delayMicroseconds(cfg::GALVO_SETTLE_US);

  const int16_t rawSignal = measureReflection();
  BeamRuntime &beam = beams[index];

  if (frameCounter == 0) {
    beam.baseline = rawSignal;
  } else if (warmupFramesRemaining > 0 || !beam.gate.active()) {
    const int16_t error = static_cast<int16_t>(rawSignal - beam.baseline);
    if (warmupFramesRemaining > 0) {
      beam.baseline = static_cast<int16_t>(beam.baseline + error / (1 << cfg::BASELINE_WARMUP_SHIFT));
    } else if (error < cfg::PER_BEAM_ON_DELTA[index]) {
      beam.baseline = static_cast<int16_t>(beam.baseline + error / (1 << cfg::BASELINE_EMA_SHIFT));
    }
  }

  const int16_t delta = static_cast<int16_t>(rawSignal - beam.baseline);
  beam.lastDelta = delta;
  if (warmupFramesRemaining > 0) return;

  const GateEvent event = beam.gate.update(
      delta,
      cfg::PER_BEAM_ON_DELTA[index],
      cfg::PER_BEAM_OFF_DELTA[index],
      cfg::ATTACK_CONFIRM_FRAMES,
      cfg::RELEASE_CONFIRM_FRAMES);

  if (event == GateEvent::NoteOn) {
    beam.activeNote = laserharp::noteForBeam(index, cfg::BASE_NOTE, currentOctaveSemitones);
    sendNoteOn(beam.activeNote);
  } else if (event == GateEvent::NoteOff) {
    sendNoteOff(beam.activeNote);
    beam.activeNote = 0;
  }
}

void scanFrame() {
  for (uint8_t i = 0; i < laserharp::kBeamCount; ++i) {
    if (!interlockClosed()) {
      enterFault();
      return;
    }
    processBeam(i);
  }
  ++frameCounter;
  if (warmupFramesRemaining > 0) --warmupFramesRemaining;
}

void serviceDiagnostics() {
#if ENABLE_DIAGNOSTICS
  const uint32_t now = millis();
  if (now - lastDiagnosticMs < cfg::DIAGNOSTIC_INTERVAL_MS) return;
  lastDiagnosticMs = now;
  if (Serial && Serial.availableForWrite() > 96) {
    Serial.printf("state=%u octave=%d frames=%lu warmup=%u\n",
                  static_cast<unsigned>(runState),
                  currentOctaveSemitones,
                  static_cast<unsigned long>(frameCounter),
                  warmupFramesRemaining);
  }
#endif
}

} // namespace

void setup() {
  pinMode(cfg::PIN_ARM, INPUT_PULLUP);
  pinMode(cfg::PIN_INTERLOCK_MON, INPUT_PULLDOWN);
  pinMode(cfg::PIN_LASER_TTL, OUTPUT);
  pinMode(cfg::PIN_STATUS_LED, OUTPUT);
  pinMode(cfg::PIN_DAC_CS, OUTPUT);

  laserOff();
  digitalWriteFast(cfg::PIN_STATUS_LED, LOW);
  digitalWriteFast(cfg::PIN_DAC_CS, HIGH);

  analogReadResolution(12);
  analogReadAveraging(1);
  SPI.begin();
  centerGalvos();

  Serial.begin(115200);
  setupHeightSensor();

  if (!interlockClosed() || !heightReadyForArm()) enterFault();
  else enterSafeOff();
}

void loop() {
  while (usbMIDI.read()) {}
  serviceArmButton();
  if (!interlockClosed() && runState != RunState::Fault) enterFault();
  if (runState == RunState::Armed) scanFrame();
  else laserOff();
  serviceHeightSensor();
  serviceDiagnostics();
}
