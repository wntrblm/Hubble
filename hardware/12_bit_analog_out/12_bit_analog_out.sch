EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "12-bit analog outputs"
Date "2021-10-05"
Rev "v0"
Comp "Winterbloom"
Comment1 "CERN OHL-P V2"
Comment2 "testkit.wntr.dev"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Ferrite_Bead_Small FB1
U 1 1 615C815F
P 1750 2625
F 0 "FB1" V 1513 2625 50  0000 C CNN
F 1 "BEAD" V 1604 2625 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 1680 2625 50  0001 C CNN
F 3 "~" H 1750 2625 50  0001 C CNN
	1    1750 2625
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 615C9EB6
P 4675 3175
F 0 "#PWR0101" H 4675 2925 50  0001 C CNN
F 1 "GND" H 4680 3002 50  0001 C CNN
F 2 "" H 4675 3175 50  0001 C CNN
F 3 "" H 4675 3175 50  0001 C CNN
	1    4675 3175
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3VA #PWR0107
U 1 1 615CE9E7
P 4675 2475
F 0 "#PWR0107" H 4675 2325 50  0001 C CNN
F 1 "+3.3VA" V 4675 2725 50  0000 C CNN
F 2 "" H 4675 2475 50  0001 C CNN
F 3 "" H 4675 2475 50  0001 C CNN
	1    4675 2475
	1    0    0    -1  
$EndComp
Text Label 3900 2875 2    50   ~ 0
~LDAC
Text Label 3900 2775 2    50   ~ 0
SDA
Text Label 3900 2675 2    50   ~ 0
SCL
Wire Wire Line
	3900 2675 4075 2675
Wire Wire Line
	3900 2775 4075 2775
Wire Wire Line
	3900 2875 4075 2875
Text Label 3900 2975 2    50   ~ 0
RDY
Wire Wire Line
	3900 2975 4075 2975
Text Label 5275 2675 0    50   ~ 0
DAC_OUT_A
Text Label 5275 2775 0    50   ~ 0
DAC_OUT_B
Text Label 5275 2875 0    50   ~ 0
DAC_OUT_C
Text Label 5275 2975 0    50   ~ 0
DAC_OUT_D
$Comp
L power:+3.3VA #PWR0108
U 1 1 615D08D7
P 2425 2625
F 0 "#PWR0108" H 2425 2475 50  0001 C CNN
F 1 "+3.3VA" V 2425 2875 50  0000 C CNN
F 2 "" H 2425 2625 50  0001 C CNN
F 3 "" H 2425 2625 50  0001 C CNN
	1    2425 2625
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR0109
U 1 1 615D11ED
P 1650 2625
F 0 "#PWR0109" H 1650 2475 50  0001 C CNN
F 1 "+3.3V" V 1650 2750 50  0000 L CNN
F 2 "" H 1650 2625 50  0001 C CNN
F 3 "" H 1650 2625 50  0001 C CNN
	1    1650 2625
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 615D3AEF
P 1950 2800
F 0 "C1" H 1858 2754 50  0000 R CNN
F 1 "1uF" H 1858 2845 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1950 2800 50  0001 C CNN
F 3 "~" H 1950 2800 50  0001 C CNN
	1    1950 2800
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 615D470B
P 2325 2800
F 0 "C2" H 2233 2754 50  0000 R CNN
F 1 "0.1uF" H 2233 2845 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2325 2800 50  0001 C CNN
F 3 "~" H 2325 2800 50  0001 C CNN
	1    2325 2800
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 615D61B6
P 1950 2900
F 0 "#PWR0112" H 1950 2650 50  0001 C CNN
F 1 "GND" H 1955 2727 50  0001 C CNN
F 2 "" H 1950 2900 50  0001 C CNN
F 3 "" H 1950 2900 50  0001 C CNN
	1    1950 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 615D6930
P 2325 2900
F 0 "#PWR0113" H 2325 2650 50  0001 C CNN
F 1 "GND" H 2330 2727 50  0001 C CNN
F 2 "" H 2325 2900 50  0001 C CNN
F 3 "" H 2325 2900 50  0001 C CNN
	1    2325 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2425 2625 2325 2625
Wire Wire Line
	1950 2700 1950 2625
Connection ~ 1950 2625
Wire Wire Line
	1950 2625 1850 2625
Wire Wire Line
	2325 2700 2325 2625
