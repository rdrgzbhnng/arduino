void airQuality() {
  aqsData = airSensor.slope();

  Serial.print("Sensor value: ");
  Serial.println(airSensor.getValue());

  if (aqsData == AirQualitySensor::FORCE_SIGNAL) {
    oledMessage = "Dangerous air quality!!";
    Serial.println("Dangerous pollution!!");
    ledControl(3);
    oledDisplay(oledMessage);
  } else if (aqsData == AirQualitySensor::HIGH_POLLUTION) {
    oledMessage = "High pollution in the air";
    Serial.println("High pollution!");
    ledControl(2);
    oledDisplay(oledMessage);
  } else if (aqsData == AirQualitySensor::LOW_POLLUTION) {
    oledMessage = "Low pollution in the air";
    Serial.println("Low pollution");
    ledControl(1);
    oledDisplay(oledMessage);
  } else if (aqsData == AirQualitySensor::FRESH_AIR) {
    oledMessage = "Fresh air";
    Serial.println("Fresh air");
    ledControl(0);
    oledDisplay(oledMessage);
  }

  Serial.println("------------------------");
  delay(10000);
}
