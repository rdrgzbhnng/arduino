void testSensors() {
  if (airSensor.init() == 0) {
    Serial.println("airSensor failed!");
  }

  if (dustSensor.init() == -2) {
    Serial.println("HM330X failed!");
  }

  if (sgp_probe() == -1) {
    Serial.println("SGP failed!");
  }

  if(!bmp280.init()){
    Serial.println("Device error!");
  }

  Serial.println("Sensors okay!");
  Serial.println("------------------------");
}
