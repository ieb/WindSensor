EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:WindSensor-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ArdinoMinPro U1
U 1 1 5F4604C6
P 5700 3800
F 0 "U1" H 6000 3800 60  0000 C CNN
F 1 "ArdinoMinPro" H 5700 3800 60  0000 C CNN
F 2 "Divers:ArduinoProMini" H 6000 3800 60  0001 C CNN
F 3 "" H 6000 3800 60  0001 C CNN
	1    5700 3800
	1    0    0    -1  
$EndComp
Text GLabel 2150 5750 0    60   BiDi ~ 0
SPEED
$Comp
L GND #PWR01
U 1 1 5F4616C9
P 6850 3500
F 0 "#PWR01" H 6850 3500 30  0001 C CNN
F 1 "GND" H 6850 3430 30  0001 C CNN
F 2 "" H 6850 3500 60  0001 C CNN
F 3 "" H 6850 3500 60  0001 C CNN
	1    6850 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5F4616E3
P 4300 3700
F 0 "#PWR02" H 4300 3700 30  0001 C CNN
F 1 "GND" H 4300 3630 30  0001 C CNN
F 2 "" H 4300 3700 60  0001 C CNN
F 3 "" H 4300 3700 60  0001 C CNN
	1    4300 3700
	1    0    0    -1  
$EndComp
Text GLabel 6800 3650 2    60   Output ~ 0
3v3
Text GLabel 4900 3750 0    60   BiDi ~ 0
SPEED
Text GLabel 6750 4650 2    60   BiDi ~ 0
SCL
Text GLabel 6750 4550 2    60   BiDi ~ 0
SDA
Text GLabel 4700 3950 0    60   Output ~ 0
TX
Text GLabel 4700 4050 0    60   Input ~ 0
RX
Text GLabel 4700 4150 0    60   Output ~ 0
DE
Text GLabel 9850 3600 2    60   Input ~ 0
TX
Text GLabel 9850 3500 2    60   Output ~ 0
RX
Text GLabel 9850 3400 2    60   Input ~ 0
DE
Text GLabel 6950 3350 2    60   Input ~ 0
RAWV
Text Notes 8000 5100 0    60   ~ 0
Case Mounted
NoConn ~ 5000 3550
NoConn ~ 6500 3550
NoConn ~ 6500 3750
NoConn ~ 6500 3850
NoConn ~ 6500 3950
NoConn ~ 6500 4050
NoConn ~ 6500 4150
NoConn ~ 6500 4250
NoConn ~ 6500 4350
NoConn ~ 5000 4350
NoConn ~ 5000 4550
NoConn ~ 5000 4650
NoConn ~ 6500 4450
$Comp
L JDY40 U3
U 1 1 5FC74A6C
P 9100 3450
F 0 "U3" H 9150 3300 60  0000 C CNN
F 1 "JDY40" H 9150 3450 60  0000 C CNN
F 2 "Divers:JDY-40" H 8950 3400 60  0001 C CNN
F 3 "" H 8950 3400 60  0001 C CNN
	1    9100 3450
	1    0    0    -1  
$EndComp
NoConn ~ 8500 3000
NoConn ~ 8500 3100
NoConn ~ 8500 3300
NoConn ~ 8500 3200
NoConn ~ 8500 3400
NoConn ~ 8500 3500
NoConn ~ 8500 3600
NoConn ~ 8500 3700
Text GLabel 9850 3700 2    60   Input ~ 0
3v3
$Comp
L GND #PWR03
U 1 1 5FC75544
P 10250 3300
F 0 "#PWR03" H 10250 3300 30  0001 C CNN
F 1 "GND" H 10250 3230 30  0001 C CNN
F 2 "" H 10250 3300 60  0001 C CNN
F 3 "" H 10250 3300 60  0001 C CNN
	1    10250 3300
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5FCB270F
P 4600 2250
F 0 "C2" H 4600 2350 40  0000 L CNN
F 1 "10nF" H 4606 2165 40  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_5x5.8" H 4638 2100 30  0001 C CNN
F 3 "" H 4600 2250 60  0000 C CNN
	1    4600 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5FCB2926
