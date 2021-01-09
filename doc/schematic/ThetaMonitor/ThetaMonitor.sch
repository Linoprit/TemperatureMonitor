EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ThetaMonitor"
Date "2021-01-08"
Rev "V2.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L YAAJ_BluePill_Part_Like:YAAJ_BluePill_Part_Like U2
U 1 1 5FF89F25
P 9150 2000
F 0 "U2" H 9150 3165 50  0000 C CNN
F 1 "YAAJ_BluePill_Part_Like" H 9150 3074 50  0000 C CNN
F 2 "" H 9850 1000 50  0001 C CNN
F 3 "" H 9850 1000 50  0001 C CNN
	1    9150 2000
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AMS1117-3.3 U3
U 1 1 5FF914B5
P 9150 5550
F 0 "U3" H 9150 5792 50  0000 C CNN
F 1 "AMS1117-3.3" H 9150 5701 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 9150 5750 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 9250 5300 50  0001 C CNN
	1    9150 5550
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x04_Odd_Even J11
U 1 1 5FF97A12
P 5950 4250
F 0 "J11" H 6000 4567 50  0000 C CNN
F 1 "NRF24" H 6000 4476 50  0000 C CNN
F 2 "" H 5950 4250 50  0001 C CNN
F 3 "~" H 5950 4250 50  0001 C CNN
	1    5950 4250
	1    0    0    -1  
$EndComp
$Comp
L Memory_EEPROM:CAT24C256 U1
U 1 1 5FF9F23E
P 5550 6300
F 0 "U1" H 5000 6750 50  0000 C CNN
F 1 "CAT24C256" H 5150 6650 50  0000 C CNN
F 2 "" H 5550 6300 50  0001 C CNN
F 3 "https://www.onsemi.cn/PowerSolutions/document/CAT24C256-D.PDF" H 5550 6300 50  0001 C CNN
	1    5550 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR031
U 1 1 5FFB9920
P 2300 5300
F 0 "#PWR031" H 2300 5050 50  0001 C CNN
F 1 "GND" H 2305 5127 50  0000 C CNN
F 2 "" H 2300 5300 50  0001 C CNN
F 3 "" H 2300 5300 50  0001 C CNN
	1    2300 5300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR021
U 1 1 5FFB9ED6
P 3250 3850
F 0 "#PWR021" H 3250 3700 50  0001 C CNN
F 1 "+3.3V" H 3265 4023 50  0000 C CNN
F 2 "" H 3250 3850 50  0001 C CNN
F 3 "" H 3250 3850 50  0001 C CNN
	1    3250 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR020
U 1 1 5FFBA70D
P 2300 3850
F 0 "#PWR020" H 2300 3700 50  0001 C CNN
F 1 "+5V" H 2315 4023 50  0000 C CNN
F 2 "" H 2300 3850 50  0001 C CNN
F 3 "" H 2300 3850 50  0001 C CNN
	1    2300 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR030
U 1 1 5FFBD8DB
P 1800 5300
F 0 "#PWR030" H 1800 5050 50  0001 C CNN
F 1 "GND" H 1805 5127 50  0000 C CNN
F 2 "" H 1800 5300 50  0001 C CNN
F 3 "" H 1800 5300 50  0001 C CNN
	1    1800 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR032
U 1 1 5FFBDD19
P 3250 5300
F 0 "#PWR032" H 3250 5050 50  0001 C CNN
F 1 "GND" H 3255 5127 50  0000 C CNN
F 2 "" H 3250 5300 50  0001 C CNN
F 3 "" H 3250 5300 50  0001 C CNN
	1    3250 5300
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC817 Q2
U 1 1 5FFBE04E
P 3150 5000
F 0 "Q2" H 3341 5046 50  0000 L CNN
F 1 "BC817" H 3341 4955 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3350 4925 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC817.pdf" H 3150 5000 50  0001 L CNN
	1    3150 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5FFC7F1B
P 3250 4100
F 0 "R6" H 3320 4146 50  0000 L CNN
F 1 "4.7k" H 3320 4055 50  0000 L CNN
F 2 "" V 3180 4100 50  0001 C CNN
F 3 "~" H 3250 4100 50  0001 C CNN
	1    3250 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5FFC8279
P 2800 4850
F 0 "R8" H 2870 4896 50  0000 L CNN
F 1 "47k" H 2870 4805 50  0000 L CNN
F 2 "" V 2730 4850 50  0001 C CNN
F 3 "~" H 2800 4850 50  0001 C CNN
	1    2800 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 3850 2300 3950
Wire Wire Line
	2300 4350 2300 4550
Wire Wire Line
	3250 4250 3250 4350
Wire Wire Line
	2300 4550 2800 4550
Wire Wire Line
	2800 4550 2800 4700
Connection ~ 2300 4550
$Comp
L Connector_Generic:Conn_01x03 J7
U 1 1 5FFCBA83
P 4150 4550
F 0 "J7" H 4150 4300 50  0000 C CNN
F 1 "1-Wire CH1" V 4300 4600 50  0000 C CNN
F 2 "" H 4150 4550 50  0001 C CNN
F 3 "~" H 4150 4550 50  0001 C CNN
	1    4150 4550
	1    0    0    1   
$EndComp
Wire Wire Line
	2800 4550 3950 4550
