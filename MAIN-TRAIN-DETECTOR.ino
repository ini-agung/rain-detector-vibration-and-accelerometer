#include "INCLUDE.h"

MPU9250 mpu;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
HTTPClient client;
TaskHandle_t Task1;

void IRAM_ATTR IntSelectMode() {
  selectMode = true;
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Wire.begin();
  pinMode(pinSelectMode, INPUT_PULLUP);
  attachInterrupt(pinSelectMode, IntSelectMode, RISING);

  initOled();
  initMpu();
  if (isRestart) RESTART(device);

  xTaskCreatePinnedToCore(
    Task1code,   /* Task function. */
    "Task1",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task1,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */
  delay(500);
}

void loop() {
  if (selectMode) buttonSelectMode();
  if (isSendingData) SENDING();
  if (isUpdateOta) UPDATEOTA();
}

void buttonSelectMode() {
  selectedMenuItem = (selectedMenuItem + 1) % MENU_ITEM_COUNT;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Menu:");

  for (int i = 0; i < MENU_ITEM_COUNT; i++) {
    if (i == selectedMenuItem) {
      display.print(" > ");
    } else {
      display.print("");
    }
    display.println(menuItems[i]);
    if (pinEnterMode == LOW) {
      selectMode = false;
      switch (i) {
        case 0:
          RUNMODE = true;
          break;

        case 1:
          RUNMODE = false;
          break;
          
        case 2:
          RESTART("Manual Restart");
          break;

        case 3:
          CALIBRATE();
          break;

        case 4:
          isUpdateOta = true;
          break;

        case 5:
          isSendingData = true;
          break;

        case 6:
          RESTART("Reconnect Wifi");
          break;
      }
    }
  }
}
