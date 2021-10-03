EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 9725 625  1350 1000
U 60711259
F0 "Power" 50
F1 "power.sch" 50
$EndSheet
$Sheet
S 725  750  1000 875 
U 608B4064
F0 "MCU" 50
F1 "mcu.sch" 50
$EndSheet
$Sheet
S 6850 925  1250 3025
U 60F6EF94
F0 "Switching" 50
F1 "switching.sch" 50
F2 "AUDIO_IN_1" I L 6850 1075 50 
F3 "AUDIO_IN_2" I L 6850 1475 50 
F4 "AUDIO_IN_1A" I R 8100 1075 50 
F5 "AUDIO_IN_1B" I R 8100 1175 50 
F6 "AUDIO_IN_1C" I R 8100 1275 50 
F7 "AUDIO_IN_1D" I R 8100 1375 50 
F8 "AUDIO_IN_2A" I R 8100 1475 50 
F9 "AUDIO_IN_2B" I R 8100 1575 50 
F10 "AUDIO_IN_2C" I R 8100 1675 50 
F11 "AUDIO_IN_2D" I R 8100 1775 50 
F12 "SDI" I L 6850 3625 50 
F13 "~CS" I L 6850 3725 50 
F14 "SCK" I L 6850 3825 50 
F15 "DAC_4B" I R 8100 3250 50 
F16 "DAC_4A" I R 8100 3150 50 
F17 "DAC_3B" I R 8100 2850 50 
F18 "DAC_3A" I R 8100 2750 50 
F19 "DAC_2B" I R 8100 2450 50 
F20 "DAC_2A" I R 8100 2350 50 
F21 "DAC_1B" I R 8100 2050 50 
F22 "DAC_1A" I R 8100 1950 50 
F23 "DAC_4" I L 6850 3275 50 
F24 "DAC_3" I L 6850 3075 50 
F25 "DAC_2" I L 6850 2875 50 
F26 "DAC_1" I L 6850 2675 50 
F27 "DAC_2D" I R 8100 2650 50 
F28 "DAC_2C" I R 8100 2550 50 
F29 "DAC_1D" I R 8100 2250 50 
F30 "DAC_1C" I R 8100 2150 50 
F31 "DAC_4D" I R 8100 3450 50 
F32 "DAC_4C" I R 8100 3350 50 
F33 "DAC_3D" I R 8100 3050 50 
F34 "DAC_3C" I R 8100 2950 50 
$EndSheet
$Sheet
S 4750 3325 1225 550 
U 608FFE97
F0 "AnalogOutBuffers" 50
F1 "AnalogOutBuffers.sch" 50
F2 "DAC_IN_1" I L 4750 3450 50 
F3 "DAC_IN_2" I L 4750 3550 50 
F4 "DAC_IN_3" I L 4750 3650 50 
F5 "DAC_IN_4" I L 4750 3750 50 
F6 "DAC_OUT_1" I R 5975 3450 50 
F7 "DAC_OUT_2" I R 5975 3550 50 
F8 "DAC_OUT_3" I R 5975 3650 50 
F9 "DAC_OUT_4" I R 5975 3750 50 
$EndSheet
$Sheet
S 725  2025 1225 550 
U 61059808
F0 "AnalogInBuffers" 50
F1 "AnalogInBuffers.sch" 50
$EndSheet
Wire Wire Line
	5975 3450 6325 3450
Wire Wire Line
	6325 3450 6325 2675
Wire Wire Line
	6325 2675 6850 2675
Wire Wire Line
	5975 3650 6475 3650
Wire Wire Line
	6475 3650 6475 3075
Wire Wire Line
	6475 3075 6850 3075
Wire Wire Line
	5975 3750 6550 3750
Wire Wire Line
	6550 3750 6550 3275
Wire Wire Line
	6550 3275 6850 3275
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J5
U 1 1 613689DC
P 1300 6300
F 0 "J5" H 1350 7417 50  0000 C CNN
F 1 "Left" H 1350 7326 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H 1300 6300 50  0001 C CNN
F 3 "~" H 1300 6300 50  0001 C CNN
	1    1300 6300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J7
U 1 1 61377789
P 3875 6250
F 0 "J7" V 3879 7230 50  0000 L CNN
F 1 "Bottom" V 3970 7230 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H 3875 6250 50  0001 C CNN
F 3 "~" H 3875 6250 50  0001 C CNN
	1    3875 6250
	0    -1   1    0   