Connection ~ 2800 4550
Wire Wire Line
	2800 5000 2950 5000
Wire Wire Line
	3250 5200 3250 5300
Wire Wire Line
	3250 3950 3250 3850
Text HLabel 1050 4350 0    50   Output ~ 0
CH1_RX
Wire Wire Line
	3250 4350 2300 4350
Connection ~ 3250 4350
Wire Wire Line
	3250 4350 3250 4800
Connection ~ 2300 4350
Wire Wire Line
	2300 4350 1050 4350
Wire Wire Line
	1050 4800 1350 4800
Text HLabel 1050 4800 0    50   Input ~ 0
CH1_TX
Wire Wire Line
	1800 5200 1800 5300
Wire Wire Line
	1800 4800 2000 4800
Connection ~ 1800 4800
Wire Wire Line
	1800 4900 1800 4800
Wire Wire Line
	1650 4800 1800 4800
Wire Wire Line
	2300 5000 2300 5300
Wire Wire Line
	2300 4550 2300 4600
$Comp
L Device:R R7
U 1 1 5FFBFE18
P 1500 4800
F 0 "R7" V 1293 4800 50  0000 C CNN
F 1 "47k" V 1384 4800 50  0000 C CNN
F 2 "" V 1430 4800 50  0001 C CNN
F 3 "~" H 1500 4800 50  0001 C CNN
	1    1500 4800
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4148 D1
U 1 1 5FFBAEDF
P 1800 5050
F 0 "D1" V 1800 4800 50  0000 L CNN
F 1 "1N4148" V 1900 4650 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1800 4875 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1800 5050 50  0001 C CNN
	1    1800 5050
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:BC817 Q1
U 1 1 5FF90287
P 2200 4800
F 0 "Q1" H 2391 4846 50  0000 L CNN
F 1 "BC817" H 2391 4755 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2400 4725 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC817.pdf" H 2200 4800 50  0001 L CNN
	1    2200 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5FFF32C2
P 2300 4100
F 0 "R5" H 2370 4146 50  0000 L CNN
F 1 "4.7k" H 2370 4055 50  0000 L CNN
F 2 "" V 2230 4100 50  0001 C CNN
F 3 "~" H 2300 4100 50  0001 C CNN
	1    2300 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 4250 2300 4350
$Comp
L power:GND #PWR025
U 1 1 5FFFFFCD
P 3850 4800
F 0 "#PWR025" H 3850 4550 50  0001 C CNN
F 1 "GND" H 3855 4627 50  0000 C CNN
F 2 "" H 3850 4800 50  0001 C CNN
F 3 "" H 3850 4800 50  0001 C CNN
	1    3850 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 4800 3850 4650
Wire Wire Line
	3850 4650 3950 4650
$Comp
L power:+5V #PWR022
U 1 1 6000148F
P 3850 4250
F 0 "#PWR022" H 3850 4100 50  0001 C CNN
F 1 "+5V" H 3865 4423 50  0000 C CNN
F 2 "" H 3850 4250 50  0001 C CNN
F 3 "" H 3850 4250 50  0001 C CNN
	1    3850 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 4450 3850 4450
Wire Wire Line
	3850 4450 3850 4250
$Comp
L power:GND #PWR040
U 1 1 6002B032
P 2300 7450
F 0 "#PWR040" H 2300 7200 50  0001 C CNN
F 1 "GND" H 2305 7277 50  0000 C CNN
F 2 "" H 2300 7450 50  0001 C CNN
F 3 "" H 2300 7450 50  0001 C CNN
	1    2300 7450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR034
U 1 1 6002B03C
P 3250 6000
F 0 "#PWR034" H 3250 5850 50  0001 C CNN
F 1 "+3.3V" H 3265 6173 50  0000 C CNN
F 2 "" H 3250 6000 50  0001 C CNN
F 3 "" H 3250 6000 50  0001 C CNN
	1    3250 6000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR033
U 1 1 6002B046
P 2300 6000
F 0 "#PWR033" H 2300 5850 50  0001 C CNN
F 1 "+5V" H 2315 6173 50  0000 C CNN
F 2 "" H 2300 6000 50  0001 C CNN
F 3 "" H 2300 6000 50  0001 C CNN
	1    2300 6000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR039
U 1 1 6002B050
P 1800 7450
F 0 "#PWR039" H 1800 7200 50  0001 C CNN
F 1 "GND" H 1805 7277 50  0000 C CNN
F 2 "" H 1800 7450 50  0001 C CNN
F 3 "" H 1800 7450 50  0001 C CNN
	1    1800 7450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR041
U 1 1 6002B05A
P 3250 7450
F 0 "#PWR041" H 3250 7200 50  0001 C CNN
F 1 "GND" H 3255 7277 50  0000 C CNN
F 2 "" H 3250 7450 50  0001 C CNN
F 3 "" H 3250 7450 50  0001 C CNN
	1    3250 7450
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC817 Q4
U 1 1 6002B064
P 3150 7150
F 0 "Q4" H 3341 7196 50  0000 L CNN
F 1 "BC817" H 3341 7105 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3350 7075 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC817.pdf" H 3150 7150 50  0001 L CNN
	1    3150 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 6002B06E
