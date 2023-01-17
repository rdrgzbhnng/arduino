HM330XErrorCode print_result(const char* hm330Str, uint16_t value) {
  if (NULL == hm330Str) {
    return ERROR_PARAM;
  }
  Serial.print(hm330Str);
  Serial.println(value);
  return NO_ERROR;
}

HM330XErrorCode parse_result(uint8_t* data) {
  uint16_t value = 0;
  if (NULL == data) {
    return ERROR_PARAM;
  }
  for (int i = 1; i < 8; i++) {
    value = (uint16_t) data[i * 2] << 8 | data[i * 2 + 1];
    print_result(hm330Str[i - 1], value);
  }
  return NO_ERROR;
}

HM330XErrorCode parse_result_value(uint8_t* data) {
  if (NULL == data) {
    return ERROR_PARAM;
  }
  for (int i = 0; i < 28; i++) {
    Serial.print(data[i], HEX);
    Serial.print("  ");
    if ((0 == (i) % 5) || (0 == i)) {
      Serial.println("");
    }
  }
  uint8_t sum = 0;
  for (int i = 0; i < 28; i++) {
    sum += data[i];
  }
  if (sum != data[28]) {
    Serial.println("wrong checkSum!!");
  }
  Serial.println("");
  return NO_ERROR;
}
