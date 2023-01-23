void gasDetection() {
  for(int x = 0 ; x < 100 ; x++) {
    mq9Data = mq9Data + analogRead(gasDetectionPin);
  }
  mq9Data = mq9Data/100.0;
 
  mq9Volt = mq9Data/1024*5.0;
  mq9RsAir = (5.0-mq9Volt)/mq9Volt;
  mq9R0 = mq9RsAir/9.9;
 
  Serial.print("Sensor volt = ");
  Serial.print(mq9Volt);
  Serial.println("V");
 
  Serial.print("R0 = ");
  Serial.println(mq9R0);

  mq9Data = analogRead(A6);
  mq9Volt=(float)mq9Data/1024*5.0;
  mq9RsGas = (5.0-mq9Volt)/mq9Volt;
 
  mq9GasRatio = mq9RsGas/mq9R0;
 
  Serial.print("Sensor volt = ");
  Serial.print(mq9Volt);
  Serial.println("V");
  Serial.print("RS ratio = ");
  Serial.println(mq9RsGas);
  Serial.print("RS/R0 = ");
  Serial.println(mq9GasRatio);

  if (mq9RsGas > 300) {
    Serial.println("Gas has been detected in the air");
    oledMessage = "Gas was detected!!";
    ledControl(3);
    oledDisplay(oledMessage);
  } else {
    Serial.println("No gas has been detected");
    oledMessage = "No gas detected";
    ledControl(0);
    oledDisplay(oledMessage);
  }

  Serial.println("------------------------");
  delay(10000);
}