$EndComp
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J6
U 1 1 6137A5E9
P 7225 5400
F 0 "J6" H 7275 6517 50  0000 C CNN
F 1 "Right" H 7275 6426 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H 7225 5400 50  0001 C CNN
F 3 "~" H 7225 5400 50  0001 C CNN
	1    7225 5400
	1    0    0    -1  
$EndComp
$Sheet
S 9675 5300 1375 1075
U 613C06E5
F0 "Upstream I/O" 50
F1 "upstream-io.sch" 50
F2 "AUDIO_IN_L" I L 9675 5425 50 
F3 "AUDIO_IN_R" I L 9675 5525 50 
F4 "AUDIO_OUT_L" I L 9675 5625 50 
F5 "AUDIO_OUT_R" I L 9675 5725 50 
F6 "OSC_A" I L 9675 5825 50 
F7 "OSC_B" I L 9675 5925 50 
F8 "OSC_C" I L 9675 6025 50 
F9 "OSC_D" I L 9675 6125 50 
$EndSheet
$Comp
L power:GND #PWR0101
U 1 1 613D42C8
P 2975 6550
F 0 "#PWR0101" H 2975 6300 50  0001 C CNN
F 1 "GND" H 2980 6377 50  0000 C CNN
F 2 "" H 2975 6550 50  0001 C CNN
F 3 "" H 2975 6550 50  0001 C CNN
	1    2975 6550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 613D4870
P 4875 6550
F 0 "#PWR0102" H 4875 6300 50  0001 C CNN
F 1 "GND" H 4880 6377 50  0000 C CNN
F 2 "" H 4875 6550 50  0001 C CNN
F 3 "" H 4875 6550 50  0001 C CNN
	1    4875 6550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 613D4D0A
P 4875 6050
F 0 "#PWR0103" H 4875 5800 50  0001 C CNN
F 1 "GND" H 4880 5877 50  0000 C CNN
F 2 "" H 4875 6050 50  0001 C CNN
F 3 "" H 4875 6050 50  0001 C CNN
	1    4875 6050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 613D5215
P 2975 6050
F 0 "#PWR0104" H 2975 5800 50  0001 C CNN
F 1 "GND" H 2980 5877 50  0000 C CNN
F 2 "" H 2975 6050 50  0001 C CNN
F 3 "" H 2975 6050 50  0001 C CNN
	1    2975 6050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 613D5998
P 1100 5400
F 0 "#PWR0105" H 1100 5150 50  0001 C CNN
F 1 "GND" V 1105 5272 50  0000 R CNN
F 2 "" H 1100 5400 50  0001 C CNN
F 3 "" H 1100 5400 50  0001 C CNN
	1    1100 5400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 613D60E3
P 1600 5400
F 0 "#PWR0106" H 1600 5150 50  0001 C CNN
F 1 "GND" V 1605 5272 50  0000 R CNN
F 2 "" H 1600 5400 50  0001 C CNN
F 3 "" H 1600 5400 50  0001 C CNN
	1    1600 5400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 613D6590
P 1600 7300
F 0 "#PWR0107" H 1600 7050 50  0001 C CNN
F 1 "GND" V 1605 7172 50  0000 R CNN
F 2 "" H 1600 7300 50  0001 C CNN
F 3 "" H 1600 7300 50  0001 C CNN
	1    1600 7300
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 613D6C7A
P 1100 7300
F 0 "#PWR0108" H 1100 7050 50  0001 C CNN
F 1 "GND" V 1105 7172 50  0000 R CNN
F 2 "" H 1100 7300 50  0001 C CNN
F 3 "" H 1100 7300 50  0001 C CNN
	1    1100 7300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 613D7482
P 7525 4500
F 0 "#PWR0109" H 7525 4250 50  0001 C CNN
F 1 "GND" V 7530 4372 50  0000 R CNN
F 2 "" H 7525 4500 50  0001 C CNN
F 3 "" H 7525 4500 50  0001 C CNN
	1    7525 4500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 613D7A6C
P 7025 4500
F 0 "#PWR0110" H 7025 4250 50  0001 C CNN
F 1 "GND" V 7030 4372 50  0000 R CNN
F 2 "" H 7025 4500 50  0001 C CNN
F 3 "" H 7025 4500 50  0001 C CNN
	1    7025 4500
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 613D8081
P 7025 6400
F 0 "#PWR0111" H 7025 6150 50  0001 C CNN
F 1 "GND" V 7030 6272 50  0000 R CNN
F 2 "" H 7025 6400 50  0001 C CNN
F 3 "" H 7025 6400 50  0001 C CNN
	1    7025 6400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 613D85FC
