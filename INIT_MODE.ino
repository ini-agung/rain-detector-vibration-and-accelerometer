void initMpu() {
  if (!mpu.setup(0x68)) {
    isRestart = true;
    device = "MPU";
  }
}

void initOled() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    isRestart = true;
    device = "OLED";
  }else{
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("Press Button 1 To Select Menu"));
  }
}
