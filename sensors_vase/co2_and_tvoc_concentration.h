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
    oledMessage = "Excellent tVOC\nconcentration";
    ledControl(0);
    oledDisplay(oledMessage);
  } else if (sgp30Tvoc_ppb < 1000) {
    Serial.println("tVOC Concentration: Ventilation/airing recommended");
    oledMessage = "Good tVOC\nconcentration";
    ledControl(1);
    oledDisplay(oledMessage);
  } else if (sgp30Tvoc_ppb < 3000) {
    Serial.println("tVOC Concentration: Intensified ventilation recommended");
    oledMessage = "Moderate tVOC\nconcentration";
    ledControl(2);
    oledDisplay(oledMessage);
  } else if (sgp30Tvoc_ppb > 10000) {
    Serial.println("tVOC Concentration: Intensified ventilation/airing necessary");
    oledMessage = "Poor tVOC\nconcentration!";
    ledControl(3);
    oledDisplay(oledMessage);
  } else {
    Serial.println("tVOC Concentration: Hazardous");
    oledMessage = "Unhealthy tVOC\nconcentration!";
    ledControl(3);
    oledDisplay(oledMessage);
  } 

  Serial.println("------------------------");
  delay(10000);

  if (sgp30Co2_eq_ppm > 950) {
    Serial.println("Hazardous CO2eq Concentration detected");
    oledMessage = "Hazardous CO2eq\nconcentration!!";
    oledDisplay(oledMessage);
    ledControl(3);
  } else if (sgp30Co2_eq_ppm > 750) {
    Serial.println("Strong CO2eq Concentration detected");
    oledMessage = "Strong CO2eq\nconcentration!";
    oledDisplay(oledMessage);
    ledControl(2);
  } else if (sgp30Co2_eq_ppm > 550) {
    Serial.println("High CO2eq Concentration detected");
    oledMessage = "High CO2eq\nconcentration!";
    oledDisplay(oledMessage);
    ledControl(1);
  } else if (sgp30Co2_eq_ppm > 350) {
    Serial.println("Normal CO2eq Concentration");
    oledMessage = "Normal CO2eq\nconcentration";
    oledDisplay(oledMessage);
    ledControl(0);
  } else {
    Serial.println("Misreading of CO2eq Concentration");
    oledMessage = "Misreading\nreading CO2eq";
    oledDisplay(oledMessage);
    ledControl(3);
  }

  Serial.println("------------------------");
  delay(10000);
}
