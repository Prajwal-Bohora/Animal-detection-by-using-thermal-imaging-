#include <Wire.h>
#include <Adafruit_AMG88xx.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>

#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

//==============================
// WiFi
//==============================

const char* ssid = "              ";
const char* password = "             ";

//==============================
// Telegram
//==============================

#define BOTtoken "                     "

#define CHAT_ID "                      "

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

//==============================
// AMG8833
//==============================

Adafruit_AMG88xx amg;

float pixels[64];

//==============================
// Pins
//==============================

#define PIR_PIN 27
#define LED_PIN 25
#define BUZZER_PIN 26

#define TRIG_PIN 32
#define ECHO_PIN 33

//==============================

float thresholdTemp = 31.0;
float thresholdDistance = 200.0; // cm (2 m)

bool alreadySent = false;

//==============================

float readDistanceCM()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // 30ms timeout ~ 5m max range, avoids blocking loop() forever if no echo
  long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (duration == 0)
  {
    return -1.0; // no echo / out of range
  }

  float distanceCM = duration * 0.0343 / 2.0;
  return distanceCM;
}

//==============================

void setup()
{

Serial.begin(115200);

pinMode(PIR_PIN, INPUT);

pinMode(LED_PIN, OUTPUT);

pinMode(BUZZER_PIN, OUTPUT);

pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);

digitalWrite(LED_PIN, LOW);

digitalWrite(BUZZER_PIN, LOW);

digitalWrite(TRIG_PIN, LOW);

//------------------------------

Wire.begin(21,22);

if(!amg.begin())
{
Serial.println("AMG8833 NOT FOUND!");

while(1);
}

Serial.println("AMG8833 OK");

//------------------------------

WiFi.begin(ssid,password);

Serial.print("Connecting WiFi");

while(WiFi.status()!=WL_CONNECTED)
{
delay(500);
Serial.print(".");
}

Serial.println();

Serial.println("WiFi Connected");

client.setInsecure();

bot.sendMessage(CHAT_ID,"ESP32 Animal Detection System Started","");
}

//=================================================

void loop()
{

bool motion = digitalRead(PIR_PIN);

amg.readPixels(pixels);

float distance = readDistanceCM();

//------------------------------------------
// Send 64 temperatures to Python
//------------------------------------------

for(int i=0;i<64;i++)
{
Serial.print(pixels[i]);

if(i<63)
Serial.print(",");
}

Serial.println();

//------------------------------------------
// Find hottest pixel
//------------------------------------------

float hottest = pixels[0];

for(int i=1;i<64;i++)
{

if(pixels[i]>hottest)
{
hottest=pixels[i];
}

}

//------------------------------------------
// Distance check
//------------------------------------------

bool objectClose = (distance > 0 && distance <= thresholdDistance);

//------------------------------------------

if(motion && hottest>thresholdTemp && objectClose)
{

digitalWrite(LED_PIN,HIGH);

digitalWrite(BUZZER_PIN,HIGH);

if(!alreadySent)
{

String msg="⚠ Motion Detected!\n";
msg+="Warm Object Found\n";
msg+="Max Temp: ";
msg+=String(hottest);
msg+=" C\n";
msg+="Distance: ";
msg+=String(distance);
msg+=" cm";

bot.sendMessage(CHAT_ID,msg,"");

alreadySent=true;

}

}
else
{

digitalWrite(LED_PIN,LOW);

digitalWrite(BUZZER_PIN,LOW);

alreadySent=false;

}

delay(100);

}