Connection ~ 2325 2625
Wire Wire Line
	2325 2625 1950 2625
$Comp
L winterbloom:OPA4197 U3
U 1 1 615DFB3C
P 8150 2000
F 0 "U3" H 8150 2367 50  0000 C CNN
F 1 "OPA4197" H 8150 2276 50  0000 C CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 8150 1650 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/opa4197.pdf" H 8200 2200 50  0001 C CNN
F 4 "OPA4197IPW" H 8150 1550 39  0001 C CNN "mpn"
	1    8150 2000
	1    0    0    -1  
$EndComp
Text Label 7100 2100 2    50   ~ 0
DAC_OUT_A
$Comp
L power:GND #PWR0114
U 1 1 615E1678
P 7850 1900
F 0 "#PWR0114" H 7850 1650 50  0001 C CNN
F 1 "GND" H 7855 1727 50  0001 C CNN
F 2 "" H 7850 1900 50  0001 C CNN
F 3 "" H 7850 1900 50  0001 C CNN
	1    7850 1900
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R2
U 1 1 615E220C
P 7400 2100
F 0 "R2" V 7195 2100 50  0000 C CNN
F 1 "1.54k" V 7286 2100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7440 2090 50  0001 C CNN
F 3 "~" H 7400 2100 50  0001 C CNN
	1    7400 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	7100 2100 7250 2100
$Comp
L Device:R_US R3
U 1 1 615E290D
P 7400 2400
F 0 "R3" V 7195 2400 50  0000 C CNN
F 1 "12.4k" V 7286 2400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7440 2390 50  0001 C CNN
F 3 "~" H 7400 2400 50  0001 C CNN
	1    7400 2400
	0    1    1    0   
$EndComp
$Comp
L power:-10V #PWR0115
U 1 1 615E33A4
P 7100 2400
F 0 "#PWR0115" H 7100 2500 50  0001 C CNN
F 1 "-10V" V 7100 2525 50  0000 L CNN
F 2 "" H 7100 2400 50  0001 C CNN
F 3 "" H 7100 2400 50  0001 C CNN
	1    7100 2400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7100 2400 7250 2400
Wire Wire Line
	7550 2400 7675 2400
Wire Wire Line
	7675 2400 7675 2100
Wire Wire Line
	7675 2100 7550 2100
Wire Wire Line
	7675 2100 7850 2100
Connection ~ 7675 2100
$Comp
L Device:R_US R10
U 1 1 615E5D2E
P 8175 2400
F 0 "R10" V 7970 2400 50  0000 C CNN
F 1 "10k" V 8061 2400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8215 2390 50  0001 C CNN
F 3 "~" H 8175 2400 50  0001 C CNN
	1    8175 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	7850 2100 7850 2400
Wire Wire Line
	7850 2400 8025 2400
Connection ~ 7850 2100
$Comp
L Device:R_US R14
U 1 1 615E6BD2
P 8600 2000
F 0 "R14" V 8395 2000 50  0000 C CNN
F 1 "1k" V 8486 2000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8640 1990 50  0001 C CNN
F 3 "~" H 8600 2000 50  0001 C CNN
	1    8600 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	8325 2400 8750 2400
Wire Wire Line
	8750 2400 8750 2000
Wire Wire Line
	8750 2000 8925 2000
Connection ~ 8750 2000
Text Label 8925 2000 0    50   ~ 0
OUT_A
$Comp
L winterbloom:OPA4197 U3
U 2 1 615EB5C5
P 8150 3000
F 0 "U3" H 8150 3367 50  0000 C CNN
F 1 "OPA4197" H 8150 3276 50  0000 C CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 8150 2650 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/opa4197.pdf" H 8200 3200 50  0001 C CNN
F 4 "OPA4197IPW" H 8150 2550 39  0001 C CNN "mpn"
	2    8150 3000
	1    0    0    -1  
$EndComp
Text Label 7100 3100 2    50   ~ 0
DAC_OUT_B
$Comp
L power:GND #PWR0116
U 1 1 615EB5D0
P 7850 2900
F 0 "#PWR0116" H 7850 2650 50  0001 C CNN
F 1 "GND" H 7855 2727 50  0001 C CNN
F 2 "" H 7850 2900 50  0001 C CNN
F 3 "" H 7850 2900 50  0001 C CNN
	1    7850 2900
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R4
U 1 1 615EB5DA
P 7400 3100
F 0 "R4" V 7195 3100 50  0000 C CNN
F 1 "1.54k" V 7286 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7440 3090 50  0001 C CNN
F 3 "~" H 7400 3100 50  0001 C CNN
	1    7400 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	7100 3100 7250 3100