P 7525 6400
F 0 "#PWR0112" H 7525 6150 50  0001 C CNN
F 1 "GND" V 7530 6272 50  0000 R CNN
F 2 "" H 7525 6400 50  0001 C CNN
F 3 "" H 7525 6400 50  0001 C CNN
	1    7525 6400
	0    -1   -1   0   
$EndComp
Text GLabel 1100 6100 0    50   Input ~ 0
A1-PRE
Text GLabel 1600 6100 2    50   Input ~ 0
A2-PRE
Text GLabel 1100 6200 0    50   Input ~ 0
A3-PRE
Text GLabel 1600 6200 2    50   Input ~ 0
A4-PRE
Text GLabel 1600 6300 2    50   Input ~ 0
A6-PRE
Text GLabel 1100 6400 0    50   Input ~ 0
A7-PRE
Text GLabel 1600 6400 2    50   Input ~ 0
A8-PRE
Text GLabel 1100 6500 0    50   Input ~ 0
A9-PRE
Text GLabel 1600 6500 2    50   Input ~ 0
A10-PRE
Text GLabel 1100 6600 0    50   Input ~ 0
A11-PRE
Text GLabel 1600 6600 2    50   Input ~ 0
A12-PRE
Text GLabel 1100 6800 0    50   Input ~ 0
A13
Text GLabel 1100 6900 0    50   Input ~ 0
A15
Text GLabel 1600 6900 2    50   Input ~ 0
A16
Text GLabel 1600 7000 2    50   Input ~ 0
A17
Text GLabel 1100 7000 0    50   Input ~ 0
A18
Text GLabel 1600 7100 2    50   Input ~ 0
A19
Text GLabel 1100 7100 0    50   Input ~ 0
A20
Text GLabel 4375 6050 1    50   Input ~ 0
SERIAL1.3
Text GLabel 4275 6050 1    50   Input ~ 0
SERIAL1.2
Text GLabel 4175 6050 1    50   Input ~ 0
SERIAL1.1
Text GLabel 4075 6050 1    50   Input ~ 0
SERIAL1.0
Text GLabel 4775 6050 1    50   Input ~ 0
DR1
Text GLabel 4675 6050 1    50   Input ~ 0
DR2
Text GLabel 4575 6050 1    50   Input ~ 0
DR3
Text GLabel 4475 6050 1    50   Input ~ 0
DR4
Text GLabel 3875 6050 1    50   Input ~ 0
DB0
Text GLabel 3275 6050 1    50   Input ~ 0
DB1
Text GLabel 3375 6050 1    50   Input ~ 0
DB2
Text GLabel 1100 6300 0    50   Input ~ 0
A5-PRE
Text GLabel 1600 6800 2    50   Input ~ 0
A14
Text Label 8100 1075 0    50   ~ 0
AUDIO_IN_1A
Text Label 8100 1175 0    50   ~ 0
AUDIO_IN_1B
Text Label 8100 1275 0    50   ~ 0
AUDIO_IN_1C
Text Label 8100 1375 0    50   ~ 0
AUDIO_IN_1D
Text Label 8100 1475 0    50   ~ 0
AUDIO_IN_2A
Text Label 8100 1575 0    50   ~ 0
AUDIO_IN_2B
Text Label 8100 1675 0    50   ~ 0
AUDIO_IN_2C
Text Label 8100 1775 0    50   ~ 0
AUDIO_IN_2D
Text Label 7525 4900 0    50   ~ 0
AUDIO_IN_1A
Text Label 7025 4900 2    50   ~ 0
AUDIO_IN_1B
Text Label 7025 5000 2    50   ~ 0
AUDIO_IN_1C
Text Label 7525 5000 0    50   ~ 0
AUDIO_IN_1D
Text Label 7525 4700 0    50   ~ 0
AUDIO_IN_2A
Text Label 7025 4700 2    50   ~ 0
AUDIO_IN_2B
Text Label 7025 4800 2    50   ~ 0
AUDIO_IN_2C
Text Label 7525 4800 0    50   ~ 0
AUDIO_IN_2D
Text Label 8100 1950 0    50   ~ 0
DAC_1A
Text Label 8100 2050 0    50   ~ 0
DAC_1B
Text Label 8100 2150 0    50   ~ 0
DAC_1C
Text Label 8100 2250 0    50   ~ 0
DAC_1D
Text Label 8100 2350 0    50   ~ 0
DAC_2A
Text Label 8100 2450 0    50   ~ 0
DAC_2B
Text Label 8100 2550 0    50   ~ 0
DAC_2C
Text Label 8100 2650 0    50   ~ 0
DAC_2D
Text Label 8100 2750 0    50   ~ 0
DAC_3A
Text Label 8100 2850 0    50   ~ 0
DAC_3B
Text Label 8100 2950 0    50   ~ 0
DAC_3C
Text Label 8100 3050 0    50   ~ 0
DAC_3D
Text Label 8100 3150 0    50   ~ 0
DAC_4A
Text Label 8100 3250 0    50   ~ 0
DAC_4B
Text Label 8100 3350 0    50   ~ 0
DAC_4C
Text Label 8100 3450 0    50   ~ 0
DAC_4D
Text Label 7525 5700 0    50   ~ 0
DAC_1A
Text Label 7025 5700 2    50   ~ 0
DAC_1B
Text Label 7025 5800 2    50   ~ 0
DAC_1C
Text Label 7525 5800 0    50   ~ 0
DAC_1D
Text Label 7525 5500 0    50   ~ 0
DAC_2A
Text Label 7025 5500 2    50   ~ 0
DAC_2B
Text Label 7025 5600 2    50   ~ 0
DAC_2C
Text Label 7525 5600 0    50   ~ 0
DAC_2D
Text Label 7525 6200 0    50   ~ 0
DAC_3A
Text Label 7025 6200 2    50   ~ 0
DAC_3B
Text Label 7025 6300 2    50   ~ 0
DAC_3C
Text Label 7525 6300 0    50   ~ 0
DAC_3D
Text Label 7525 6000 0    50   ~ 0
DAC_4A
Text Label 7025 6000 2    50   ~ 0
DAC_4B
Text Label 7025 6100 2    50   ~ 0
DAC_4C
Text Label 7525 6100 0    50   ~ 0
DAC_4D
$Comp
L power:GND #PWR0121
U 1 1 61428885
P 7525 5400
F 0 "#PWR0121" H 7525 5150 50  0001 C CNN
F 1 "GND" V 7530 5272 50  0000 R CNN
F 2 "" H 7525 5400 50  0001 C CNN
F 3 "" H 7525 5400 50  0001 C CNN
	1    7525 5400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 61428D1B
