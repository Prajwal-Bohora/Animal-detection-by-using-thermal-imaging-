Components
ESP32 DevKit
AMG8833 Thermal Camera
PIR Sensor (HC-SR501)
Active Buzzer
LED
220 Ω resistor
Breadboard
Jumper wires
USB cable
Wiring
1. AMG8833 → ESP32
AMG8833	ESP32
VIN	3.3V
GND	GND
SDA	GPIO21
SCL	GPIO22
2. PIR Sensor
PIR	ESP32
VCC	5V (VIN)
GND	GND
OUT	GPIO27
3. Active Buzzer
Buzzer	ESP32
+	GPIO26
–	GND
4. LED
LED	ESP32
Long leg (+)	GPIO25 through 220 Ω resistor
Short leg (–)	GND
5. ultrasonic sensor
 	Connections
HC-SR04	ESP32
VCC -	5V (VIN)
GND -	GND
TRIG	- GPIO 32
ECHO	- GPIO 33 (through a voltage divider)


Pin Summary
GPIO21  → AMG8833 SDA
GPIO22  → AMG8833 SCL

GPIO27  → PIR OUT

GPIO26  → Active Buzzer

GPIO25  → LED

3.3V    → AMG8833
5V(VIN) → PIR

GND      → All GNDs
Logic
Start

↓

Initialize Wi-Fi

↓

Initialize Telegram

↓

Initialize AMG8833

↓

Initialize PIR

↓

Loop forever

↓

PIR detects motion?

NO
↓

Continue monitoring

YES
↓

Read AMG8833

↓

Find highest temperature

↓

Temperature > Threshold?

NO
↓

Nothing

YES
↓

LED ON

↓

Buzzer ON

↓

Send Telegram Message

↓

Continue displaying thermal image

↓

Wait 3 seconds

↓

LED OFF

↓

Buzzer OFF

↓

Back to monitoring
