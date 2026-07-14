EESchema Schematic File Version 4
LIBS:power
LIBS:device
LIBS:switch
LIBS:Connector_Generic
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
Sheet 1 1
Title "RDV4 Laser Harp - Module Wiring"
Date "2026-07-14"
Rev "1.0"
Comp "Maitresinh / RDV4"
Comment1 "KiCad legacy schematic; KiCad 6-9 imports and converts it"
Comment2 "No custom PCB: modules, terminals and board wiring"
Comment3 "Confirm galvo interface pinout before connection"
Comment4 "Laser <= 1 mW for prototype"
$EndDescr
Text Notes 700 650 0    60   ~ 12
LOGIC / MIDI / SENSORS
Text Notes 6500 650 0    60   ~ 12
LASER SAFETY AND GALVO
$Comp
L Connector_Generic:Conn_01x14 J1
U 1 1 00000001
P 1500 2200
F 0 "J1" H 1680 2320 50  0000 C CNN
F 1 "TEENSY_4.0" H 1750 2080 50  0000 C CNN
	1    1500 2200
	1 0 0 -1
$EndComp
Wire Wire Line
	1600 1550 2200 1550
Text Label 2200 1550 0    50   ~ 0
3V3
Wire Wire Line
	1600 1650 2200 1650
Text Label 2200 1650 0    50   ~ 0
GND_LOGIC
Wire Wire Line
	1600 1750 2200 1750
Text Label 2200 1750 0    50   ~ 0
ARM_PIN2
Wire Wire Line
	1600 1850 2200 1850
Text Label 2200 1850 0    50   ~ 0
INTERLOCK_MON_PIN3
Wire Wire Line
	1600 1950 2200 1950
Text Label 2200 1950 0    50   ~ 0
LASER_TTL_PIN6
Wire Wire Line
	1600 2050 2200 2050
Text Label 2200 2050 0    50   ~ 0
STATUS_LED_PIN7
Wire Wire Line
	1600 2150 2200 2150
Text Label 2200 2150 0    50   ~ 0
DAC_CS_PIN10
Wire Wire Line
	1600 2250 2200 2250
Text Label 2200 2250 0    50   ~ 0
SPI_MOSI_PIN11
Wire Wire Line
	1600 2350 2200 2350
Text Label 2200 2350 0    50   ~ 0
SPI_SCK_PIN13
Wire Wire Line
	1600 2450 2200 2450
Text Label 2200 2450 0    50   ~ 0
PHOTO_A1
Wire Wire Line
	1600 2550 2200 2550
Text Label 2200 2550 0    50   ~ 0
I2C_SDA_PIN18
Wire Wire Line
	1600 2650 2200 2650
Text Label 2200 2650 0    50   ~ 0
I2C_SCL_PIN19
Wire Wire Line
	1600 2750 2200 2750
Text Label 2200 2750 0    50   ~ 0
VIN_USB_5V
Wire Wire Line
	1600 2850 2200 2850
Text Label 2200 2850 0    50   ~ 0
USB_MIDI
$Comp
L Connector_Generic:Conn_01x08 J2
U 1 1 00000002
P 3300 2000
F 0 "J2" H 3480 2120 50  0000 C CNN
F 1 "MCP4822_MODULE" H 3550 1880 50  0000 C CNN
	1    3300 2000
	1 0 0 -1
$EndComp
Wire Wire Line
	3400 1650 4000 1650
Text Label 4000 1650 0    50   ~ 0
3V3
Wire Wire Line
	3400 1750 4000 1750
Text Label 4000 1750 0    50   ~ 0
GND_LOGIC
Wire Wire Line
	3400 1850 4000 1850
Text Label 4000 1850 0    50   ~ 0
DAC_CS_PIN10
Wire Wire Line
	3400 1950 4000 1950
Text Label 4000 1950 0    50   ~ 0
SPI_MOSI_PIN11
Wire Wire Line
	3400 2050 4000 2050
