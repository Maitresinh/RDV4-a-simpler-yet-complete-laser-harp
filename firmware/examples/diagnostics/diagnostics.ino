#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <VL53L4CD.h>

// Choisir un seul mode puis téléverser.
// 0: USB MIDI, 1: DAC, 2: VL53L4CD, 3: OPT101 + LED, 4: petit balayage galvo sans laser
#define TEST_MODE 0

constexpr uint8_t BUTTON_PIN = 2;
constexpr uint8_t LIGHT_PIN = 6;
constexpr uint8_t PHOTO_PIN = A1;
constexpr uint8_t DAC_CS = 10;
SPISettings dacSpi(20000000, MSBFIRST, SPI_MODE0);
VL53L4CD tof;

void writeDacA(uint16_t value) {
  value = min<uint16_t>(value, 4095);
  SPI.beginTransaction(dacSpi);
  digitalWriteFast(DAC_CS, LOW);
  SPI.transfer16(0x3000U | value);
  digitalWriteFast(DAC_CS, HIGH);
  SPI.endTransaction();
}

uint16_t averageRead(uint8_t count) {
  uint32_t sum = 0;
  for (uint8_t i = 0; i < count; ++i) sum += analogRead(PHOTO_PIN);
  return sum / count;
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(DAC_CS, OUTPUT);
  digitalWriteFast(LIGHT_PIN, LOW);
  digitalWriteFast(DAC_CS, HIGH);
  analogReadResolution(12);
  analogReadAveraging(1);
  SPI.begin();

#if TEST_MODE == 2
  Wire.begin();
  Wire.setClock(400000);
  tof.setBus(&Wire);
  tof.setTimeout(100);
  if (!tof.init(true, false)) {
    Serial.println("VL53L4CD absent ou câblage incorrect");
    while (true) delay(1000);
  }
  tof.setRangeTiming(10, 0);
  tof.startContinuous();
#endif
}

void loop() {
#if TEST_MODE == 0
  static bool previous = false;
  const bool pressed = digitalRead(BUTTON_PIN) == LOW;
  if (pressed != previous) {
    delay(20);
    if (pressed == (digitalRead(BUTTON_PIN) == LOW)) {
      previous = pressed;
      if (pressed) usbMIDI.sendNoteOn(60, 100, 1);
      else usbMIDI.sendNoteOff(60, 0, 1);
      usbMIDI.send_now();
    }
  }
  while (usbMIDI.read()) {}

#elif TEST_MODE == 1
  const uint16_t values[] = {1800, 2048, 2300};
  for (uint16_t value : values) {
    writeDacA(value);
    Serial.printf("DAC=%u Vout≈%.3f V\n", value, value * 2.048f / 4096.0f);
    delay(2000);
  }

#elif TEST_MODE == 2
  if (tof.dataReady()) {
    const uint16_t mm = tof.read(false);
    Serial.printf("distance=%u mm status=%u\n", mm, tof.ranging_data.range_status);
  }

#elif TEST_MODE == 3
  digitalWriteFast(LIGHT_PIN, LOW);
  delayMicroseconds(50);
  const uint16_t ambient = averageRead(8);
  digitalWriteFast(LIGHT_PIN, HIGH);
  delayMicroseconds(100);
  const uint16_t lit = averageRead(8);
  digitalWriteFast(LIGHT_PIN, LOW);
  Serial.printf("ambient=%u lit=%u delta=%ld\n", ambient, lit, (long)lit - ambient);
  delay(100);

#elif TEST_MODE == 4
  constexpr uint16_t center = 2048;
  constexpr uint16_t halfSpan = 80;
  for (uint8_t i = 0; i < 12; ++i) {
    writeDacA(center - halfSpan + (2U * halfSpan * i) / 11U);
    delay(20);
  }
  for (int i = 10; i >= 1; --i) {
    writeDacA(center - halfSpan + (2U * halfSpan * i) / 11U);
    delay(20);
  }
#endif
}