P 4050 2750
F 0 "#PWR04" H 4050 2750 30  0001 C CNN
F 1 "GND" H 4050 2680 30  0001 C CNN
F 2 "" H 4050 2750 60  0001 C CNN
F 3 "" H 4050 2750 60  0001 C CNN
	1    4050 2750
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P2
U 1 1 5FCB2DB4
P 3150 2550
F 0 "P2" H 3230 2550 40  0000 L CNN
F 1 "0V" H 3150 2605 30  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm_SMD_Pin1Left" H 3150 2550 60  0001 C CNN
F 3 "" H 3150 2550 60  0001 C CNN
	1    3150 2550
	-1   0    0    1   
$EndComp
$Comp
L CONN_1 P3
U 1 1 5FCB2E64
P 6300 5250
F 0 "P3" H 6380 5250 40  0000 L CNN
F 1 "3v3" H 6300 5305 30  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm_SMD_Pin1Left" H 6300 5250 60  0001 C CNN
F 3 "" H 6300 5250 60  0001 C CNN
	1    6300 5250
	1    0    0    -1  
$EndComp
Text Notes 6550 5600 0    60   ~ 0
Connects to AS5600 i2C device\nwith 10nF Cap between GND and V3v3\nSee data sheet
Text Notes 8700 2850 0    60   ~ 0
2.4GHz Radio Interface
Text Notes 3700 1700 0    60   ~ 0
Power In
Text GLabel 4850 1900 2    60   Output ~ 0
RAWV
Text Notes 2900 1750 0    60   ~ 0
16V-11V in
Text Notes 4750 1800 0    60   ~ 0
16V-11V
$Comp
L GND #PWR05
U 1 1 5FCE4E58
P 5700 5100
F 0 "#PWR05" H 5700 5100 30  0001 C CNN
F 1 "GND" H 5700 5030 30  0001 C CNN
F 2 "" H 5700 5100 60  0001 C CNN
F 3 "" H 5700 5100 60  0001 C CNN
	1    5700 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5FCE4E8A
P 6350 2950
F 0 "#PWR06" H 6350 2950 30  0001 C CNN
F 1 "GND" H 6350 2880 30  0001 C CNN
F 2 "" H 6350 2950 60  0001 C CNN
F 3 "" H 6350 2950 60  0001 C CNN
	1    6350 2950
	1    0    0    -1  
$EndComp
NoConn ~ 5550 2950
NoConn ~ 5650 2950
NoConn ~ 5750 2950
NoConn ~ 5850 2950
$Comp
L CONN_1 P1
U 1 1 5FCE5DF1
P 2800 5100
F 0 "P1" H 2880 5100 40  0000 L CNN
F 1 "SP" H 2800 5155 30  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm_SMD_Pin1Left" H 2800 5100 60  0001 C CNN
F 3 "" H 2800 5100 60  0001 C CNN
	1    2800 5100
	0    -1   -1   0   
$EndComp
$Comp
L CONN_1 P4
U 1 1 5FCE66DA
P 2900 1900
F 0 "P4" H 2980 1900 40  0000 L CNN
F 1 "SP" H 2900 1955 30  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm_SMD_Pin1Left" H 2900 1900 60  0001 C CNN
F 3 "" H 2900 1900 60  0001 C CNN
	1    2900 1900
	-1   0    0    1   
$EndComp
NoConn ~ 5000 4450
NoConn ~ 10450 2450
$Comp
L C C1
U 1 1 5FCF365C
P 4300 2250
F 0 "C1" H 4300 2350 40  0000 L CNN
F 1 "10nF" H 4306 2165 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4338 2100 30  0001 C CNN
F 3 "" H 4300 2250 60  0000 C CNN
	1    4300 2250
	1    0    0    -1  
