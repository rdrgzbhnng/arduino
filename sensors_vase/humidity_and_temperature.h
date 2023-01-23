void humidityAndTemperature() {

  dhtHumidity = dht.readHumidity();
  dhtTemperature = dht.readTemperature();
  dhtHic = dht.computeHeatIndex(dhtTemperature, dhtHumidity, false);

  if (isnan(dhtHumidity) || isnan(dhtTemperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(dhtHumidity);
  Serial.println(F("%"));

  Serial.print(F("Temperature: "));
  Serial.print(dhtTemperature);
  Serial.println(F("°C"));

  Serial.print(F("Heat index: "));
  Serial.print(dhtHic);
  Serial.println(F("°C"));

  if (dhtHic > 40) {
    Serial.println("Dangerously hot");
    oledMessage = "Dangerously hot";
    ledControl(2);
  } else if (dhtHic > 30) {
    Serial.println("pretty hot");
    oledMessage = "pretty hot";
    ledControl(2);
  } else if (dhtHic > 25) {
    Serial.println("Open doors and windows");
    oledMessage = "Open doors and\nwindows";
    ledControl(2);
  } else if (dhtHic < 15) {
    Serial.println("Try turning up the heat");
    oledMessage = "Try turning up\nthe heat";
    ledControl(2);
  } else if (dhtHic < 5) {
    Serial.println("Too cold");
    oledMessage = "Too cold";
    ledControl(2);
  } else {
    Serial.println("Nice tempeture");
    oledMessage = "Nice tempeture";
    ledControl(0);
  }

  oledDisplay(oledMessage);
  Serial.println("------------------------");
  delay(10000);
}
