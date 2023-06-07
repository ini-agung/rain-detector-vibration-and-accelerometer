void CALIBRATE() {
  if (isCalibrate) {
    isCalibrate = false;

    status = "KALIBRASI MULAI";
    printOled(status.c_str(), 0, 10, true, 2000, 2);
    status = "LETAKKAN ALAT PADA \nALAS YANG RATA";
    printOled(status.c_str(), 0, 20, false, 2000, 1);
    mpu.verbose(true);
    delay(5000);
    mpu.calibrateAccelGyro();

    status = "GERAKKAN ALAT MEMBENTUK \n ANGKA 8";
    printOled(status.c_str(), 0, 30, false, 2000, 1);
    delay(5000);
    mpu.calibrateMag();
    mpu.verbose(false);
    delay(1000);
    MPUbias[0] = mpu.getAccBiasX() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY;
    MPUbias[1] = mpu.getAccBiasY() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY;
    MPUbias[2] = mpu.getAccBiasZ() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY;
    MPUbias[3] = mpu.getGyroBiasX() / (float)MPU9250::CALIB_GYRO_SENSITIVITY;
    MPUbias[4] = mpu.getGyroBiasY() / (float)MPU9250::CALIB_GYRO_SENSITIVITY;
    MPUbias[5] = mpu.getGyroBiasZ() / (float)MPU9250::CALIB_GYRO_SENSITIVITY;
    MPUbias[6] = mpu.getMagBiasX();
    MPUbias[7] = mpu.getMagBiasY();
    MPUbias[8] = mpu.getMagBiasZ();
    MPUbias[9] = mpu.getMagScaleX();
    MPUbias[10] = mpu.getMagScaleY();
    MPUbias[11] = mpu.getMagScaleZ();
    status = "Kalibrasi Selesai, Bias : \n";
    status += "Acc : (x, y, z)\n";
    status += String(MPUbias[0]) + " " + MPUbias[1] + " " + MPUbias[2];
    status += "Gyro : (x, y, z)\n";
    status += String(MPUbias[3]) + " " + MPUbias[4] + " " + MPUbias[5];
    status += "Mag : (x, y, z)\n";
    status += String(MPUbias[6]) + " " + MPUbias[7] + " " + MPUbias[8];
    status += "Scale : (x, y, z)\n";
    status += String(MPUbias[6]) + " " + MPUbias[7] + " " + MPUbias[8];
    printOled(status.c_str(), 0, 0, true, 2000, 1);
  }
}