$Comp
L Device:R_US R5
U 1 1 615EB5E5
P 7400 3400
F 0 "R5" V 7195 3400 50  0000 C CNN
F 1 "12.4k" V 7286 3400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7440 3390 50  0001 C CNN
F 3 "~" H 7400 3400 50  0001 C CNN
	1    7400 3400
	0    1    1    0   
$EndComp
$Comp
L power:-10V #PWR0117
U 1 1 615EB5EF
P 7100 3400
F 0 "#PWR0117" H 7100 3500 50  0001 C CNN
F 1 "-10V" V 7100 3525 50  0000 L CNN
F 2 "" H 7100 3400 50  0001 C CNN
F 3 "" H 7100 3400 50  0001 C CNN
	1    7100 3400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7100 3400 7250 3400
Wire Wire Line
	7550 3400 7675 3400
Wire Wire Line
	7675 3400 7675 3100
Wire Wire Line
	7675 3100 7550 3100
Wire Wire Line
	7675 3100 7850 3100
Connection ~ 7675 3100
$Comp
L Device:R_US R11
U 1 1 615EB5FF
P 8175 3400
F 0 "R11" V 7970 3400 50  0000 C CNN
F 1 "10k" V 8061 3400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8215 3390 50  0001 C CNN
F 3 "~" H 8175 3400 50  0001 C CNN
	1    8175 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	7850 3100 7850 3400
Wire Wire Line
	7850 3400 8025 3400
Connection ~ 7850 3100
$Comp
L Device:R_US R15
U 1 1 615EB60C
P 8600 3000
F 0 "R15" V 8395 3000 50  0000 C CNN
F 1 "1k" V 8486 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8640 2990 50  0001 C CNN
F 3 "~" H 8600 3000 50  0001 C CNN
	1    8600 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	8325 3400 8750 3400
Wire Wire Line
	8750 3400 8750 3000
Wire Wire Line
	8750 3000 8925 3000
Connection ~ 8750 3000
Text Label 8925 3000 0    50   ~ 0
OUT_B
$Comp
L winterbloom:OPA4197 U3
U 3 1 615F684D
P 8150 4075
F 0 "U3" H 8150 4442 50  0000 C CNN
F 1 "OPA4197" H 8150 4351 50  0000 C CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 8150 3725 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/opa4197.pdf" H 8200 4275 50  0001 C CNN
F 4 "OPA4197IPW" H 8150 3625 39  0001 C CNN "mpn"
	3    8150 4075
	1    0    0    -1  
$EndComp
Text Label 7100 4175 2    50   ~ 0
DAC_OUT_C
$Comp
L power:GND #PWR0118
U 1 1 615F6858
P 7850 3975
F 0 "#PWR0118" H 7850 3725 50  0001 C CNN
F 1 "GND" H 7855 3802 50  0001 C CNN
F 2 "" H 7850 3975 50  0001 C CNN
F 3 "" H 7850 3975 50  0001 C CNN
	1    7850 3975
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R6
U 1 1 615F6862
P 7400 4175
F 0 "R6" V 7195 4175 50  0000 C CNN
F 1 "1.54k" V 7286 4175 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7440 4165 50  0001 C CNN
F 3 "~" H 7400 4175 50  0001 C CNN
	1    7400 4175
	0    1    1    0   
$EndComp
Wire Wire Line
	7100 4175 7250 4175
$Comp
L Device:R_US R7
U 1 1 615F686D
P 7400 4475
F 0 "R7" V 7195 4475 50  0000 C CNN
F 1 "12.4k" V 7286 4475 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7440 4465 50  0001 C CNN
F 3 "~" H 7400 4475 50  0001 C CNN
	1    7400 4475
	0    1    1    0   
$EndComp
$Comp
L power:-10V #PWR0119
U 1 1 615F6877
P 7100 4475
F 0 "#PWR0119" H 7100 4575 50  0001 C CNN
F 1 "-10V" V 7100 4600 50  0000 L CNN
F 2 "" H 7100 4475 50  0001 C CNN
F 3 "" H 7100 4475 50  0001 C CNN
	1    7100 4475
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7100 4475 7250 4475
Wire Wire Line
	7550 4475 7675 4475
