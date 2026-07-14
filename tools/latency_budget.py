#!/usr/bin/env python3
BEAMS = 12
GALVO_SETTLE_US = 90
LASER_RISE_US = 10
VISIBLE_DWELL_US = 22
ADC_READS = 4
ADC_US_ESTIMATE = 3
SPI_AND_CODE_US = 8
slot = GALVO_SETTLE_US + LASER_RISE_US + VISIBLE_DWELL_US + ADC_READS * ADC_US_ESTIMATE + SPI_AND_CODE_US
frame = slot * BEAMS
print(f"slot estimate: {slot} us")
print(f"frame estimate: {frame} us ({frame/1000:.3f} ms)")
print(f"scan rate: {1_000_000/frame:.1f} Hz")
