void potentiometerSensor() {
  potentiometerData = analogRead(potentiometerPin);
  potentiometerMap = map(potentiometerData, 0, 1023, 0, 100);

  char potentiometerMessage[17];
  String str;
  str = "P value about " + String(potentiometerMap);
  str.toCharArray(potentiometerMessage,17);

  Serial.print("Potentiometer value: ");
  Serial.println(potentiometerMap);

  oledMessage = potentiometerMessage;
  oledDisplay(oledMessage);

  Serial.println("------------------------");
  delay(10000);
}