P 3250 6250
F 0 "R10" H 3320 6296 50  0000 L CNN
F 1 "4.7k" H 3320 6205 50  0000 L CNN
F 2 "" V 3180 6250 50  0001 C CNN
F 3 "~" H 3250 6250 50  0001 C CNN
	1    3250 6250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 6002B078
P 2800 7000
F 0 "R12" H 2870 7046 50  0000 L CNN
F 1 "47k" H 2870 6955 50  0000 L CNN
F 2 "" V 2730 7000 50  0001 C CNN
F 3 "~" H 2800 7000 50  0001 C CNN
	1    2800 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 6000 2300 6100
Wire Wire Line
	2300 6500 2300 6700
Wire Wire Line
	3250 6400 3250 6500
Wire Wire Line
	2300 6700 2800 6700
Wire Wire Line
	2800 6700 2800 6850
Connection ~ 2300 6700
$Comp
L Connector_Generic:Conn_01x03 J10
U 1 1 6002B088
P 4150 6700
F 0 "J10" H 4150 6450 50  0000 C CNN
F 1 "1-Wire CH2" V 4300 6750 50  0000 C CNN
F 2 "" H 4150 6700 50  0001 C CNN
F 3 "~" H 4150 6700 50  0001 C CNN
	1    4150 6700
	1    0    0    1   
$EndComp
Wire Wire Line
	2800 6700 3950 6700
Connection ~ 2800 6700
Wire Wire Line
	2800 7150 2950 7150
Wire Wire Line
	3250 7350 3250 7450
Wire Wire Line
	3250 6100 3250 6000
Text HLabel 1050 6500 0    50   Output ~ 0
CH2_RX
Wire Wire Line
	3250 6500 2300 6500
Connection ~ 3250 6500
Wire Wire Line
	3250 6500 3250 6950
Connection ~ 2300 6500
Wire Wire Line
	2300 6500 1050 6500
Wire Wire Line
	1050 6950 1350 6950
Text HLabel 1050 6950 0    50   Input ~ 0
CH2_TX
Wire Wire Line
	1800 7350 1800 7450
Wire Wire Line
	1800 6950 2000 6950
Connection ~ 1800 6950
Wire Wire Line
	1800 7050 1800 6950
Wire Wire Line
	1650 6950 1800 6950
Wire Wire Line
	2300 7150 2300 7450
Wire Wire Line
	2300 6700 2300 6750
$Comp
L Device:R R11
U 1 1 6002B0A6
P 1500 6950
F 0 "R11" V 1293 6950 50  0000 C CNN
F 1 "47k" V 1384 6950 50  0000 C CNN
F 2 "" V 1430 6950 50  0001 C CNN
F 3 "~" H 1500 6950 50  0001 C CNN
	1    1500 6950
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4148 D2
U 1 1 6002B0B0
P 1800 7200
F 0 "D2" V 1800 6950 50  0000 L CNN
F 1 "1N4148" V 1900 6800 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1800 7025 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1800 7200 50  0001 C CNN
	1    1800 7200
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:BC817 Q3
U 1 1 6002B0BA
P 2200 6950
F 0 "Q3" H 2391 6996 50  0000 L CNN
F 1 "BC817" H 2391 6905 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2400 6875 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC817.pdf" H 2200 6950 50  0001 L CNN
	1    2200 6950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 6002B0C4
P 2300 6250
F 0 "R9" H 2370 6296 50  0000 L CNN
F 1 "4.7k" H 2370 6205 50  0000 L CNN
F 2 "" V 2230 6250 50  0001 C CNN
F 3 "~" H 2300 6250 50  0001 C CNN
	1    2300 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 6400 2300 6500
$Comp
L power:GND #PWR038
U 1 1 6002B0CF
P 3850 6950
F 0 "#PWR038" H 3850 6700 50  0001 C CNN
F 1 "GND" H 3855 6777 50  0000 C CNN
F 2 "" H 3850 6950 50  0001 C CNN
F 3 "" H 3850 6950 50  0001 C CNN
	1    3850 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 6950 3850 6800
Wire Wire Line
	3850 6800 3950 6800
$Comp
L power:+5V #PWR035
U 1 1 6002B0DB
P 3850 6400
F 0 "#PWR035" H 3850 6250 50  0001 C CNN
F 1 "+5V" H 3865 6573 50  0000 C CNN
F 2 "" H 3850 6400 50  0001 C CNN
F 3 "" H 3850 6400 50  0001 C CNN
	1    3850 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 6600 3850 6600
Wire Wire Line
	3850 6600 3850 6400
Text HLabel 7850 2000 0    50   Input ~ 0
CH2_RX
Text HLabel 7850 2100 0    50   Output ~ 0
CH2_TX
Wire Wire Line
	7850 2000 8350 2000
Wire Wire Line
	7850 2100 8350 2100
Text Notes 700  6100 0    50   ~ 0
Both signals are inverted.\nUse an inverter-chip, \nlike 7400 NAND, or \n7408 NOR, if needed.
Text HLabel 10450 1600 2    50   Input ~ 0
BME280_SCL
Text HLabel 10450 1500 2    50   Input ~ 0
BME280_SDA
Wire Wire Line
	10450 1600 9950 1600
Wire Wire Line
	10450 1500 9950 1500
