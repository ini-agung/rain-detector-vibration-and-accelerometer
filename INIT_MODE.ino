void initOled() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    isRestart = true;
    device = "OLED";
  }else{
    printOled("OLED Success", 0, 0, true, 0, 1);
  }
}

void initMpu() {
  if (!mpu.setup(0x68)) {
    isRestart = true;
    device = "MPU";
  }else{
    printOled("MPU Success", 10, 0, false, 0, 1);
  }
}

void initWifi(){
  int row = 0;
  WiFi.begin(SSID, PASSWORD);
  status = "Connecting to";
  status += String(SSID);
  status += String(PASSWORD);
  printOled(status.c_str(), 0, 0, true, 0, 1);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    printOled(".", row+=5, 50, false, 0, 1);
    if(row>50){
      RESTART("Cannot Connect to Wifi");
    }
  }
  status = "Connected with ip";
  status += String(WiFi.localIP());
  printOled("Connected with ip", 0, 60, false, 0, 1);
  printOled(status.c_str(), 0, 70, false, 0, 1);
}