P 7025 5400
F 0 "#PWR0122" H 7025 5150 50  0001 C CNN
F 1 "GND" V 7030 5272 50  0000 R CNN
F 2 "" H 7025 5400 50  0001 C CNN
F 3 "" H 7025 5400 50  0001 C CNN
	1    7025 5400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 61429FEB
P 7025 5900
F 0 "#PWR0123" H 7025 5650 50  0001 C CNN
F 1 "GND" V 7030 5772 50  0000 R CNN
F 2 "" H 7025 5900 50  0001 C CNN
F 3 "" H 7025 5900 50  0001 C CNN
	1    7025 5900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0124
U 1 1 6142A557
P 7525 5900
F 0 "#PWR0124" H 7525 5650 50  0001 C CNN
F 1 "GND" V 7530 5772 50  0000 R CNN
F 2 "" H 7525 5900 50  0001 C CNN
F 3 "" H 7525 5900 50  0001 C CNN
	1    7525 5900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0125
U 1 1 6142E9CE
P 7025 5100
F 0 "#PWR0125" H 7025 4850 50  0001 C CNN
F 1 "GND" V 7030 4972 50  0000 R CNN
F 2 "" H 7025 5100 50  0001 C CNN
F 3 "" H 7025 5100 50  0001 C CNN
	1    7025 5100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0126
U 1 1 6142ED24
P 7525 5100
F 0 "#PWR0126" H 7525 4850 50  0001 C CNN
F 1 "GND" V 7530 4972 50  0000 R CNN
F 2 "" H 7525 5100 50  0001 C CNN
F 3 "" H 7525 5100 50  0001 C CNN
	1    7525 5100
	0    -1   -1   0   