Wire Wire Line
	7675 4475 7675 4175
Wire Wire Line
	7675 4175 7550 4175
Wire Wire Line
	7675 4175 7850 4175
Connection ~ 7675 4175
$Comp
L Device:R_US R12
U 1 1 615F6887
P 8175 4475
F 0 "R12" V 7970 4475 50  0000 C CNN
F 1 "10k" V 8061 4475 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8215 4465 50  0001 C CNN
F 3 "~" H 8175 4475 50  0001 C CNN
	1    8175 4475
	0    1    1    0   
$EndComp
Wire Wire Line
	7850 4175 7850 4475
Wire Wire Line
	7850 4475 8025 4475
Connection ~ 7850 4175
$Comp
L Device:R_US R16
U 1 1 615F6894
P 8600 4075
F 0 "R16" V 8395 4075 50  0000 C CNN
F 1 "1k" V 8486 4075 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8640 4065 50  0001 C CNN
F 3 "~" H 8600 4075 50  0001 C CNN
	1    8600 4075
	0    1    1    0   
$EndComp
Wire Wire Line
	8325 4475 8750 4475
Wire Wire Line
	8750 4475 8750 4075
Wire Wire Line
	8750 4075 8925 4075
Connection ~ 8750 4075
Text Label 8925 4075 0    50   ~ 0
OUT_C
$Comp
L winterbloom:OPA4197 U3
U 4 1 615F68A4
P 8150 5075
F 0 "U3" H 8150 5442 50  0000 C CNN
F 1 "OPA4197" H 8150 5351 50  0000 C CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 8150 4725 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/opa4197.pdf" H 8200 5275 50  0001 C CNN
F 4 "OPA4197IPW" H 8150 4625 39  0001 C CNN "mpn"
	4    8150 5075
	1    0    0    -1  
$EndComp
Text Label 7100 5175 2    50   ~ 0
DAC_OUT_D
$Comp
L power:GND #PWR0120
U 1 1 615F68AF
P 7850 4975
F 0 "#PWR0120" H 7850 4725 50  0001 C CNN
F 1 "GND" H 7855 4802 50  0001 C CNN
F 2 "" H 7850 4975 50  0001 C CNN
F 3 "" H 7850 4975 50  0001 C CNN
	1    7850 4975
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R8
U 1 1 615F68B9
P 7400 5175
F 0 "R8" V 7195 5175 50  0000 C CNN
F 1 "1.54k" V 7286 5175 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7440 5165 50  0001 C CNN
F 3 "~" H 7400 5175 50  0001 C CNN
	1    7400 5175
	0    1    1    0   
$EndComp
Wire Wire Line
	7100 5175 7250 5175
$Comp
L Device:R_US R9
U 1 1 615F68C4
P 7400 5475
F 0 "R9" V 7195 5475 50  0000 C CNN
F 1 "12.4k" V 7286 5475 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7440 5465 50  0001 C CNN
F 3 "~" H 7400 5475 50  0001 C CNN
	1    7400 5475
	0    1    1    0   
$EndComp
$Comp
L power:-10V #PWR0121
U 1 1 615F68CE
P 7100 5475
F 0 "#PWR0121" H 7100 5575 50  0001 C CNN
F 1 "-10V" V 7100 5600 50  0000 L CNN
F 2 "" H 7100 5475 50  0001 C CNN
F 3 "" H 7100 5475 50  0001 C CNN
	1    7100 5475
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7100 5475 7250 5475
Wire Wire Line
	7550 5475 7675 5475
Wire Wire Line
	7675 5475 7675 5175
Wire Wire Line
	7675 5175 7550 5175
Wire Wire Line
	7675 5175 7850 5175
Connection ~ 7675 5175
$Comp
L Device:R_US R13
U 1 1 615F68DE
P 8175 5475
F 0 "R13" V 7970 5475 50  0000 C CNN
F 1 "10k" V 8061 5475 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8215 5465 50  0001 C CNN
F 3 "~" H 8175 5475 50  0001 C CNN
	1    8175 5475
	0    1    1    0   
$EndComp
Wire Wire Line
	7850 5175 7850 5475
Wire Wire Line
	7850 5475 8025 5475
