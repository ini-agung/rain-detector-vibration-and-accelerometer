void printOled(const char* status, uint8_t col, uint8_t row, bool clear, uint8_t del, uint8_t tSize) {
  if (clear) display.clearDisplay();
  display.setTextSize(tSize);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(col, row);
  display.println(F(status));
  if (del) delay(del);
}