$Comp
L power:GND #PWR019
U 1 1 600C7AC3
P 2850 3050
F 0 "#PWR019" H 2850 2800 50  0001 C CNN
F 1 "GND" H 2855 2877 50  0000 C CNN
F 2 "" H 2850 3050 50  0001 C CNN
F 3 "" H 2850 3050 50  0001 C CNN
	1    2850 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 3050 2850 2900
Wire Wire Line
	2850 2900 2950 2900
$Comp
L power:+3.3V #PWR012
U 1 1 600CEB6D
P 2850 2450
F 0 "#PWR012" H 2850 2300 50  0001 C CNN
F 1 "+3.3V" H 2865 2623 50  0000 C CNN
F 2 "" H 2850 2450 50  0001 C CNN
F 3 "" H 2850 2450 50  0001 C CNN
	1    2850 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 2600 2850 2450
$Comp
L power:+3.3V #PWR010
U 1 1 600E85D4
P 2200 2250
F 0 "#PWR010" H 2200 2100 50  0001 C CNN
F 1 "+3.3V" H 2215 2423 50  0000 C CNN
F 2 "" H 2200 2250 50  0001 C CNN
F 3 "" H 2200 2250 50  0001 C CNN
	1    2200 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 600E85DE
P 2200 2500
F 0 "R3" H 2270 2546 50  0000 L CNN
F 1 "4.7k" H 2270 2455 50  0000 L CNN
F 2 "" V 2130 2500 50  0001 C CNN
F 3 "~" H 2200 2500 50  0001 C CNN
	1    2200 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2350 2200 2300
Wire Wire Line
	2200 2650 2200 2800
Text Notes 600  2000 0    50   ~ 0
BMP280 Sensors
Text Notes 600  3550 0    50   ~ 0
DS18x20 Tempsensors
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 60121747
P 2000 1200
F 0 "J1" H 1950 1350 50  0000 L CNN
F 1 "Button" V 2150 1050 50  0000 L CNN
F 2 "" H 2000 1200 50  0001 C CNN
F 3 "~" H 2000 1200 50  0001 C CNN
	1    2000 1200
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 6013B3CF
P 1050 1400
F 0 "#PWR04" H 1050 1150 50  0001 C CNN
F 1 "GND" H 1055 1227 50  0000 C CNN
F 2 "" H 1050 1400 50  0001 C CNN
F 3 "" H 1050 1400 50  0001 C CNN
	1    1050 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 1400 1350 1400
Wire Wire Line
	1800 1200 1700 1200
Text HLabel 1100 1100 0    50   Output ~ 0
Pushbutton
Wire Wire Line
	1800 1100 1350 1100
$Comp
L Device:C C1
U 1 1 6014F0B4
P 1350 1250
F 0 "C1" H 1465 1296 50  0000 L CNN
F 1 "100n" H 1465 1205 50  0000 L CNN
F 2 "" H 1388 1100 50  0001 C CNN
F 3 "~" H 1350 1250 50  0001 C CNN
	1    1350 1250
	1    0    0    -1  
$EndComp
Connection ~ 1350 1100
Wire Wire Line
	1350 1100 1100 1100
Wire Wire Line
	1700 1200 1700 1400
Connection ~ 1350 1400
Wire Wire Line
	1350 1400 1700 1400
Text Notes 650  650  0    50   ~ 0
Pushbutton
Text HLabel 7850 1900 0    50   Input ~ 0
Pushbutton
Wire Wire Line
	7850 1900 8350 1900
Text HLabel 7850 1600 0    50   Output ~ 0
Debug_TX
Text HLabel 7850 1700 0    50   Input ~ 0
Debug_RX
Wire Wire Line
	7850 1600 8350 1600
Wire Wire Line
	7850 1700 8350 1700
Text HLabel 8100 4000 0    50   Input ~ 0
Debug_TX
Text HLabel 8100 4100 0    50   Output ~ 0
Debug_RX
Wire Wire Line
	8100 4000 8600 4000
Wire Wire Line
	8100 4100 8600 4100
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 6019AB99
P 8800 4100
F 0 "J3" H 8800 3850 50  0000 C CNN
F 1 "Debug" V 8950 4100 50  0000 C CNN
F 2 "" H 8800 4100 50  0001 C CNN
F 3 "~" H 8800 4100 50  0001 C CNN
	1    8800 4100
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 6019E5EF
P 8500 4350
F 0 "#PWR016" H 8500 4100 50  0001 C CNN
F 1 "GND" H 8505 4177 50  0000 C CNN
F 2 "" H 8500 4350 50  0001 C CNN
F 3 "" H 8500 4350 50  0001 C CNN
	1    8500 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4350 8500 4200
Wire Wire Line
	8500 4200 8600 4200
Text Notes 7500 3650 0    50   ~ 0
Serial Debug\nUSART_1
Text HLabel 9900 4000 0    50   Input ~ 0
RASP_TX
Text HLabel 9900 4100 0    50   Output ~ 0
RASP_RX
Wire Wire Line
	9900 4000 10400 4000
Wire Wire Line
	9900 4100 10400 4100
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 601C7154
P 10600 4100
F 0 "J4" H 10600 3850 50  0000 C CNN
F 1 "Raspi" V 10750 4100 50  0000 C CNN
F 2 "" H 10600 4100 50  0001 C CNN
F 3 "~" H 10600 4100 50  0001 C CNN
	1    10600 4100
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR017
U 1 1 601C715E
P 10300 4350
F 0 "#PWR017" H 10300 4100 50  0001 C CNN
F 1 "GND" H 10305 4177 50  0000 C CNN
F 2 "" H 10300 4350 50  0001 C CNN
F 3 "" H 10300 4350 50  0001 C CNN
	1    10300 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 4350 10300 4200
