#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SPI.h>
//#include <SD.h>

#include <Wire.h>
#include "Adafruit_HTU21DF.h"

#include "password.h"

// Special char 'ms2', 33x21px
// http://javl.github.io/image2cpp/
const PROGMEM  uint8_t mssymbol[]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
0x02, 0x00, 0x00, 0x27, 0x1c, 0x02, 0x1e, 0x00, 0x3f, 0xbe, 0x06, 0x7f, 0x00, 0x31, 0xe3, 0x04,
0x61, 0x00, 0x30, 0xc3, 0x04, 0x60, 0x00, 0x20, 0xc3, 0x0c, 0x38, 0x00, 0x20, 0xc3, 0x08, 0x0f,
0x00, 0x20, 0xc3, 0x08, 0x01, 0x00, 0x20, 0xc3, 0x18, 0x43, 0x00, 0x20, 0xc3, 0x18, 0x7f, 0x00,
0x20, 0xc3, 0x10, 0x3e, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#include <TM1637Display.h>
#include "Adafruit_GFX.h"
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeMonoBoldOblique9pt7b.h>

#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <ESP8266HTTPClient.h>

#include <time.h>
#include <TimeLib.h>
time_t t;

// OTA
#include <ArduinoOTA.h>

#define DEBUG 1

void mqttreconnect();
void readTemp();
void readWind();
void otafunk();
void drawTft();
void weathercheck();
void readhtu();

/* KMR-1.8 TFT. Uses SPI.
Pin 1 down below at "KMR".
1 - Gnd
2 - Vcc
3 - NC
4 - NC
5 - NC
6 - Reset. Can be connected to Wemos Rst. 
7 - A0. = DC. 
8 - SDA/MOSI. Not used? D7
9 - SCL/SCLK. Not used? D5
10 - CS. 
11 - SCK. Not used.
12 - Miso. Not used.
13 - Mosi. Not used.
14 - SD_CS
15 - Backlight +
16 - Backlight -
*/
#define TFT_DC D8   // display pin 7 (A0 = DC) D2 = Gpio 4
#define TFT_CS D0   // display pin 10 (CS) (Was D0)
//#define TFT_RST D0  // display pin 6 (RESET)  D0 = 16
#define TFT_RST -1  // display pin 6 (RESET) // Set to -1 and connect to Arduino/Wemos RESET pin

//#define SD_CS D4    // display pin 14

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// TM1637 connections. Uses a I2C-like communication.
#define CLK 0 //D3
#define DIO 12 //D6
// Init display object, add data 
TM1637Display display(CLK, DIO);
uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };

/* HTU21D
Hardware I2C Wemos:
    SDA => D2.
    SCL => D1
*/
Adafruit_HTU21DF htudev = Adafruit_HTU21DF();
float htutemp, htuhum;
//int ihtutemp, ihtuhum;
char chtutemp[5];
char chtuhum[5];

// Timer
#include <elapsedMillis.h>
elapsedMillis sinceLast=60000;

const char* password = "";
int status = WL_IDLE_STATUS;    
char ssid[] = "NETGEAR83";      
char key[] = "no";       // your network key
int keyIndex = 0;  

// Settings for the Mqtt broker:
#define MQTT_USERNAME "emonpi"     
#define MQTT_PASSWORD "emonpimqtt2016"  
const char* mqtt_server = "192.168.1.79";
char* mqtt_value_topic = "emonled_Esp/values";
char* mqtt_debug_topic = "emonled_Esp/debug";
char* mqtt_tempin_topic = "Rflink/DKW2012";
char* mqtt_indoorsensor_topic = "Rflink/Alecto V2";

char* mqtt_ha_topic = "HomeAssistant";
char* mqtt_time_topic = "time";

// Note - change #define MQTT_MAX_PACKET_SIZE to 250 in PubSubClient.h
// https://pubsubclient.knolleary.net/api.html

const char compile_date[] = __DATE__ " " __TIME__;
#define appname "Emonled181230"
bool displayState=true;
const char* outdoortemp;
const char* outdoorhum="-";
const char* indoortemp="---";
const char* indoorhumidity="-";
const char* winddir;
const char* airpressure;
int outdoorwind, wd;
String winddirs[50] = {"N","NNO", "NO", "ONO", "O", "OSO", "SO", "SSO", "S", "SSV", "SV", "VSV", "V", "VNV", "NV", "NNV"};    

int h1, h2, m1, m2;
//float tempNow;

// OTA
#include <ArduinoOTA.h>

// Json
#include <ArduinoJson.h>

// Mqtt
#include <PubSubClient.h>
//JsonObject& root = jsonBuffer.createObject();

WiFiClient espClient;
PubSubClient client(espClient);
char msg[150];
const size_t bufferSize = JSON_OBJECT_SIZE(12) + 140;
DynamicJsonBuffer jsonBuffer(bufferSize);

void setup() {
  Serial.begin(115200);
  Serial.print("Welcome to ");
  Serial.println(appname);

  // TM1637 LED
  display.setBrightness(0x0f);      // 0-7d
  /*
  data[0] = display.encodeDigit(0);
  data[1] = display.encodeDigit(1);
  data[2] = display.encodeDigit(2);
  data[3] = display.encodeDigit(3);
  display.setSegments(data);
  */

  //  void showNumberDecEx(int num, uint8_t dots = 0, bool leading_zero = false, uint8_t length = 4, uint8_t pos = 0);
  display.showNumberDecEx(1234, 0b01000000, false, 4, 0);
  
  // ST7735 TFT
  tft.initR(INITR_GREENTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_GREEN); // Green on black
  tft.setTextSize(2);
  tft.setRotation(2);
  tft.setCursor(2,35); // x,y
  tft.print("Connecting...");
  
  // Wifi, code from WifiManagerAutoConnect example
  WiFiManager wifiManager;
  wifiManager.autoConnect(appname);
  WiFi.hostname("Emonled");
  Serial.print("Connected to Wifi with IP ");
  Serial.println(WiFi.localIP());

  // Setup Mqtt connection
  client.setServer(mqtt_server, 1883);
  if (!client.connected()) {
      mqttreconnect();
  }
  client.setCallback(callback);
  client.publish(mqtt_debug_topic, "Emonled started");

  otafunk();
  
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_RED); // Green on black
  tft.setCursor(2,20); // x,y    
  tft.setTextSize(2);
  tft.print("Waiting for data.");

/*
  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
  }
*/

  if (!htudev.begin()) {
    Serial.println("Couldn't find sensor!");
    //while (1);
  }

  readTemp();
}

void loop() {
  ArduinoOTA.handle();

  if (sinceLast > 60000)  // 30s
  //if (sinceLast > 10000)
  {      
    Serial.println("Timeout");
    sinceLast = 0;
    
    // Read temp
    readTemp();  
    readWind();
    readPressure();
    readhtu();
    drawTft();
    //weathercheck();

    // Publish values from local sensor

    StaticJsonBuffer<150> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    char msg[30];
    root["temp"] = chtutemp;
    root["humidity"] = chtuhum;
    root.printTo((char*)msg, root.measureLength() + 1);
    client.publish(mqtt_value_topic, msg, true);  // Send with retain=true

    
   }
  
  // Mqtt
  if (!client.connected()) {
    mqttreconnect();
  }
  client.loop();

}