$EndComp
Text GLabel 5750 5550 0    60   BiDi ~ 0
SDA
Text GLabel 5750 5700 0    60   BiDi ~ 0
SCL
$Comp
L CONN_1 P5
U 1 1 5FCF3996
P 6150 5550
F 0 "P5" H 6230 5550 40  0000 L CNN
F 1 "SDA" H 6150 5605 30  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm_SMD_Pin1Left" H 6150 5550 60  0001 C CNN
F 3 "" H 6150 5550 60  0001 C CNN
	1    6150 5550
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P6
U 1 1 5FCF39C7
P 6150 5700
F 0 "P6" H 6230 5700 40  0000 L CNN
F 1 "SCL" H 6150 5755 30  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm_SMD_Pin1Left" H 6150 5700 60  0001 C CNN
F 3 "" H 6150 5700 60  0001 C CNN
	1    6150 5700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5FCF3D37
P 5600 6050
F 0 "#PWR07" H 5600 6050 30  0001 C CNN
F 1 "GND" H 5600 5980 30  0001 C CNN
F 2 "" H 5600 6050 60  0001 C CNN
F 3 "" H 5600 6050 60  0001 C CNN
	1    5600 6050
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P9
U 1 1 5FCF3D60
P 6150 5950
F 0 "P9" H 6230 5950 40  0000 L CNN
F 1 "GND" H 6150 6005 30  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm_SMD_Pin1Left" H 6150 5950 60  0001 C CNN
F 3 "" H 6150 5950 60  0001 C CNN
	1    6150 5950
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P7
U 1 1 5FCF3E5D
P 2500 5100
F 0 "P7" H 2580 5100 40  0000 L CNN
F 1 "5V" H 2500 5155 30  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm_SMD_Pin1Left" H 2500 5100 60  0001 C CNN
F 3 "" H 2500 5100 60  0001 C CNN
	1    2500 5100
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR08
U 1 1 5FCF3F31
P 1750 5700
F 0 "#PWR08" H 1750 5700 30  0001 C CNN
F 1 "GND" H 1750 5630 30  0001 C CNN
F 2 "" H 1750 5700 60  0001 C CNN
F 3 "" H 1750 5700 60  0001 C CNN
	1    1750 5700
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P8
U 1 1 5FCF3F60
P 2650 5100
F 0 "P8" H 2730 5100 40  0000 L CNN
F 1 "GND" H 2650 5155 30  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm_SMD_Pin1Left" H 2650 5100 60  0001 C CNN
F 3 "" H 2650 5100 60  0001 C CNN
	1    2650 5100
	0    -1   -1   0   
$EndComp
NoConn ~ 5000 3450
NoConn ~ 5000 3350
$Comp
L AS5600 U2
U 1 1 5FE9996D
P 2300 4300
F 0 "U2" H 2300 4300 60  0000 C CNN
F 1 "AS5600" H 2350 4600 60  0000 C CNN
F 2 "SMD_Packages:SOIC-8-N" H 2300 4300 60  0001 C CNN
F 3 "" H 2300 4300 60  0001 C CNN
	1    2300 4300
	1    0    0    -1  
$EndComp
Text GLabel 3350 4650 2    60   BiDi ~ 0
SDA
Text GLabel 3350 4500 2    60   BiDi ~ 0
SCL
NoConn ~ 1700 4250
NoConn ~ 2900 4400
$Comp
L C C3
U 1 1 5FE99E5F
P 1100 4300
F 0 "C3" H 1100 4400 40  0000 L CNN
F 1 "100nF" H 1106 4215 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1138 4150 30  0001 C CNN
F 3 "" H 1100 4300 60  0000 C CNN
	1    1100 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5FE99F11
