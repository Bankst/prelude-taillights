EESchema Schematic File Version 5
EELAYER 36 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
Connection ~ 7400 4900
Connection ~ 7400 5000
Wire Wire Line
	1600 1250 7700 1250
Wire Wire Line
	3400 2950 3600 2950
Wire Wire Line
	4550 2950 4000 2950
Wire Wire Line
	7300 4800 7400 4800
Wire Wire Line
	7300 4900 7400 4900
Wire Wire Line
	7300 5000 7400 5000
Wire Wire Line
	7400 4800 7400 4900
Wire Wire Line
	7400 4900 7400 5000
Wire Wire Line
	7400 5000 7400 5100
Wire Wire Line
	7700 1250 7700 2700
Wire Wire Line
	7700 2700 7300 2700
$Comp
L ludeled-rescue:GND-power #PWR0569
U 1 1 63C52153
P 3400 2950
F 0 "#PWR0569" H 3400 2700 50  0001 C CNN
F 1 "GND" H 3405 2777 50  0000 C CNN
F 2 "" H 3400 2950 50  0001 C CNN
F 3 "" H 3400 2950 50  0001 C CNN
	1    3400 2950
	1    0    0    -1  
$EndComp
$Comp
L ludeled-rescue:GND-power #PWR0568
U 1 1 63C4E7A0
P 7400 5100
F 0 "#PWR0568" H 7400 4850 50  0001 C CNN
F 1 "GND" H 7405 4927 50  0000 C CNN
F 2 "" H 7400 5100 50  0001 C CNN
F 3 "" H 7400 5100 50  0001 C CNN
	1    7400 5100
	1    0    0    -1  
$EndComp
$Comp
L ludeled-rescue:SW_Push-Switch SW1
U 1 1 63C51508
P 3800 2950
F 0 "SW1" H 3800 3235 50  0000 C CNN
F 1 "BOOT0_SW" H 3800 3144 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_DIP_SPSTx01_Slide_6.7x4.1mm_W6.73mm_P2.54mm_LowProfile_JPin" H 3800 3150 50  0001 C CNN
F 3 "~" H 3800 3150 50  0001 C CNN
	1    3800 2950
	1    0    0    -1  
$EndComp
$Comp
L ludeled-rescue:ESP32-WROOM-32E-Espressif U1
U 1 1 63AA1055
P 5900 3500
F 0 "U1" H 5925 5315 50  0000 C CNN
F 1 "ESP32-WROOM-32E" H 5925 5224 50  0000 C CNN
F 2 "Espressif:ESP32-WROOM-32E" H 5900 1750 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32e_esp32-wroom-32ue_datasheet_en.pdf" H 6300 3500 50  0001 C CNN
	1    5900 3500
	1    0    0    -1  
$EndComp
$Sheet
S 700  750  900  550 
U 631B9534
F0 "FrontLeds" 50
F1 "front_leds.sch" 50
F2 "LED_LOWER_DIN" I R 1600 1250 50 
$EndSheet
$EndSCHEMATC
