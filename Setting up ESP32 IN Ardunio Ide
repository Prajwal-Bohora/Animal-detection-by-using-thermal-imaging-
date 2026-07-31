Step 1: Install Arduino IDE

If you haven't already:

Download and install the Arduino IDE (version 2.x is recommended).
Open Arduino IDE.




Step 2: Install the ESP32 Board Package
Open Arduino IDE.
Go to:
File → Preferences
In Additional Boards Manager URLs, paste:
'https://espressif.github.io/arduino-esp32/package_esp32_index.json'

If there's already another URL, separate them with a comma.

Click OK.



Step 3: Install ESP32 Boards
Go to:
Tools → Board → Boards Manager
Search:
ESP32
Install the package by Espressif Systems.

Wait until it finishes.



Step 4: Connect the ESP32
Connect the ESP32 to your laptop using a data USB cable (not a charge-only cable).
Windows should detect it automatically.




Step 5: Select the Correct Board

Go to:

Tools → Board

Choose:

ESP32 Dev Module

If you know your exact board model, tell me the model number.




Step 6: Select the COM Port

Go to:

Tools → Port

Select something like:

COM3
COM4
COM5

If no COM port appears, tell me.






Step 7: Test with Blink

Open:

File → Examples → 01.Basics → Blink

Change:

LED_BUILTIN

to

2

So it becomes:




Code:    ------------------------------------------------------------------
void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
}
--------------------------------------------------------------------------------------------------------
Step 8: Upload

Click the Upload (→) button.

If uploading gets stuck on:

Connecting...

Press and hold the BOOT button on the ESP32 until you see:

Writing at...

Then release it.





Step 9: Open Serial Monitor

Go to:

Tools → Serial Monitor

or press

Ctrl + Shift + M

Set the baud rate to:

115200