Text Label 4000 2050 0    50   ~ 0
SPI_SCK_PIN13
Wire Wire Line
	3400 2150 4000 2150
Text Label 4000 2150 0    50   ~ 0
GND_LOGIC
Wire Wire Line
	3400 2250 4000 2250
Text Label 4000 2250 0    50   ~ 0
DAC_X_0_2V048
Wire Wire Line
	3400 2350 4000 2350
Text Label 4000 2350 0    50   ~ 0
DAC_Y_0_2V048
Text Notes 3150 2550 0    60   ~ 12
J2 pin 6 = LDAC -> GND\nVOUTA = X, VOUTB = Y neutral
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 00000003
P 1500 3800
F 0 "J3" H 1680 3920 50  0000 C CNN
F 1 "OPT101_MODULE" H 1750 3680 50  0000 C CNN
	1    1500 3800
	1 0 0 -1
$EndComp
Wire Wire Line
	1600 3700 2200 3700
Text Label 2200 3700 0    50   ~ 0
3V3_OR_MODULE_VCC
Wire Wire Line
	1600 3800 2200 3800
Text Label 2200 3800 0    50   ~ 0
GND_LOGIC
Wire Wire Line
	1600 3900 2200 3900
Text Label 2200 3900 0    50   ~ 0
PHOTO_A1
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 00000004
P 3300 3800
F 0 "J4" H 3480 3920 50  0000 C CNN
F 1 "VL53L4CD_MODULE" H 3550 3680 50  0000 C CNN
	1    3300 3800
	1 0 0 -1
$EndComp
Wire Wire Line
	3400 3650 4000 3650
Text Label 4000 3650 0    50   ~ 0
3V3
Wire Wire Line
	3400 3750 4000 3750
Text Label 4000 3750 0    50   ~ 0
GND_LOGIC
Wire Wire Line
	3400 3850 4000 3850
Text Label 4000 3850 0    50   ~ 0
I2C_SDA_PIN18
Wire Wire Line
	3400 3950 4000 3950
Text Label 4000 3950 0    50   ~ 0
I2C_SCL_PIN19
$Comp
L Switch:SW_Push SW3
U 1 1 00000005
P 1200 5000
F 0 "SW3" H 1380 5120 50  0000 C CNN
F 1 "ARM" H 1450 4880 50  0000 C CNN
	1    1200 5000
	1 0 0 -1
$EndComp
Wire Wire Line
	1300 5000 1900 5000
Text Label 1900 5000 0    50   ~ 0
ARM_PIN2
Wire Wire Line
	1100 5000 800 5000
Text Label 800 5000 0    50   ~ 0
GND_LOGIC
$Comp
L Device:LED D1
U 1 1 00000006
P 3300 5000
F 0 "D1" H 3480 5120 50  0000 C CNN
F 1 "STATUS_LED" H 3550 4880 50  0000 C CNN
	1    3300 5000
	1 0 0 -1
$EndComp
$Comp
L Device:R R6
U 1 1 00000007
P 3900 5000
F 0 "R6" H 4080 5120 50  0000 C CNN
F 1 "330R" H 4150 4880 50  0000 C CNN
	1    3900 5000
	0 -1 -1 0
$EndComp
Wire Wire Line
	3200 5000 2700 5000
Text Label 2700 5000 0    50   ~ 0
STATUS_LED_PIN7
Wire Wire Line
	3400 5000 3750 5000
Wire Wire Line
	4050 5000 4400 5000
Text Label 4400 5000 0    50   ~ 0
GND_LOGIC
$Comp
L Connector_Generic:Conn_01x03 J5
U 1 1 00000008
P 8200 2150
F 0 "J5" H 8380 2270 50  0000 C CNN
F 1 "LASER_650NM_TTL" H 8450 2030 50  0000 C CNN
	1    8200 2150
	1 0 0 -1
$EndComp
Wire Wire Line
	8300 2050 9000 2050
