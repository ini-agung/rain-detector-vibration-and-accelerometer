void Task1code(void *pvParameters)
{
  Serial.print("Counter running on core ");
  Serial.println(xPortGetCoreID());
  while (true) {
    delay(100);
    if (RUNMODE) {
      static uint32_t prev_ms = millis();
      if (millis() > prev_ms + 25) {
        MPUValue[0]    = mpu.getAccX();
        MPUValue[1]    = mpu.getAccY();
        MPUValue[2]    = mpu.getAccZ();
        MPUValue[3]    = mpu.getGyroX();
        MPUValue[4]    = mpu.getGyroY();
        MPUValue[5]    = mpu.getGyroZ();
        MPUValue[6]    = mpu.getMagX();
        MPUValue[7]    = mpu.getMagY();
        MPUValue[8]    = mpu.getMagZ();
        MPUValue[9]    = mpu.getLinearAccX();
        MPUValue[10]   = mpu.getLinearAccY();
        MPUValue[11]   = mpu.getLinearAccZ();

        RPYEQ[0]       = mpu.getRoll();
        RPYEQ[1]       = mpu.getPitch();
        RPYEQ[2]       = mpu.getYaw();
        RPYEQ[3]       = mpu.getEulerX();
        RPYEQ[4]       = mpu.getEulerY();
        RPYEQ[5]       = mpu.getEulerZ();
        RPYEQ[6]       = mpu.getQuaternionX();
        RPYEQ[7]       = mpu.getQuaternionY();
        RPYEQ[8]       = mpu.getQuaternionZ();
        RPYEQ[9]       = mpu.getQuaternionW();

        status = "Accelerometer\n";
        status += String(MPUValue[0]) + " ";
        status += String(MPUValue[1]) + " ";
        status += String(MPUValue[2]) + " ";
        printOled(status.c_str(), 10, 0, false, 0, 1);
        status = "Gyroscope\n";
        status += String(MPUValue[3]) + " ";
        status += String(MPUValue[4]) + " ";
        status += String(MPUValue[5]) + " ";
        printOled(status.c_str(), 30, 0, false, 0, 1);
        status = "Magnetometer";
        status += String(MPUValue[6]) + " ";
        status += String(MPUValue[7]) + " ";
        status += String(MPUValue[8]) + " ";
        printOled(status.c_str(), 50, 0, false, 0, 1);
        status = "Linear";
        status += String(MPUValue[9]) + " ";
        status += String(MPUValue[10]) + " ";
        status += String(MPUValue[11]) + " ";
        printOled(status.c_str(), 70, 0, false, 0, 1);
      }

      static uint32_t sending = millis();
      if (millis() > sending + 15000) {
        isSendingData = true;
      }
    }
  }
}
