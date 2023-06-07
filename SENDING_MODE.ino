/*
* This function use to sending all values from sensor to server (ServerName)
*/
void SENDING() {
  if (isSendingData) {
    isSendingData = false;
    String data = READ_ALL_SENSOR();
    if (numSending == 3) {
      RESTART("Gagal Mengirim Data");
    }
    
    WiFiClient client;
    HTTPClient http;
    http.begin(ServerName);
    delay(150);
    http.addHeader("Content-Type", "application/json");
    delay(150);
    int httpResponseCode = http.POST(data);
    delay(150);
    printOled("Try to Sending data", 0, 0, true, 100, 1);
    if (httpResponseCode > 0) {
      numSending = 0;
      printOled("Success to Sending data", 0, 0, true, 0, 1);
      printOled(data.c_str(), 0, 10, false, 0, 1);
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
      http.end();
    } else {
      numSending++;
      initWifi();
      SENDING();
    }
  }
}

String READ_ALL_SENSOR() {
  String returnData;

  /*UUID DEVICE*/
  returnData = "[{\"UUID\":\"";
  returnData += String(UUID);

  /*ACCELEROMETER X. ACCELEROMETER Y. ACCELEROMETER Z*/
  returnData += "\", \"acc_x\":\"";
  returnData += String(MPUValue[0]);
  returnData += "\", \"acc_y\":\"";
  returnData += String(MPUValue[1]);
  returnData += "\", \"acc_z\":\"";
  returnData += String(MPUValue[2]);

  /*GYROSCOPE X. GYROSCOPE Y. GYROSCOPE Z*/
  returnData += "\", \"gyro_x\":\"";
  returnData += String(MPUValue[3]);
  returnData += "\", \"gyro_y\":\"";
  returnData += String(MPUValue[4]);
  returnData += "\", \"gyro_z\":\"";
  returnData += String(MPUValue[5]);

  /*MAGNETOMETER X. MAGNETOMETER Y. MAGNETOMETER Z*/
  returnData += "\", \"mag_x\":\"";
  returnData += String(MPUValue[6]);
  returnData += "\", \"mag_y\":\"";
  returnData += String(MPUValue[7]);
  returnData += "\", \"mag_z\":\"";
  returnData += String(MPUValue[8]);

  /*LINEAR ACCELEROMETER X. LINEAR ACCELEROMETER Y. LINEAR ACCELEROMETER Z*/
  returnData += "\", \"lin_acc_x\":\"";
  returnData += String(MPUValue[9]);
  returnData += "\", \"lin_acc_y\":\"";
  returnData += String(MPUValue[10]);
  returnData += "\", \"lin_acc_z\":\"";
  returnData += String(MPUValue[11]);

  /*ROLL. PITCH. YAW*/
  returnData += "\", \"roll\":\"";
  returnData += String(RPYEQ[0]);
  returnData += "\", \"pitch\":\"";
  returnData += String(RPYEQ[1]);
  returnData += "\", \"yaw\":\"";
  returnData += String(RPYEQ[2]);

  /*EULER X. EULER Y. EULER Z*/
  returnData += "\", \"euler_x\":\"";
  returnData += String(RPYEQ[3]);
  returnData += "\", \"euler_y\":\"";
  returnData += String(RPYEQ[4]);
  returnData += "\", \"euler_z\":\"";
  returnData += String(RPYEQ[5]);

  /*QUATERNION X. QUATERNION Y. QUATERNION Z. QUATERNION W*/
  returnData += "\", \"quat_x\":\"";
  returnData += String(RPYEQ[6]);
  returnData += "\", \"quat_y\":\"";
  returnData += String(RPYEQ[7]);
  returnData += "\", \"quat_z\":\"";
  returnData += String(RPYEQ[8]);
  returnData += "\", \"quat_w\":\"";
  returnData += String(RPYEQ[9]);

  /*GPS LATITUDE. GPS LONGITUDE*/
  returnData += "\", \"lat\":\"";
  returnData += String(GPS[0]);
  returnData += "\", \"long\":\"";
  returnData += String(GPS[1]);

  /*DATETIME*/

  returnData += "\", \"timestamp\":\"";
  returnData += timestamp;

  returnData += "\"}]";
  return returnData;
}