Wire Wire Line
	10300 4200 10400 4200
Text Notes 9500 3650 0    50   ~ 0
Raspi_Connection\nUSART_2
$Comp
L Connector_Generic:Conn_01x02 J8
U 1 1 601E72E8
P 10600 5650
F 0 "J8" H 10600 5400 50  0000 C CNN
F 1 "Power" V 10750 5600 50  0000 C CNN
F 2 "" H 10600 5650 50  0001 C CNN
F 3 "~" H 10600 5650 50  0001 C CNN
	1    10600 5650
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR027
U 1 1 6020E977
P 10250 5800
F 0 "#PWR027" H 10250 5550 50  0001 C CNN
F 1 "GND" H 10255 5627 50  0000 C CNN
F 2 "" H 10250 5800 50  0001 C CNN
F 3 "" H 10250 5800 50  0001 C CNN
	1    10250 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 5800 10250 5650
Wire Wire Line
	10400 5650 10250 5650
$Comp
L power:GND #PWR029
U 1 1 6021E0B3
P 9150 6150
F 0 "#PWR029" H 9150 5900 50  0001 C CNN
F 1 "GND" H 9155 5977 50  0000 C CNN
F 2 "" H 9150 6150 50  0001 C CNN
F 3 "" H 9150 6150 50  0001 C CNN
	1    9150 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 6150 9150 6000
Wire Wire Line
	9450 5550 9650 5550
$Comp
L power:+3.3V #PWR023
U 1 1 6022C144
P 8050 5400
F 0 "#PWR023" H 8050 5250 50  0001 C CNN
F 1 "+3.3V" H 8065 5573 50  0000 C CNN
F 2 "" H 8050 5400 50  0001 C CNN
F 3 "" H 8050 5400 50  0001 C CNN
	1    8050 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR024
U 1 1 6022C14E
P 10250 5450
F 0 "#PWR024" H 10250 5300 50  0001 C CNN
F 1 "+5V" H 10265 5623 50  0000 C CNN
F 2 "" H 10250 5450 50  0001 C CNN
F 3 "" H 10250 5450 50  0001 C CNN
	1    10250 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 5450 10250 5550
Connection ~ 10250 5550
Wire Wire Line
	10250 5550 10400 5550
Wire Wire Line
	8850 5550 8550 5550
Wire Wire Line
	8050 5400 8050 5550
$Comp
L Device:C C3
U 1 1 6026F83F
P 8550 5850
F 0 "C3" H 8665 5896 50  0000 L CNN
F 1 "100n" H 8665 5805 50  0000 L CNN
F 2 "" H 8588 5700 50  0001 C CNN
F 3 "~" H 8550 5850 50  0001 C CNN
	1    8550 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 602859C3
P 9650 5850
F 0 "C4" H 9765 5896 50  0000 L CNN
F 1 "100n" H 9765 5805 50  0000 L CNN
F 2 "" H 9688 5700 50  0001 C CNN
F 3 "~" H 9650 5850 50  0001 C CNN
	1    9650 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 602869D6
P 8050 5850
F 0 "C2" H 8168 5896 50  0000 L CNN
F 1 "10u" H 8168 5805 50  0000 L CNN
F 2 "" H 8088 5700 50  0001 C CNN
F 3 "~" H 8050 5850 50  0001 C CNN
	1    8050 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 5700 9650 5550
Connection ~ 9650 5550
Wire Wire Line
	9650 5550 10250 5550
Wire Wire Line
	9650 6000 9150 6000
Connection ~ 9150 6000
Wire Wire Line
	9150 6000 9150 5850
Wire Wire Line
	9150 6000 8550 6000
Wire Wire Line
	8050 6000 8550 6000
Connection ~ 8550 6000
Wire Wire Line
	8050 5700 8050 5550
Connection ~ 8050 5550
Wire Wire Line
	8550 5700 8550 5550
Connection ~ 8550 5550
Wire Wire Line
	8550 5550 8050 5550
Text Notes 7550 5000 0    50   ~ 0
3.3V Supply. Regulated 5V input required.
$Comp
L Connector_Generic:Conn_01x08 J9
U 1 1 602C44B2
P 6550 1500
F 0 "J9" H 6500 950 50  0000 L CNN
F 1 "LCD_Nokia_5110" V 6700 1200 50  0000 L CNN
F 2 "" H 6550 1500 50  0001 C CNN
F 3 "~" H 6550 1500 50  0001 C CNN
	1    6550 1500
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR028
U 1 1 602D3682
P 4850 1950
F 0 "#PWR028" H 4850 1700 50  0001 C CNN
F 1 "GND" H 4855 1777 50  0000 C CNN
F 2 "" H 4850 1950 50  0001 C CNN
F 3 "" H 4850 1950 50  0001 C CNN
	1    4850 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1950 4850 1800
Wire Wire Line
	4850 1800 6350 1800
