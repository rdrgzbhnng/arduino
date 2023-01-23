void barometerSensor() {
  Serial.print("Temperature: ");
  Serial.print(bmp280.getTemperature());
  Serial.println("C");

  Serial.print("Pressure: ");
  Serial.print(bmp280Pressure = bmp280.getPressure());
  Serial.println("Pa");

  Serial.print("Altitude: ");
  Serial.print(bmp280.calcAltitude(bmp280Pressure));
  Serial.println("m");

  if (bmp280Pressure > 102268.9) {
    Serial.println("High Pressure!!!");
    oledMessage = "Pressure:\nHigh Pressure";
    ledControl(2);
  } else if (bmp280Pressure < 100914.4) {
    Serial.println("Low Pressure!!!");
    oledMessage = "Pressure:\nLow Pressure";
    ledControl(2);
  } else {
    Serial.println("Pressure seems normal.");
    oledMessage = "Pressure:\nSeems normal";
    ledControl(0);
  }

  oledDisplay(oledMessage);
  Serial.println("------------------------");
  delay(10000);
}
