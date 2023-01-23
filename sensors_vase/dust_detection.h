void dustDetection() {
  if (dustSensor.read_sensor_value(hm330Data, 29)) {
    Serial.println("HM330X read result failed!");
  }
  parse_result_value(hm330Data);
  parse_result(hm330Data);

  Serial.println(parse_result(hm330Data));
  Serial.println("------------------------");
}

void dustDetectionLE() {
  if (!dustSensorLE.readSensor()) {
    Serial.println("Failed to read HM330X");
  } else {
    Serial.print("Sensor number: ");
    Serial.print(dustSensorLE.getSensorNumber());

    Serial.println("Concentration based on CF=1 standard particlate matter (ug/m^3):");
    Serial.print("PM1.0: ");
    Serial.println(dustSensorLE.std.getPM1());
    Serial.print("PM2.5: ");
    Serial.println(dustSensorLE.std.getPM2_5());
    Serial.print("PM10: ");
    Serial.println(dustSensorLE.std.getPM10());

    Serial.println("Concentration based on atmospheric environment (ug/m^3):");
    Serial.print("PM1.0: ");
    Serial.println(dustSensorLE.atm.getPM1());
    Serial.print("PM2.5: ");
    Serial.println(dustSensorLE.atm.getPM2_5());
    Serial.print("PM10: ");
    Serial.println(dustSensorLE.atm.getPM10());

    if ((dustSensorLE.std.getPM1()          >  25)
            || (dustSensorLE.std.getPM2_5() >  50)
            || (dustSensorLE.std.getPM10()  > 100)
            || (dustSensorLE.atm.getPM1()   >  25)
            || (dustSensorLE.atm.getPM2_5() >  50)
            || (dustSensorLE.atm.getPM10()  > 100)) {
      oledMessage = "Too many\nparticles\nwas detected!!";
      oledDisplay(oledMessage);
      ledControl(3);
    } else if ((dustSensorLE.std.getPM1()   > 15)
            || (dustSensorLE.std.getPM2_5() > 25)
            || (dustSensorLE.std.getPM10()  > 50)
            || (dustSensorLE.atm.getPM1()   > 15)
            || (dustSensorLE.atm.getPM2_5() > 25)
            || (dustSensorLE.atm.getPM10()  > 50)) {
    oledMessage = "Many particles\nwas detected!!";
    oledDisplay(oledMessage);
    ledControl(3);
    } else if ((dustSensorLE.std.getPM1()   > 10)
            || (dustSensorLE.std.getPM2_5() > 20)
            || (dustSensorLE.std.getPM10()  > 35)
            || (dustSensorLE.atm.getPM1()   > 10)
            || (dustSensorLE.atm.getPM2_5() > 20)
            || (dustSensorLE.atm.getPM10()  > 35)) {
    oledMessage = "Some particles\nwas detected!";
    oledDisplay(oledMessage);
    ledControl(2);
    } else if ((dustSensorLE.std.getPM1()   >  5)
            || (dustSensorLE.std.getPM2_5() > 10)
            || (dustSensorLE.std.getPM10()  > 20)
            || (dustSensorLE.atm.getPM1()   >  5)
            || (dustSensorLE.atm.getPM2_5() > 10)
            || (dustSensorLE.atm.getPM10()  > 20)) {
    oledMessage = "Few particles\nwas detected";
    oledDisplay(oledMessage);
    ledControl(1);
    } else {
      oledMessage = "Almost none\nparticles\nwas detected";
      oledDisplay(oledMessage);
      ledControl(0);
    }

    Serial.println("------------------------");
    delay(10000);
  }
}
