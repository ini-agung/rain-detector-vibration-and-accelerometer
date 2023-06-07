#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MPU9250.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <EEPROM.h>
#include <Update.h>
#include "time.h"
#include <ArduinoJson.h>


#define OLED_RESET            -1
#define SCREEN_ADDRESS        0x3D /*0x3D for 128x64, 0x3C for 128x32 */
#define SCREEN_WIDTH          128 /*width, in pixels*/
#define SCREEN_HEIGHT         64   /*height, in pixels*/
#define pinSelectMode         11
#define pinEnterMode          12
#define UUID                  "b28eaf0c-449b-481d-8a31-9b8b3a7f3c14"

String ServerName           = "https://cisea.bukitasam.co.id/api-iot/api/v1/iot/rain-detector/post";
String HostOta              = "https://s3.bukitasam.co.id/public/rain-detector/esp32/"+String(UUID)+"/"+String(UUID)+".ino.esp32.bin";
const char* SSID            = "Rain-Detector-Vibration";
const char* PASSWORD        = "@RDV2023_";
const char* ntpServer       = "pool.ntp.org";
const long  gmtOffset_sec   = 0;
const int   daylightOffset_sec          = 3600;
const int MENU_ITEM_COUNT   = 8;
const char* menuItems[MENU_ITEM_COUNT]  =  {"Run", "Stop", "Restart", "Calibrate", "Update OTA", "SENDING", "RECONNECT WIFI", "READ_ALL_SENSOR"};

String device, status, timestamp;
bool isCalibrate      = false;
bool isRestart        = false;
bool interrupt        = false;
bool selectMode       = false;
bool RUNMODE          = false;
bool isSendingData    = false;
bool isUpdateOta      = false;
bool isPrintData      = false;
int selectedMenuItem  = 0;
int numSending        = 0;
int totalLength       = 0;
int currentLength     = 0;
float MPUbias[12];
float MPUValue[12];
float RPYEQ[12];
double GPS[2];


/*
data = 


*/