Connection ~ 7850 5175
$Comp
L Device:R_US R17
U 1 1 615F68EB
P 8600 5075
F 0 "R17" V 8395 5075 50  0000 C CNN
F 1 "1k" V 8486 5075 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8640 5065 50  0001 C CNN
F 3 "~" H 8600 5075 50  0001 C CNN
	1    8600 5075
	0    1    1    0   
$EndComp
Wire Wire Line
	8325 5475 8750 5475
Wire Wire Line
	8750 5475 8750 5075
Wire Wire Line
	8750 5075 8925 5075
Connection ~ 8750 5075
Text Label 8925 5075 0    50   ~ 0
OUT_D
$Comp
L winterbloom:OPA4197 U3
U 5 1 615FBF3D
P 5500 7375
F 0 "U3" H 5730 7421 50  0000 L CNN
F 1 "OPA4197" H 5730 7330 50  0000 L CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 5500 7025 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/opa4197.pdf" H 5550 7575 50  0001 C CNN
F 4 "OPA4197IPW" H 5500 6925 39  0001 C CNN "mpn"
	5    5500 7375
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0122
U 1 1 615FD8C8
P 5400 7075
F 0 "#PWR0122" H 5400 6925 50  0001 C CNN
F 1 "+12V" H 5415 7248 50  0000 C CNN
F 2 "" H 5400 7075 50  0001 C CNN
F 3 "" H 5400 7075 50  0001 C CNN
	1    5400 7075
	1    0    0    -1  
$EndComp
$Comp
L power:-12V #PWR0123
U 1 1 615FE907
P 5400 7675
F 0 "#PWR0123" H 5400 7775 50  0001 C CNN
F 1 "-12V" H 5415 7848 50  0000 C CNN
F 2 "" H 5400 7675 50  0001 C CNN
F 3 "" H 5400 7675 50  0001 C CNN
	1    5400 7675
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR0124
U 1 1 615FF1D2
P 4400 7300
F 0 "#PWR0124" H 4400 7150 50  0001 C CNN
F 1 "+12V" H 4415 7473 50  0000 C CNN
F 2 "" H 4400 7300 50  0001 C CNN
F 3 "" H 4400 7300 50  0001 C CNN
	1    4400 7300
	1    0    0    -1  
$EndComp
$Comp
L power:-12V #PWR0125
U 1 1 615FF4F4
P 4825 7300
F 0 "#PWR0125" H 4825 7400 50  0001 C CNN
F 1 "-12V" H 4840 7473 50  0000 C CNN
F 2 "" H 4825 7300 50  0001 C CNN
F 3 "" H 4825 7300 50  0001 C CNN
	1    4825 7300
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C6
U 1 1 615FF953
P 4825 7400
F 0 "C6" H 4733 7354 50  0000 R CNN
F 1 "0.1uF" H 4733 7445 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 4825 7400 50  0001 C CNN
F 3 "~" H 4825 7400 50  0001 C CNN
	1    4825 7400
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C5
U 1 1 616000DD
P 4400 7400
F 0 "C5" H 4308 7354 50  0000 R CNN
F 1 "0.1uF" H 4308 7445 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 4400 7400 50  0001 C CNN
F 3 "~" H 4400 7400 50  0001 C CNN
	1    4400 7400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0126
U 1 1 6160152C
P 4400 7500
F 0 "#PWR0126" H 4400 7250 50  0001 C CNN
F 1 "GND" H 4405 7327 50  0001 C CNN
F 2 "" H 4400 7500 50  0001 C CNN
F 3 "" H 4400 7500 50  0001 C CNN
	1    4400 7500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 61601CA8
P 4825 7500
F 0 "#PWR0127" H 4825 7250 50  0001 C CNN
F 1 "GND" H 4830 7327 50  0001 C CNN
F 2 "" H 4825 7500 50  0001 C CNN
F 3 "" H 4825 7500 50  0001 C CNN
	1    4825 7500
	1    0    0    -1  
$EndComp
Text Notes 7150 1325 0    50   ~ 0
Amplifies 0 V - 3.3 V to -8 V to 8 V\nResolution: 4mV
Text Label 5075 5825 0    50   ~ 0
OUT_D
Text Label 5075 5725 0    50   ~ 0
OUT_C
Text Label 5075 5625 0    50   ~ 0
OUT_B
Text Label 5075 5525 0    50   ~ 0
OUT_A
$Comp
L power:+12V #PWR0128
U 1 1 61607C5E
P 4925 5300
F 0 "#PWR0128" H 4925 5150 50  0001 C CNN
F 1 "+12V" V 4925 5425 50  0000 L CNN
F 2 "" H 4925 5300 50  0001 C CNN
F 3 "" H 4925 5300 50  0001 C CNN
	1    4925 5300
	0    1    1    0   