$Comp
L power:+3.3V #PWR026
U 1 1 602E35A1
P 4850 1550
F 0 "#PWR026" H 4850 1400 50  0001 C CNN
F 1 "+3.3V" H 4865 1723 50  0000 C CNN
F 2 "" H 4850 1550 50  0001 C CNN
F 3 "" H 4850 1550 50  0001 C CNN
	1    4850 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1550 4850 1700
Wire Wire Line
	6350 1700 4850 1700
Text HLabel 5650 1100 0    50   Input ~ 0
LED_BKG
Wire Wire Line
	5650 1100 6350 1100
Text HLabel 5650 1200 0    50   Input ~ 0
LCD_Reset
Wire Wire Line
	5650 1200 6350 1200
Text HLabel 5650 1300 0    50   Input ~ 0
LCD_MOSI
Wire Wire Line
	5650 1300 6350 1300
Text HLabel 5650 1400 0    50   Input ~ 0
LCD_DatCmd
Wire Wire Line
	5650 1400 6350 1400
Text HLabel 5650 1600 0    50   Input ~ 0
LED_CE
Wire Wire Line
	5650 1500 6350 1500
Text HLabel 5650 1500 0    50   Input ~ 0
LCD_SCK
Wire Wire Line
	5650 1600 6350 1600
Text Notes 4700 700  0    50   ~ 0
LCD Nokia 5110
Text Notes 4750 2700 0    50   ~ 0
CAREFULL:\nOlder LCD-Modules draw \nmore than 10mA. \nThe newer ones have an\nintegrated transistor.
Text HLabel 7850 1800 0    50   Output ~ 0
LED_BKG
Text HLabel 7850 1500 0    50   Output ~ 0
LCD_Reset
Text HLabel 7850 1400 0    50   Output ~ 0
LCD_MOSI
Text HLabel 7850 1300 0    50   Output ~ 0
LCD_DatCmd
Text HLabel 7850 1100 0    50   Output ~ 0
LED_CE
Wire Wire Line
	7850 1800 8350 1800
Wire Wire Line
	7850 1500 8350 1500
Wire Wire Line
	7850 1400 8350 1400
Wire Wire Line
	7850 1100 8350 1100
Wire Wire Line
	7850 1300 8350 1300
Text HLabel 7850 1200 0    50   Output ~ 0
LCD_SCK
Wire Wire Line
	7850 1200 8350 1200
Text HLabel 10450 2500 2    50   Output ~ 0
NRF_CE
Text HLabel 10450 2600 2    50   Input ~ 0
NRF_IRQ
Wire Wire Line
	9950 2500 10450 2500
Wire Wire Line
	9950 2600 10450 2600
Text HLabel 10450 2100 2    50   Output ~ 0
NRF_SCK
Wire Wire Line
	9950 2100 10450 2100
Text HLabel 10450 2000 2    50   Input ~ 0
NRF_MISO
Wire Wire Line
	9950 2000 10450 2000
Text HLabel 10450 2200 2    50   Output ~ 0
NRF_CSN
Wire Wire Line
	9950 2200 10450 2200
Text HLabel 10450 1900 2    50   Output ~ 0
NRF_MOSI
Wire Wire Line
	9950 1900 10450 1900
Text HLabel 5450 4250 0    50   Input ~ 0
NRF_CE
Text HLabel 6650 4450 2    50   Output ~ 0
NRF_IRQ
Wire Wire Line
	5750 4250 5450 4250
Wire Wire Line
	6250 4450 6650 4450
Text HLabel 5450 4350 0    50   Input ~ 0
NRF_SCK
Wire Wire Line
	5750 4350 5450 4350
Text HLabel 5450 4450 0    50   Output ~ 0
NRF_MISO
Wire Wire Line
	5750 4450 5450 4450
Text HLabel 6650 4250 2    50   Input ~ 0
NRF_CSN
Wire Wire Line
	6250 4250 6650 4250
Text HLabel 6650 4350 2    50   Input ~ 0
NRF_MOSI
Wire Wire Line
	6250 4350 6650 4350
$Comp
L power:GND #PWR037
U 1 1 603DAE82
P 4850 4300
F 0 "#PWR037" H 4850 4050 50  0001 C CNN
F 1 "GND" H 4855 4127 50  0000 C CNN
F 2 "" H 4850 4300 50  0001 C CNN
F 3 "" H 4850 4300 50  0001 C CNN
	1    4850 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 4300 4850 4150
Wire Wire Line
	4850 4150 5750 4150
$Comp
L power:+3.3V #PWR036
U 1 1 603DAE8E
P 6650 4000
F 0 "#PWR036" H 6650 3850 50  0001 C CNN
F 1 "+3.3V" H 6665 4173 50  0000 C CNN
F 2 "" H 6650 4000 50  0001 C CNN
F 3 "" H 6650 4000 50  0001 C CNN
	1    6650 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 4000 6650 4150
Wire Wire Line
	6250 4150 6650 4150
Text Notes 4600 3650 0    50   ~ 0
NRF24 Connector.\nTop View
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 6046A680
P 4100 1200
F 0 "J2" H 4050 850 50  0000 C CNN
F 1 "Relay_Module" V 4250 1150 50  0000 C CNN
F 2 "" H 4100 1200 50  0001 C CNN
F 3 "~" H 4100 1200 50  0001 C CNN
	1    4100 1200
	1    0    0    1   
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 6047451D
P 2800 1100
F 0 "#PWR02" H 2800 950 50  0001 C CNN
F 1 "+5V" H 2815 1273 50  0000 C CNN
F 2 "" H 2800 1100 50  0001 C CNN
F 3 "" H 2800 1100 50  0001 C CNN
	1    2800 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 1100 2800 1200