Text Label 9000 2050 0    50   ~ 0
LASER_5V_SAFE
Wire Wire Line
	8300 2150 9000 2150
Text Label 9000 2150 0    50   ~ 0
GND_LOGIC
Wire Wire Line
	8300 2250 9000 2250
Text Label 9000 2250 0    50   ~ 0
LASER_TTL_IN
$Comp
L Device:R R1
U 1 1 00000009
P 7200 2250
F 0 "R1" H 7380 2370 50  0000 C CNN
F 1 "1K" H 7450 2130 50  0000 C CNN
	1    7200 2250
	0 1 1 0
$EndComp
Wire Wire Line
	6900 2250 6500 2250
Text Label 6500 2250 0    50   ~ 0
LASER_TTL_PIN6
Wire Wire Line
	7500 2250 7850 2250
Text Label 7850 2250 0    50   ~ 0
LASER_TTL_IN
$Comp
L Device:R R2
U 1 1 0000000A
P 7850 2750
F 0 "R2" H 8030 2870 50  0000 C CNN
F 1 "10K" H 8100 2630 50  0000 C CNN
	1    7850 2750
	1 0 0 -1
$EndComp
Wire Wire Line
	7850 2600 7850 2250
Wire Wire Line
	7850 2900 7850 3150
Text Label 7850 3150 0    50   ~ 0
GND_LOGIC
$Comp
L Connector_Generic:Conn_01x02 J8
U 1 1 0000000B
P 6500 1200
F 0 "J8" H 6680 1320 50  0000 C CNN
F 1 "AUX_5V_INPUT" H 6750 1080 50  0000 C CNN
	1    6500 1200
	1 0 0 -1
$EndComp
Wire Wire Line
	6600 1150 7000 1150
Text Label 7000 1150 0    50   ~ 0
AUX_5V_RAW
Wire Wire Line
	6600 1250 7000 1250
Text Label 7000 1250 0    50   ~ 0
GND_LOGIC
$Comp
L Switch:SW_SPST SW1
U 1 1 0000000C
P 7600 1150
F 0 "SW1" H 7780 1270 50  0000 C CNN
F 1 "E_STOP_NC" H 7850 1030 50  0000 C CNN
	1    7600 1150
	1 0 0 -1
$EndComp
Wire Wire Line
	7450 1150 7000 1150
Wire Wire Line
	7750 1150 8050 1150
$Comp
L Switch:SW_SPST SW2
U 1 1 0000000D
P 8500 1150
F 0 "SW2" H 8680 1270 50  0000 C CNN
F 1 "LID_NC" H 8750 1030 50  0000 C CNN
	1    8500 1150
	1 0 0 -1
$EndComp
Wire Wire Line
	8350 1150 8050 1150
Wire Wire Line
	8650 1150 9100 1150
Text Label 9100 1150 0    50   ~ 0
LASER_5V_SAFE
Text Notes 7150 900 0    60   ~ 12
Both switches wired using normally-closed contacts
$Comp
L Device:R R3
U 1 1 0000000E
P 7100 3500
F 0 "R3" H 7280 3620 50  0000 C CNN
F 1 "12K" H 7350 3380 50  0000 C CNN
	1    7100 3500
	0 1 1 0
$EndComp
Wire Wire Line
	6800 3500 6500 3500
Text Label 6500 3500 0    50   ~ 0
LASER_5V_SAFE
Wire Wire Line
	7400 3500 7800 3500
Text Label 7800 3500 0    50   ~ 0
INTERLOCK_MON_PIN3
$Comp
L Device:R R4
U 1 1 0000000F
P 7800 4000
F 0 "R4" H 7980 4120 50  0000 C CNN
F 1 "22K" H 8050 3880 50  0000 C CNN
	1    7800 4000
	1 0 0 -1
$EndComp
Wire Wire Line
	7800 3850 7800 3500
Wire Wire Line
	7800 4150 7800 4400
