void UPDATEOTA() {
  isUpdateOta = false;
  if(isUpdateOta){
    printOled("Connecting to \nHost Ota", 0, 0, true, 0, 1);
    client.begin(HostOta);
    int response = client.GET();
    if(response == 200){
      printOled("Connected \n Start to Download", 0, 20, false, 0, 1);
      totalLength = client.getSize();
      int len = totalLength;
      Update.begin(UPDATE_SIZE_UNKNOWN);

    }else{
      printOled("Failed to Connected", 0, 20, false, 0, 1);
    }
  }
}

void TimeNTP() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  char fullTime[20];
  strftime(fullTime, sizeof(fullTime), "%Y-%m-%d %H:%M:%S", &timeinfo);
  timestamp =  String(fullTime);
}