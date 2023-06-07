void RESTART(String problem) {
  if (isRestart) {
    /*ESP32 will restart*/
    status = "Restart dalam 5 detik";
    status += "\nStatus : ";
    status += problem;
    printOled(status.c_str(), 0, 0, true, 5000, 2);
    ESP.restart();
  }
}
