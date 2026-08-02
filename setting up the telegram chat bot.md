1. Open telegram and search ' BotFather ' and then click start
2. then after you receive a response type /newbot and send
3. then you are asked to chose the chatbot name such as (Animal Alert Bot)
4. then you are asked to choose the username such as (animal_alert_nepal_bot)
5. you will receive the token such as (987493274972394:hdhdhf***********)
6. then the work is in the browser
7. Open this link in your browser:

https://api.telegram.org/botYOUR_BOT_TOKEN/getUpdates

Replace:

YOUR_BOT_TOKEN

with your actual token.

Example:

https://api.telegram.org/bot123456:ABCXYZ/getUpdates

You should see something similar to:

{
 "ok":true,
 "result":[
   {
     "message":{
       "chat":{
         "id":987654321,
         "first_name":"Prajwal"
       }
     }
   }
 ]
}

Your Chat ID is:

987654321

8.In Arduino IDE:

Sketch → Include Library → Manage Libraries

Install:

UniversalTelegramBot

Also install:

ArduinoJson


9.Step 1: Include Libraries
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>


Step 2: Enter Your Wi-Fi
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";


Step 3: Enter Bot Token
#define BOT_TOKEN "1234567890:AAHkxxxxxxxxxxxxxxxx"


Step 4: Enter Chat ID
String CHAT_ID = "987654321";