$EndComp
Text Label 7525 5300 0    50   ~ 0
OSC_A
Text Label 7025 5300 2    50   ~ 0
OSC_B
Text Label 7525 5200 0    50   ~ 0
OSC_C
Text Label 7025 5200 2    50   ~ 0
OSC_D
Text GLabel 1600 5500 2    50   Input ~ 0
+12VDOWNSTREAM
Text GLabel 1100 5500 0    50   Input ~ 0
+12VDOWNSTREAM
$Comp
L power:GND #PWR0127
U 1 1 61434CD9
P 1100 5600
F 0 "#PWR0127" H 1100 5350 50  0001 C CNN
F 1 "GND" V 1105 5472 50  0000 R CNN
F 2 "" H 1100 5600 50  0001 C CNN
F 3 "" H 1100 5600 50  0001 C CNN
	1    1100 5600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0128
U 1 1 6143512F
P 1600 5600
F 0 "#PWR0128" H 1600 5350 50  0001 C CNN
F 1 "GND" V 1605 5472 50  0000 R CNN
F 2 "" H 1600 5600 50  0001 C CNN
F 3 "" H 1600 5600 50  0001 C CNN
	1    1600 5600
	0    -1   -1   0   
$EndComp
Text GLabel 1600 5700 2    50   Input ~ 0
-12VDOWNSTREAM
Text GLabel 1100 5700 0    50   Input ~ 0
-12VDOWNSTREAM
$Comp
L power:GND #PWR0129
U 1 1 61436723
P 1100 5800
F 0 "#PWR0129" H 1100 5550 50  0001 C CNN
F 1 "GND" V 1105 5672 50  0000 R CNN
F 2 "" H 1100 5800 50  0001 C CNN
F 3 "" H 1100 5800 50  0001 C CNN
	1    1100 5800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0130
U 1 1 61436A22
P 1600 5800
F 0 "#PWR0130" H 1600 5550 50  0001 C CNN
F 1 "GND" V 1605 5672 50  0000 R CNN
F 2 "" H 1600 5800 50  0001 C CNN
F 3 "" H 1600 5800 50  0001 C CNN
	1    1600 5800
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0131
U 1 1 61436FC1
P 1600 6700
F 0 "#PWR0131" H 1600 6450 50  0001 C CNN
F 1 "GND" V 1605 6572 50  0000 R CNN
F 2 "" H 1600 6700 50  0001 C CNN
F 3 "" H 1600 6700 50  0001 C CNN
	1    1600 6700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0132
U 1 1 61437330
P 1100 6700
F 0 "#PWR0132" H 1100 6450 50  0001 C CNN
F 1 "GND" V 1105 6572 50  0000 R CNN
F 2 "" H 1100 6700 50  0001 C CNN
F 3 "" H 1100 6700 50  0001 C CNN
	1    1100 6700
	0    1    1    0   
$EndComp
Text Label 9675 5425 2    50   ~ 0
AUDIO_IN_L
Text Label 9675 5525 2    50   ~ 0
AUDIO_IN_R
Text Label 6850 1075 2    50   ~ 0
AUDIO_IN_L
Text Label 6850 1475 2    50   ~ 0
AUDIO_IN_R
Text Label 9675 5625 2    50   ~ 0
AUDIO_OUT_L
Text Label 9675 5725 2    50   ~ 0
AUDIO_OUT_R
Text Label 7025 4600 2    50   ~ 0
AUDIO_OUT_L
Text Label 7525 4600 0    50   ~ 0
AUDIO_OUT_R
Text Label 9675 5825 2    50   ~ 0
OSC_A
Text Label 9675 5925 2    50   ~ 0
OSC_B
Text Label 9675 6025 2    50   ~ 0
OSC_C
Text Label 9675 6125 2    50   ~ 0
OSC_D
Text GLabel 4750 3450 0    50   Input ~ 0
DAC_1
Text GLabel 4750 3550 0    50   Input ~ 0
DAC_2
Text GLabel 4750 3650 0    50   Input ~ 0
DAC_3
Text GLabel 4750 3750 0    50   Input ~ 0
DAC_4
$Comp
L power:+3.3V #PWR?
U 1 1 6144C0F6
P 1600 5900
AR Path="/60711259/6144C0F6" Ref="#PWR?"  Part="1" 
AR Path="/6144C0F6" Ref="#PWR0133"  Part="1" 
F 0 "#PWR0133" H 1600 5750 50  0001 C CNN
F 1 "+3.3V" V 1600 6125 50  0000 C CNN
F 2 "" H 1600 5900 50  0001 C CNN
F 3 "" H 1600 5900 50  0001 C CNN
	1    1600 5900
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6144C266
P 1100 5900
AR Path="/60711259/6144C266" Ref="#PWR?"  Part="1" 
AR Path="/6144C266" Ref="#PWR0134"  Part="1" 
F 0 "#PWR0134" H 1100 5750 50  0001 C CNN
F 1 "+3.3V" V 1100 6125 50  0000 C CNN
F 2 "" H 1100 5900 50  0001 C CNN
F 3 "" H 1100 5900 50  0001 C CNN
	1    1100 5900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5975 3550 6400 3550