$EndComp
$Comp
L power:-12V #PWR0129
U 1 1 61607F20
P 4925 5400
F 0 "#PWR0129" H 4925 5500 50  0001 C CNN
F 1 "-12V" V 4925 5525 50  0000 L CNN
F 2 "" H 4925 5400 50  0001 C CNN
F 3 "" H 4925 5400 50  0001 C CNN
	1    4925 5400
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR0130
U 1 1 616085B8
P 3975 5400
F 0 "#PWR0130" H 3975 5250 50  0001 C CNN
F 1 "+3.3V" V 3975 5525 50  0000 L CNN
F 2 "" H 3975 5400 50  0001 C CNN
F 3 "" H 3975 5400 50  0001 C CNN
	1    3975 5400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0132
U 1 1 61608E20
P 4925 5900
F 0 "#PWR0132" H 4925 5650 50  0001 C CNN
F 1 "GND" H 4930 5727 50  0001 C CNN
F 2 "" H 4925 5900 50  0001 C CNN
F 3 "" H 4925 5900 50  0001 C CNN
	1    4925 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0134
U 1 1 61611E04
P 3975 5300
F 0 "#PWR0134" H 3975 5050 50  0001 C CNN
F 1 "GND" H 3980 5127 50  0001 C CNN
F 2 "" H 3975 5300 50  0001 C CNN
F 3 "" H 3975 5300 50  0001 C CNN
	1    3975 5300
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x07 J1
U 1 1 6161292B
P 4175 5600
F 0 "J1" H 4175 6100 50  0000 C CNN
F 1 "Inputs" H 4175 6025 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 4175 5600 50  0001 C CNN
F 3 "~" H 4175 5600 50  0001 C CNN
	1    4175 5600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x07 J2
U 1 1 616130E0
P 4725 5600
F 0 "J2" H 4725 6100 50  0000 C CNN
F 1 "Outputs" H 4725 6025 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 4725 5600 50  0001 C CNN
F 3 "~" H 4725 5600 50  0001 C CNN
	1    4725 5600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3975 5500 3850 5500
Wire Wire Line
	3850 5500 3850 5525
Wire Wire Line
	3850 5625 3850 5600
Wire Wire Line
	3850 5600 3975 5600
Wire Wire Line
	3850 5725 3850 5700
Wire Wire Line
	3850 5700 3975 5700
Wire Wire Line
	3850 5825 3850 5800
Wire Wire Line
	3850 5800 3975 5800
Wire Wire Line
	5075 5525 5075 5500
Wire Wire Line
	5075 5500 4925 5500
Wire Wire Line
	4925 5600 5075 5600
Wire Wire Line
	5075 5600 5075 5625
Wire Wire Line
	4925 5700 5075 5700
Wire Wire Line
	5075 5700 5075 5725
Wire Wire Line
	4925 5800 5075 5800
Wire Wire Line
	5075 5800 5075 5825
$Comp
L winterbloom:LM4040-10 U1
U 1 1 6163687E
P 3200 7475
F 0 "U1" V 3154 7554 50  0000 L CNN
F 1 "LM4040-10" V 3245 7554 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3200 7275 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm4040-n.pdf" H 3200 7475 50  0001 C CIN
F 4 "LM4040DIM3-10.0/NOPB" H 3200 7675 50  0001 C CNN "mpn"
	1    3200 7475
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0135
U 1 1 616375AB
P 3200 7625
F 0 "#PWR0135" H 3200 7375 50  0001 C CNN
F 1 "GND" H 3205 7452 50  0001 C CNN
F 2 "" H 3200 7625 50  0001 C CNN
F 3 "" H 3200 7625 50  0001 C CNN
	1    3200 7625
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 616382DB
P 3200 7175
F 0 "R1" H 3132 7129 50  0000 R CNN
F 1 "270" H 3132 7220 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 3240 7165 50  0001 C CNN
F 3 "~" H 3200 7175 50  0001 C CNN
	1    3200 7175
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C4
U 1 1 6163C207
P 2800 7525
F 0 "C4" H 2708 7479 50  0000 R CNN
F 1 "0.1uF" H 2708 7570 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2800 7525 50  0001 C CNN
F 3 "~" H 2800 7525 50  0001 C CNN
	1    2800 7525
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0136
U 1 1 6163C211
P 2800 7625
F 0 "#PWR0136" H 2800 7375 50  0001 C CNN
F 1 "GND" H 2805 7452 50  0001 C CNN
F 2 "" H 2800 7625 50  0001 C CNN
F 3 "" H 2800 7625 50  0001 C CNN
	1    2800 7625
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 7325 2800 7325
Wire Wire Line
	2800 7325 2800 7425