$Comp
L power:GND #PWR06
U 1 1 6049856E
P 2800 1450
F 0 "#PWR06" H 2800 1200 50  0001 C CNN
F 1 "GND" H 2805 1277 50  0000 C CNN
F 2 "" H 2800 1450 50  0001 C CNN
F 3 "" H 2800 1450 50  0001 C CNN
	1    2800 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 1450 2800 1300
Wire Wire Line
	2800 1300 3900 1300
Wire Wire Line
	3900 1200 2800 1200
Text Notes 2600 750  0    50   ~ 0
Arduino relay board\nwith two channels.
Text HLabel 3400 1000 0    50   Input ~ 0
RELAY_1
Wire Wire Line
	3400 1000 3900 1000
Text HLabel 3400 1100 0    50   Input ~ 0
RELAY_2
Wire Wire Line
	3400 1100 3900 1100
Text HLabel 7850 2600 0    50   Output ~ 0
RELAY_1
Text HLabel 7850 2700 0    50   Output ~ 0
RELAY_2
Wire Wire Line
	7850 2700 8350 2700
Text HLabel 7850 2400 0    50   Output ~ 0
EEPROM_SCL
Text HLabel 7850 2500 0    50   Output ~ 0
EEPROM_SDA
Wire Wire Line
	7850 2400 8350 2400
Text HLabel 6550 6300 2    50   Input ~ 0
EEPROM_SCL
Text HLabel 6550 6200 2    50   Input ~ 0
EEPROM_SDA
Wire Wire Line
	6550 6300 6150 6300
Wire Wire Line
	6550 6200 6350 6200
$Comp
L power:GND #PWR08
U 1 1 6054EB14
P 5550 6850
F 0 "#PWR08" H 5550 6600 50  0001 C CNN
F 1 "GND" H 5555 6677 50  0000 C CNN
F 2 "" H 5550 6850 50  0001 C CNN
F 3 "" H 5550 6850 50  0001 C CNN
	1    5550 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 6850 5550 6700
$Comp
L power:+3.3V #PWR03
U 1 1 6054EB20
P 5550 5750
F 0 "#PWR03" H 5550 5600 50  0001 C CNN
F 1 "+3.3V" H 5565 5923 50  0000 C CNN
F 2 "" H 5550 5750 50  0001 C CNN
F 3 "" H 5550 5750 50  0001 C CNN
	1    5550 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 60576B4E
P 6150 5900
F 0 "R1" H 5900 5950 50  0000 L CNN
F 1 "4.7k" H 5900 5850 50  0000 L CNN
F 2 "" V 6080 5900 50  0001 C CNN
F 3 "~" H 6150 5900 50  0001 C CNN
	1    6150 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 6058E143
P 6350 5900
F 0 "R2" H 6420 5946 50  0000 L CNN
F 1 "4.7k" H 6420 5855 50  0000 L CNN
F 2 "" V 6280 5900 50  0001 C CNN
F 3 "~" H 6350 5900 50  0001 C CNN
	1    6350 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 6050 6150 6300
Connection ~ 6150 6300
Wire Wire Line
	6150 6300 5950 6300
Wire Wire Line
	6350 6050 6350 6200
Connection ~ 6350 6200
Wire Wire Line
	6350 6200 5950 6200
Wire Wire Line
	6350 5750 6350 5600
Wire Wire Line
	6350 5600 6150 5600
Wire Wire Line
	6150 5750 6150 5600
Wire Wire Line
	5150 6200 4950 6200
Wire Wire Line
	4950 6200 4950 6300
Wire Wire Line
	4950 6300 5150 6300
Wire Wire Line
	5150 6400 4950 6400
Wire Wire Line
	4950 6400 4950 6300
Connection ~ 4950 6300
Connection ~ 4950 6400
Wire Wire Line
	5550 5750 5550 6000
$Comp
L power:+3.3V #PWR01
U 1 1 605E463E
P 6350 5400
F 0 "#PWR01" H 6350 5250 50  0001 C CNN
F 1 "+3.3V" H 6365 5573 50  0000 C CNN
F 2 "" H 6350 5400 50  0001 C CNN
F 3 "" H 6350 5400 50  0001 C CNN
	1    6350 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 5400 6350 5600
Connection ~ 6350 5600
Wire Wire Line
	5950 6400 6100 6400
Wire Wire Line
	6100 6400 6100 6700
Wire Wire Line
	6100 6700 5550 6700
Connection ~ 5550 6700
Wire Wire Line
	5550 6700 5550 6600
Wire Wire Line
	5550 6700 4950 6700
Wire Wire Line
	4950 6700 4950 6400
Text HLabel 10450 2400 2    50   Output ~ 0
RASP_TX
Text HLabel 10450 2300 2    50   Input ~ 0
RASP_RX
Wire Wire Line
	10450 2400 9950 2400
Wire Wire Line
	10450 2300 9950 2300
