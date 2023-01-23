void airQuality() {
  aqsData = airSensor.slope();

  Serial.print("Sensor value: ");
  Serial.println(airSensor.getValue());

  if (aqsData == AirQualitySensor::FORCE_SIGNAL) {
    oledMessage = "Air Quality:\nDangerous!!";
    Serial.println("Dangerous pollution! ");
    ledControl(3);
  } else if (aqsData == AirQualitySensor::HIGH_POLLUTION) {
    oledMessage = "Air Quality:\nHigh pollution";
    Serial.println("High pollution");
    ledControl(2);
  } else if (aqsData == AirQualitySensor::LOW_POLLUTION) {
    oledMessage = "Air Quality:\nLow pollution";
    Serial.println("Low pollution");
    ledControl(1);
  } else if (aqsData == AirQualitySensor::FRESH_AIR) {
    oledMessage = "Air Quality:\nFresh air";
    Serial.println("Fresh air");
    ledControl(0);
  }

  oledDisplay(oledMessage);
  Serial.println("------------------------");
  delay(10000);
}