Connection ~ 3200 7325
Wire Wire Line
	3200 7325 3725 7325
$Comp
L power:-10V #PWR0137
U 1 1 616458DE
P 3725 7325
F 0 "#PWR0137" H 3725 7425 50  0001 C CNN
F 1 "-10V" V 3725 7450 50  0000 L CNN
F 2 "" H 3725 7325 50  0001 C CNN
F 3 "" H 3725 7325 50  0001 C CNN
	1    3725 7325
	0    1    1    0   
$EndComp
$Comp
L power:-12V #PWR0138
U 1 1 6165B1B6
P 3200 7025
F 0 "#PWR0138" H 3200 7125 50  0001 C CNN
F 1 "-12V" H 3215 7198 50  0000 C CNN
F 2 "" H 3200 7025 50  0001 C CNN
F 3 "" H 3200 7025 50  0001 C CNN
	1    3200 7025
	1    0    0    -1  
$EndComp
$Comp
L winterbloom:MCP4728 U2
U 1 1 615D4BA2
P 4675 2775
F 0 "U2" H 4225 3025 50  0000 C CNN
F 1 "MCP4728" H 5000 2425 50  0000 C CNN
F 2 "Package_SO:MSOP-10_3x3mm_P0.5mm" H 3845 3185 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/22187E.pdf" H 4675 3025 50  0001 C CNN
F 4 "MCP4728A0T-E/UN, MCP4728A0T-I/UN" H 3865 3105 50  0001 C CNN "mpn"
	1    4675 2775
	1    0    0    -1  
$EndComp
Text Notes 7150 1425 0    50   ~ 0
TODO: Re-calculate resistors, these values are for 0-2.5v input\n
Text Label 3850 5725 2    50   ~ 0
~LDAC
Text Label 3850 5625 2    50   ~ 0
SDA
Text Label 3850 5525 2    50   ~ 0
SCL
Text Label 3850 5825 2    50   ~ 0
RDY
$Comp
L power:GND #PWR0102
U 1 1 615EFA28
P 3975 5900
F 0 "#PWR0102" H 3975 5650 50  0001 C CNN
F 1 "GND" H 3980 5727 50  0001 C CNN
F 2 "" H 3975 5900 50  0001 C CNN
F 3 "" H 3975 5900 50  0001 C CNN
	1    3975 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R18
U 1 1 615F8BD0
P 4500 3875
F 0 "R18" H 4350 3925 50  0000 C CNN
F 1 "10k" H 4350 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4540 3865 50  0001 C CNN
F 3 "~" H 4500 3875 50  0001 C CNN
	1    4500 3875
	-1   0    0    1   
$EndComp
Text Label 4500 4025 3    50   ~ 0
SCL
Text Label 4850 4025 3    50   ~ 0
SDA
$Comp
L Device:R_US R19
U 1 1 615FA656
P 4850 3875
F 0 "R19" H 4700 3925 50  0000 C CNN
F 1 "10k" H 4700 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4890 3865 50  0001 C CNN
F 3 "~" H 4850 3875 50  0001 C CNN
	1    4850 3875
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 616077F6
P 4500 3725
F 0 "#PWR?" H 4500 3575 50  0001 C CNN
F 1 "+3.3V" H 4400 3875 50  0000 L CNN
F 2 "" H 4500 3725 50  0001 C CNN
F 3 "" H 4500 3725 50  0001 C CNN
	1    4500 3725
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61608326
P 4850 3725
F 0 "#PWR?" H 4850 3575 50  0001 C CNN
F 1 "+3.3V" H 4750 3875 50  0000 L CNN
F 2 "" H 4850 3725 50  0001 C CNN
F 3 "" H 4850 3725 50  0001 C CNN
	1    4850 3725
	1    0    0    -1  
$EndComp
$EndSCHEMATC