Text Label 7800 4400 0    50   ~ 0
GND_LOGIC
$Comp
L Device:C C1
U 1 1 00000010
P 8300 4000
F 0 "C1" H 8480 4120 50  0000 C CNN
F 1 "100NF" H 8550 3880 50  0000 C CNN
	1    8300 4000
	1 0 0 -1
$EndComp
Wire Wire Line
	8300 3850 8300 3500
Wire Wire Line
	8300 3500 7800 3500
Wire Wire Line
	8300 4150 8300 4400
Text Label 8300 4400 0    50   ~ 0
GND_LOGIC
$Comp
L Connector_Generic:Conn_01x08 J6
U 1 1 00000011
P 6500 5600
F 0 "J6" H 6680 5720 50  0000 C CNN
F 1 "DUAL_BIPOLAR_INTERFACE" H 6750 5480 50  0000 C CNN
	1    6500 5600
	1 0 0 -1
$EndComp
Wire Wire Line
	6600 5250 7200 5250
Text Label 7200 5250 0    50   ~ 0
DAC_X_0_2V048
Wire Wire Line
	6600 5350 7200 5350
Text Label 7200 5350 0    50   ~ 0
DAC_Y_0_2V048
Wire Wire Line
	6600 5450 7200 5450
Text Label 7200 5450 0    50   ~ 0
GND_SIGNAL
Wire Wire Line
	6600 5550 7200 5550
Text Label 7200 5550 0    50   ~ 0
IFACE_VPLUS
Wire Wire Line
	6600 5650 7200 5650
Text Label 7200 5650 0    50   ~ 0
IFACE_VMINUS
Wire Wire Line
	6600 5750 7200 5750
Text Label 7200 5750 0    50   ~ 0
GALVO_X_CMD
Wire Wire Line
	6600 5850 7200 5850
Text Label 7200 5850 0    50   ~ 0
GALVO_Y_ZERO
Wire Wire Line
	6600 5950 7200 5950
Text Label 7200 5950 0    50   ~ 0
GND_SIGNAL
$Comp
L Connector_Generic:Conn_01x06 J7
U 1 1 00000012
P 9000 5600
F 0 "J7" H 9180 5720 50  0000 C CNN
F 1 "GALVO_XY_DRIVER_INPUTS" H 9250 5480 50  0000 C CNN
	1    9000 5600
	1 0 0 -1
$EndComp
Wire Wire Line
	9100 5350 9700 5350
Text Label 9700 5350 0    50   ~ 0
GALVO_X_CMD
Wire Wire Line
	9100 5450 9700 5450
Text Label 9700 5450 0    50   ~ 0
GND_SIGNAL
Wire Wire Line
	9100 5550 9700 5550
Text Label 9700 5550 0    50   ~ 0
GALVO_Y_ZERO
Wire Wire Line
	9100 5650 9700 5650
Text Label 9700 5650 0    50   ~ 0
GND_SIGNAL
Wire Wire Line
	9100 5750 9700 5750
Text Label 9700 5750 0    50   ~ 0
DRIVER_ENABLE_DOC
Wire Wire Line
	9100 5850 9700 5850
Text Label 9700 5850 0    50   ~ 0
SHIELD_CHASSIS
Text Notes 6450 6250 0    60   ~ 12
J6 is a dual-channel 0..2.048 V to bipolar converter.\nSet X center and Y neutral to 0 V. Begin at +/-0.5 V.\nDo not ground differential inputs unless the driver manual permits it.
Text Notes 700 6900 0    60   ~ 12
POWER / GROUND RULES
Text Notes 700 7150 0    50   ~ 0
Teensy is powered by USB. Sensors and DAC use 3.3 V. Laser uses the safe 5 V chain.\nGalvo drivers and bipolar interface use their documented supplies. Keep power wiring away from OPT101.\nConnect signal grounds at one star point only when the galvo interface manual allows single-ended operation.
$EndSCHEMATC
