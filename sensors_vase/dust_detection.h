void dustDetection() {
  if (dustSensor.read_sensor_value(hm330Data, 29)) {
    Serial.println("HM330X read result failed!");
  }
  parse_result_value(hm330Data);
  parse_result(hm330Data);

  // Serial.println(">>>> ");
  // Serial.println(parse_result_value(hm330Data));
  // Serial.println(" <<<<");

  // oledMessage = "Dust detection:\nreading:\nXXXXX!";
  // oledDisplay(oledMessage);
  // ledControl(1);

  Serial.println("------------------------");
  delay(10000);
}
