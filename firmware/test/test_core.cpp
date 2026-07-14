#include <cassert>
#include <iostream>
#include "../include/LaserHarpCore.h"

using namespace laserharp;

static void testChromaticNotes() {
  assert(kBeamCount == 12);
  assert(noteForBeam(0, 60, -12) == 48);
  assert(noteForBeam(11, 60, -12) == 59);
  assert(noteForBeam(0, 60, 0) == 60);
  assert(noteForBeam(11, 60, 0) == 71);
  assert(noteForBeam(0, 60, 24) == 84);
  assert(noteForBeam(11, 60, 24) == 95);
}

static void testPositions() {
  assert(evenlySpacedPosition(0, 1000, 2000) == 1000);
  assert(evenlySpacedPosition(11, 1000, 2000) == 2000);
  assert(evenlySpacedPosition(5, 1000, 2000) < evenlySpacedPosition(6, 1000, 2000));
}

static void testGate() {
  BeamGate gate;
  assert(gate.update(90, 80, 48, 1, 2) == GateEvent::NoteOn);
  assert(gate.active());
  assert(gate.update(40, 80, 48, 1, 2) == GateEvent::None);
  assert(gate.update(40, 80, 48, 1, 2) == GateEvent::NoteOff);
  assert(!gate.active());
}

static void testOctaves() {
  const uint16_t boundaries[3] = {280, 520, 780};
  const int8_t offsets[4] = {-12, 0, 12, 24};
  OctaveQuantizer4 q(boundaries, offsets, 35);
  assert(q.current() == 0);
  assert(q.update(540) == 0);
  assert(q.update(560) == 12);
  assert(q.update(500) == 12);
  assert(q.update(470) == 0);
  assert(q.update(220) == -12);
  assert(q.update(850) == 24);
}

int main() {
  testChromaticNotes();
  testPositions();
  testGate();
  testOctaves();
  std::cout << "All core tests passed\n";
  return 0;
}