NoConn ~ 9950 2700
NoConn ~ 9950 2800
NoConn ~ 9950 2900
NoConn ~ 9950 3000
$Comp
L power:+3.3V #PWR015
U 1 1 60653771
P 7550 3150
F 0 "#PWR015" H 7550 3000 50  0001 C CNN
F 1 "+3.3V" H 7750 3200 50  0000 C CNN
F 2 "" H 7550 3150 50  0001 C CNN
F 3 "" H 7550 3150 50  0001 C CNN
	1    7550 3150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR09
U 1 1 6065377B
P 7100 2700
F 0 "#PWR09" H 7100 2550 50  0001 C CNN
F 1 "+5V" H 7115 2873 50  0000 C CNN
F 2 "" H 7100 2700 50  0001 C CNN
F 3 "" H 7100 2700 50  0001 C CNN
	1    7100 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 2700 7100 2800
Wire Wire Line
	7550 3250 7550 3150
$Comp
L power:GND #PWR014
U 1 1 60676AB8
P 7100 3050
F 0 "#PWR014" H 7100 2800 50  0001 C CNN
F 1 "GND" H 7105 2877 50  0000 C CNN
F 2 "" H 7100 3050 50  0001 C CNN
F 3 "" H 7100 3050 50  0001 C CNN
	1    7100 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3050 7100 2900
NoConn ~ 9950 1400
Wire Wire Line
	7550 3250 8150 3250
Wire Wire Line
	8150 3250 8150 3000
Wire Wire Line
	8150 3000 8350 3000
Wire Wire Line
	8350 2900 7100 2900
Wire Wire Line
	7100 2800 8350 2800
$Comp
L power:GND #PWR05
U 1 1 606E0B00
P 10450 1100
F 0 "#PWR05" H 10450 850 50  0001 C CNN
F 1 "GND" H 10600 1100 50  0000 C CNN
F 2 "" H 10450 1100 50  0001 C CNN
F 3 "" H 10450 1100 50  0001 C CNN
	1    10450 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 1100 10450 950 
$Comp
L power:+3.3V #PWR07
U 1 1 606ED080
P 10800 1200
F 0 "#PWR07" H 10800 1050 50  0001 C CNN
F 1 "+3.3V" H 11000 1250 50  0000 C CNN
F 2 "" H 10800 1200 50  0001 C CNN
F 3 "" H 10800 1200 50  0001 C CNN
	1    10800 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10800 1300 10800 1200
Wire Wire Line
	9950 1300 10800 1300
Wire Wire Line
	9950 1200 10200 1200
Wire Wire Line
	10200 1200 10200 1100
Wire Wire Line
	10200 950  10450 950 
Wire Wire Line
	9950 1100 10200 1100
Connection ~ 10200 1100
Wire Wire Line
	10200 1100 10200 950 
NoConn ~ 9950 1700
NoConn ~ 9950 1800
Text Notes 4600 5000 0    50   ~ 0
EEPROM 24C256 or 24C64
Wire Wire Line
	7850 2600 8350 2600
Wire Wire Line
	7850 2500 8350 2500
Wire Wire Line
	8350 2300 7850 2300
Wire Wire Line
	8350 2200 7850 2200
Text HLabel 7850 2300 0    50   Output ~ 0
CH1_TX
Text HLabel 7850 2200 0    50   Input ~ 0
CH1_RX
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 60005EAD
P 3150 2800
F 0 "J?" H 3100 2450 50  0000 C CNN
F 1 "Relay_Module" V 3300 2750 50  0000 C CNN
F 2 "" H 3150 2800 50  0001 C CNN
F 3 "~" H 3150 2800 50  0001 C CNN
	1    3150 2800
	1    0    0    1   
$EndComp
Text HLabel 1950 2700 0    50   Output ~ 0
BME280_SCL
Text HLabel 1950 2800 0    50   Output ~ 0
BME280_SDA
Wire Wire Line
	2850 2600 2950 2600
Wire Wire Line
	1950 2700 2500 2700
Wire Wire Line
	2950 2800 2200 2800
Connection ~ 2200 2800
Wire Wire Line
	2200 2800 1950 2800
$Comp
L Device:R R?
U 1 1 600E371D
P 2500 2500
F 0 "R?" H 2570 2546 50  0000 L CNN
F 1 "4.7k" H 2570 2455 50  0000 L CNN
F 2 "" V 2430 2500 50  0001 C CNN
F 3 "~" H 2500 2500 50  0001 C CNN
	1    2500 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2650 2500 2700
Connection ~ 2500 2700
Wire Wire Line
	2500 2700 2950 2700
Wire Wire Line
	2200 2300 2500 2300
Wire Wire Line
	2500 2300 2500 2350
Connection ~ 2200 2300
Wire Wire Line
	2200 2300 2200 2250
Wire Notes Line
	6900 550  6900 3400
Wire Notes Line
	500  3400 11200 3400
Wire Notes Line
	4500 500  4500 7750
Wire Notes Line
	4500 4850 11200 4850
Wire Notes Line
	7400 3400 7400 6550
Wire Notes Line
	4500 1800 500  1800
Wire Notes Line
	2450 500  2450 1800
Text Notes 7150 750  0    50   ~ 0
STM32F103C8T6 BluePill-Board
Wire Notes Line
	9250 3400 9250 4850
$EndSCHEMATC
