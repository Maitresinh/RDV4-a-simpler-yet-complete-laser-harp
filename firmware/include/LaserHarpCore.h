#pragma once
#include <stdint.h>

namespace laserharp {

constexpr uint8_t kBeamCount = 12;

enum class GateEvent : uint8_t { None = 0, NoteOn = 1, NoteOff = 2 };

inline uint8_t clampMidi(int note) {
  if (note < 0) return 0;
  if (note > 127) return 127;
  return static_cast<uint8_t>(note);
}

inline uint8_t noteForBeam(uint8_t beamIndex, uint8_t baseNote, int8_t octaveSemitones) {
  const uint8_t interval = beamIndex < kBeamCount ? beamIndex : 0;
  return clampMidi(static_cast<int>(baseNote) + interval + octaveSemitones);
}

class BeamGate {
 public:
  GateEvent update(int16_t signal, int16_t onThreshold, int16_t offThreshold,
                   uint8_t attackFrames, uint8_t releaseFrames) {
    if (!active_) {
      releaseCount_ = 0;
      if (signal >= onThreshold) {
        if (++attackCount_ >= attackFrames) {
          active_ = true;
          attackCount_ = 0;
          return GateEvent::NoteOn;
        }
      } else {
        attackCount_ = 0;
      }
    } else {
      attackCount_ = 0;
      if (signal <= offThreshold) {
        if (++releaseCount_ >= releaseFrames) {
          active_ = false;
          releaseCount_ = 0;
          return GateEvent::NoteOff;
        }
      } else {
        releaseCount_ = 0;
      }
    }
    return GateEvent::None;
  }

  bool active() const { return active_; }
  void reset() { active_ = false; attackCount_ = 0; releaseCount_ = 0; }

 private:
  bool active_ = false;
  uint8_t attackCount_ = 0;
  uint8_t releaseCount_ = 0;
};

class OctaveQuantizer4 {
 public:
  OctaveQuantizer4(const uint16_t boundaries[3], const int8_t offsets[4], uint16_t hysteresis)
      : boundaries_(boundaries), offsets_(offsets), hysteresis_(hysteresis) {}

  int8_t update(uint16_t distanceMm) {
    while (zone_ < 3 && distanceMm > static_cast<uint16_t>(boundaries_[zone_] + hysteresis_)) ++zone_;
    while (zone_ > 0 && distanceMm + hysteresis_ < boundaries_[zone_ - 1]) --zone_;
    return offsets_[zone_];
  }

  int8_t current() const { return offsets_[zone_]; }
  uint8_t zone() const { return zone_; }
  void resetToBase() { zone_ = 1; }

 private:
  const uint16_t* boundaries_;
  const int8_t* offsets_;
  uint16_t hysteresis_;
  uint8_t zone_ = 1;
};

inline uint16_t evenlySpacedPosition(uint8_t index, uint16_t minValue, uint16_t maxValue) {
  const uint32_t span = static_cast<uint32_t>(maxValue) - minValue;
  return static_cast<uint16_t>(minValue + (span * index) / (kBeamCount - 1U));
}

} // namespace laserharp
