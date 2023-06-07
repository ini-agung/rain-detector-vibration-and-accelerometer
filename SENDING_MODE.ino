void SENDING() {
  isSendingData = false;
  if(numSending==3){
    RESTART("Gagal Mengirim Data");
  }
  HTTPClient http;
  http.begin(serverName);
  delay(150);
  http.addHeader("Content-Type", "application/json");
  delay(150);
  String httpRequestData = data;
  int httpResponseCode = http.POST(httpRequestData);
  delay(200);
  String ret = "";
  if (httpResponseCode > 0) {
    numSending = 0;
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
    http.end();
  }else{
    numSending++;
    SENDING();
  }
  delay(1000);
}