P 1100 4800
F 0 "#PWR09" H 1100 4800 30  0001 C CNN
F 1 "GND" H 1100 4730 30  0001 C CNN
F 2 "" H 1100 4800 60  0001 C CNN
F 3 "" H 1100 4800 60  0001 C CNN
	1    1100 4800
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5FE9A09C
P 3250 3600
F 0 "R2" V 3330 3600 40  0000 C CNN
F 1 "4K7" V 3257 3601 40  0000 C CNN
F 2 "Capacitors_SMD:C_0805" V 3180 3600 30  0001 C CNN
F 3 "" H 3250 3600 30  0000 C CNN
	1    3250 3600
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5FE9A16A
P 3100 3600
F 0 "R1" V 3180 3600 40  0000 C CNN
F 1 "4K7" V 3107 3601 40  0000 C CNN
F 2 "Capacitors_SMD:C_0805" V 3030 3600 30  0001 C CNN
F 3 "" H 3100 3600 30  0000 C CNN
	1    3100 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5FE9A1F6
P 3800 4000
F 0 "#PWR010" H 3800 4000 30  0001 C CNN
F 1 "GND" H 3800 3930 30  0001 C CNN
F 2 "" H 3800 4000 60  0001 C CNN
F 3 "" H 3800 4000 60  0001 C CNN
	1    3800 4000
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P10
U 1 1 5FE9A696
P 650 3950
F 0 "P10" H 730 3950 40  0000 L CNN
F 1 "3v3" H 650 4005 30  0001 C CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 650 3950 60  0001 C CNN
F 3 "" H 650 3950 60  0001 C CNN
	1    650  3950
	-1   0    0    1   
$EndComp
$Comp
L CONN_1 P12
U 1 1 5FE9A6A0
P 3500 4100
F 0 "P12" H 3580 4100 40  0000 L CNN
F 1 "SDA" H 3500 4155 30  0001 C CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 3500 4100 60  0001 C CNN
F 3 "" H 3500 4100 60  0001 C CNN
	1    3500 4100
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P13
U 1 1 5FE9A6A6
P 3500 4250
F 0 "P13" H 3580 4250 40  0000 L CNN
F 1 "SCL" H 3500 4305 30  0001 C CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 3500 4250 60  0001 C CNN
F 3 "" H 3500 4250 60  0001 C CNN
	1    3500 4250
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P11
U 1 1 5FE9A6B4
P 650 4650
F 0 "P11" H 730 4650 40  0000 L CNN
F 1 "GND" H 650 4705 30  0001 C CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 650 4650 60  0001 C CNN
F 3 "" H 650 4650 60  0001 C CNN
	1    650  4650
	-1   0    0    1   
$EndComp
Wire Wire Line
	6500 3450 6850 3450
Wire Wire Line
	6850 3450 6850 3500
Wire Wire Line
	4300 3650 5000 3650
Wire Wire Line
	6800 3650 6500 3650
Wire Wire Line
	5000 3750 4900 3750
Wire Wire Line
	4300 3650 4300 3700
Wire Wire Line
	6750 4550 6500 4550
Wire Wire Line
	6500 4650 6750 4650
Wire Wire Line
	9700 3500 9850 3500
Wire Wire Line
	9700 3600 9850 3600
Wire Wire Line
	9700 3300 9850 3300
Wire Wire Line
	9850 3400 9700 3400
Wire Wire Line
	9850 3700 9700 3700
Wire Wire Line
	10250 3200 10250 3300
Wire Wire Line
	6500 3350 6950 3350
Wire Wire Line
	4600 2600 4600 2450
Wire Wire Line
	4050 2600 4600 2600
Wire Wire Line
	4050 2550 4050 2750
Wire Wire Line
	4300 2450 4300 2600
Connection ~ 4300 2600
Wire Wire Line
	3050 1900 4850 1900
Wire Wire Line
	4600 1900 4600 2050
Wire Wire Line
	4300 2050 4300 1900
