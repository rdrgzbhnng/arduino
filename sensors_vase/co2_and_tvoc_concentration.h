void co2AndTvocConcentration() {
  s16 err = 0;
  u16 sgp30Tvoc_ppb, sgp30Co2_eq_ppm;
  err = sgp_measure_iaq_blocking_read(&sgp30Tvoc_ppb, &sgp30Co2_eq_ppm);
  if (err == STATUS_OK) {
    Serial.print("tVOC Concentration: ");
    Serial.print(sgp30Tvoc_ppb);
    Serial.println("ppb");

    Serial.print("CO2eq Concentration: ");
    Serial.print(sgp30Co2_eq_ppm);
    Serial.println("ppm");
  } else {
    Serial.println("error reading IAQ values\n");
  }

if (sgp30Tvoc_ppb < 300) {
    Serial.println("tVOC Concentration: No objections");
    oledMessage = "tVOC\nConcentration:\nExcellent";
    ledControl(0);
  } else if (sgp30Tvoc_ppb < 1000) {
    Serial.println("tVOC Concentration: Ventilation/airing recommended");
    oledMessage = "tVOC\nConcentration:\nGood";
    ledControl(1);
  } else if (sgp30Tvoc_ppb < 3000) {
    Serial.println("tVOC Concentration: Intensified ventilation recommended");
    oledMessage = "tVOC\nConcentration:\nModerate";
    ledControl(2);
  } else if (sgp30Tvoc_ppb > 10000) {
    Serial.println("tVOC Concentration: Intensified ventilation/airing necessary");
    oledMessage = "tVOC\nConcentration:\nPoor";
    ledControl(3);
  } else {
    Serial.println("tVOC Concentration: Hazardous");
    oledMessage = "tVOC\nConcentration:\nUnhealthy";
    ledControl(3);
  } 

  oledDisplay(oledMessage);
  delay(10000);

  if (sgp30Co2_eq_ppm < 400) {
    Serial.println("Wrong CO2eq Concentration detected");
    oledMessage = "Sensor issue";
    ledControl(3);
 } else if (sgp30Co2_eq_ppm > 420) {
    Serial.println("High CO2eq Concentration detected");
    oledMessage = "High CO2eq";
    ledControl(3);
  } else {
    Serial.println("Normal CO2eq Concentration");
    oledMessage = "Normal CO2eq\nConcentration";
    ledControl(0);
  }
  oledDisplay(oledMessage);
  Serial.println("------------------------");
  delay(10000);

}
