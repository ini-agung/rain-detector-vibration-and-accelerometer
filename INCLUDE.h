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

#define OLED_RESET      -1
#define SCREEN_ADDRESS  0x3D /*0x3D for 128x64, 0x3C for 128x32 */
#define SCREEN_WIDTH    128 /*width, in pixels*/
#define SCREEN_HEIGHT   64  /*height, in pixels*/
#define pinSelectMode   11
#define pinEnterMode    12
#define UUID            "b28eaf0c-449b-481d-8a31-9b8b3a7f3c14"

const String ServerName = "https://cisea.bukitasam.co.id/api-iot/api/v1/iot/rain-detector/post";
const String HOST       = "https://s3.bukitasam.co.id/public/rain-detector/esp32/"+String(UUID)+"/"+String(UUID)+".ino.esp32.bin";
const int MENU_ITEM_COUNT = 7;
const char* menuItems[MENU_ITEM_COUNT] = {"Run", "Stop", "Restart", "Calibrate", "Update OTA", "SENDING", "RECONNECT WIFI"};

String device, status;
bool isCalibrate      = false;
bool isRestart        = false;
bool interrupt        = false;
bool selectMode       = false;
bool RUNMODE          = false;
bool isSendingData    = false;
bool isUpdateOta      = false;
int selectedMenuItem  = 0;
int num
float MPUbias[12];
float MPUValue[12];
float RPYEQ[12];