Connection ~ 4300 1900
Wire Wire Line
	3300 2550 4050 2550
Connection ~ 4050 2600
Wire Wire Line
	6150 5250 6000 5250
Connection ~ 4600 1900
Wire Wire Line
	6050 2950 6050 2850
Wire Wire Line
	5950 2850 6350 2850
Wire Wire Line
	6350 2850 6350 2950
Wire Wire Line
	5950 2850 5950 2950
Connection ~ 6050 2850
Wire Wire Line
	5700 4950 5700 5100
Wire Wire Line
	2150 5750 2950 5750
Wire Wire Line
	4700 4150 5000 4150
Wire Wire Line
	5750 5550 6000 5550
Wire Wire Line
	5750 5700 6000 5700
Wire Wire Line
	5600 6050 5600 5950
Wire Wire Line
	5600 5950 6000 5950
Wire Wire Line
	2150 5450 2950 5450
Wire Wire Line
	1750 5600 2950 5600
Wire Wire Line
	1750 5600 1750 5700
Wire Wire Line
	5000 4050 4700 4050
Wire Wire Line
	5000 3950 4700 3950
Wire Wire Line
	800  3950 1700 3950
Wire Wire Line
	1550 3950 1550 4100
Wire Wire Line
	1550 4100 1700 4100
Wire Wire Line
	1700 4400 1450 4400
Wire Wire Line
	1450 4400 1450 4650
Wire Wire Line
	1450 4650 800  4650
Wire Wire Line
	1100 4500 1100 4800
Connection ~ 1100 4650
Connection ~ 1550 3950
Wire Wire Line
	1100 4100 1100 3950
Connection ~ 1100 3950
Wire Wire Line
	2900 3950 3800 3950
Wire Wire Line
	3800 3950 3800 4000
Wire Wire Line
	2900 4100 3350 4100
Wire Wire Line
	2900 4250 3350 4250
Wire Wire Line
	3100 3850 3100 4650
Connection ~ 3100 4250
Wire Wire Line
	3250 3850 3250 4500
Connection ~ 3250 4100
Wire Wire Line
	3250 3250 3250 3350
Wire Wire Line
	1400 3250 3250 3250
Wire Wire Line
	1400 3250 1400 3950
Connection ~ 1400 3950
Wire Wire Line
	3100 3350 3100 3250
Connection ~ 3100 3250
Wire Wire Line
	950  3700 1050 3700
Wire Wire Line
	1050 3700 1050 3950
Connection ~ 1050 3950
Wire Wire Line
	3250 4500 3350 4500
Wire Wire Line
	3100 4650 3350 4650
Text GLabel 4700 3850 0    60   Output ~ 0
SENSOR_EN
Wire Wire Line
	4700 3850 5000 3850
Text GLabel 6000 5250 0    60   Input ~ 0
SENSOR_EN
Text GLabel 950  3700 0    60   Input ~ 0
SENSOR_EN
Wire Wire Line
	9700 3200 10250 3200
Text GLabel 9850 3300 2    60   Input ~ 0
RFEN
Text GLabel 4700 4250 0    60   Output ~ 0
RFEN
Wire Wire Line
	5000 4250 4700 4250
Text GLabel 2150 5450 0    60   Input ~ 0
SENSOR_EN
$Comp
L 3144 U?
U 1 1 603DF19B
P 3450 5750
F 0 "U?" H 3500 5950 60  0000 C CNN
F 1 "S451A Hall Device" H 3550 6300 60  0000 C CNN
F 2 "" H 3450 5750 60  0001 C CNN
F 3 "" H 3450 5750 60  0001 C CNN
	1    3450 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 5250 2800 5750
Connection ~ 2800 5750
Wire Wire Line
	2650 5250 2650 5600
Connection ~ 2650 5600
Wire Wire Line
	2500 5250 2500 5450
Connection ~ 2500 5450
$EndSCHEMATC