Wire Wire Line
	6400 3550 6400 2875
Wire Wire Line
	6400 2875 6850 2875
Text GLabel 6850 3625 0    50   Input ~ 0
SPI_COPI
Text GLabel 6850 3825 0    50   Input ~ 0
SPI_SCLK
Text GLabel 3775 6050 1    50   Input ~ 0
SERIAL4.3
Text GLabel 3675 6050 1    50   Input ~ 0
SERIAL4.2
Text GLabel 3575 6050 1    50   Input ~ 0
SERIAL4.1
Text GLabel 3475 6050 1    50   Input ~ 0
SERIAL4.0
$Comp
L power:GND #PWR0167
U 1 1 6168CFB1
P 3975 6050
F 0 "#PWR0167" H 3975 5800 50  0001 C CNN
F 1 "GND" H 3980 5877 50  0000 C CNN
F 2 "" H 3975 6050 50  0001 C CNN
F 3 "" H 3975 6050 50  0001 C CNN
	1    3975 6050
	-1   0    0    1   
$EndComp
Wire Wire Line
	2975 6550 3075 6550
Connection ~ 2975 6550
Wire Wire Line
	3075 6550 3175 6550
Connection ~ 3075 6550
Wire Wire Line
	3175 6550 3275 6550
Connection ~ 3175 6550
Wire Wire Line
	3275 6550 3375 6550
Connection ~ 3275 6550
Wire Wire Line
	3375 6550 3475 6550
Connection ~ 3375 6550
Wire Wire Line
	3475 6550 3575 6550
Connection ~ 3475 6550
Wire Wire Line
	3575 6550 3675 6550
Connection ~ 3575 6550
Wire Wire Line
	3675 6550 3775 6550
Connection ~ 3675 6550
Wire Wire Line
	3775 6550 3875 6550
Connection ~ 3775 6550
Connection ~ 4875 6550
Connection ~ 3875 6550
Wire Wire Line
	3875 6550 3975 6550
Connection ~ 3975 6550
Wire Wire Line
	3975 6550 4075 6550
Connection ~ 4075 6550
Wire Wire Line
	4075 6550 4175 6550
Connection ~ 4175 6550
Wire Wire Line
	4175 6550 4275 6550
Connection ~ 4275 6550
Wire Wire Line
	4275 6550 4375 6550
Connection ~ 4375 6550
Wire Wire Line
	4375 6550 4475 6550
Connection ~ 4475 6550
Wire Wire Line
	4475 6550 4575 6550
Connection ~ 4575 6550
Wire Wire Line
	4575 6550 4675 6550
Connection ~ 4675 6550
Wire Wire Line
	4675 6550 4775 6550
Connection ~ 4775 6550
Wire Wire Line
	4775 6550 4875 6550
Wire Wire Line
	2975 6050 3075 6050
Connection ~ 2975 6050
Connection ~ 3075 6050
Wire Wire Line
	3075 6050 3175 6050
$Comp
L power:GND #PWR0168
U 1 1 616A2886
P 1600 6000
F 0 "#PWR0168" H 1600 5750 50  0001 C CNN
F 1 "GND" V 1605 5872 50  0000 R CNN
F 2 "" H 1600 6000 50  0001 C CNN
F 3 "" H 1600 6000 50  0001 C CNN
	1    1600 6000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0169
U 1 1 616A2BF7
P 1100 6000
F 0 "#PWR0169" H 1100 5750 50  0001 C CNN
F 1 "GND" V 1105 5872 50  0000 R CNN
F 2 "" H 1100 6000 50  0001 C CNN
F 3 "" H 1100 6000 50  0001 C CNN
	1    1100 6000
	0    1    1    0   
$EndComp
Text Notes 6050 4075 0    50   ~ 0
TODO: Wire up CS :(
$EndSCHEMATC
