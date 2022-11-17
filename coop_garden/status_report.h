void printStatusReport() {
    Serial.println("---------------------------------");
    Serial.println("---------------------------------");

    Serial.print("lowPulseOccupancy = ");
    Serial.println(lowPulseOccupancy);
    Serial.print("ratio = ");
    Serial.println(ratio);
    Serial.print("concentration = ");
    Serial.println(concentration);

    Serial.println("---------------------------------");
    Serial.println("---------------------------------");

    Serial.print("waterStatus = ");
    Serial.println(waterStatus);

    Serial.println("---------------------------------");
    Serial.println("---------------------------------");

    Serial.print("temperatureValue = "); 
    Serial.print(temperatureValue);
    Serial.println(" C");
    Serial.print("humidityValue = "); 
    Serial.print(humidityValue);
    Serial.println("%"); 

    Serial.println("---------------------------------");
    Serial.println("---------------------------------");

    Serial.print("DRY_VALUE01 = ");
    Serial.println(DRY_VALUE01);
    Serial.print("WET_VALUE01 = ");
    Serial.println(WET_VALUE01);
    Serial.print("soilMoisture01Value = ");
    Serial.println(soilMoisture01Value);

    Serial.print("soilMoisture01Percent = ");
    if(soilMoisture01Percent >= 100) {
      Serial.println("100 %");
    } else if(soilMoisture01Percent <=0) {
      Serial.println("0 %");
    } else if(soilMoisture01Percent >0 && soilMoisture01Percent < 100) {
      Serial.print(soilMoisture01Percent);
      Serial.println("%");
    }

    Serial.println("---------------------------------");

    Serial.print("DRY_VALUE02 = ");
    Serial.println(DRY_VALUE02);
    Serial.print("WET_VALUE02 = ");
    Serial.println(WET_VALUE02);
    Serial.print("soilMoisture02Value = ");
    Serial.println(soilMoisture02Value);
    
    Serial.print("soilMoisture02Percent = ");
    if(soilMoisture02Percent >= 100) {
      Serial.println("100 %");
    } else if(soilMoisture02Percent <=0) {
      Serial.println("0 %");
    } else if(soilMoisture02Percent >0 && soilMoisture02Percent < 100) {
      Serial.print(soilMoisture02Percent);
      Serial.println("%");
    }

    Serial.println("---------------------------------");

    Serial.print("DRY_VALUE03 = ");
    Serial.println(DRY_VALUE03);
    Serial.print("WET_VALUE03 = ");
    Serial.println(WET_VALUE03);
    Serial.print("soilMoisture03Value = ");
    Serial.println(soilMoisture03Value);

    Serial.print("soilMoisture03Percent = ");
    if(soilMoisture03Percent >= 100) {
      Serial.println("100 %");
    } else if(soilMoisture03Percent <=0) {
      Serial.println("0 %");
    } else if(soilMoisture03Percent >0 && soilMoisture03Percent < 100) {
      Serial.print(soilMoisture03Percent);
      Serial.println("%");
    }

    Serial.println("---------------------------------");

    Serial.print("DRY_VALUE04 = ");
    Serial.println(DRY_VALUE04);
    Serial.print("WET_VALUE04 = ");
    Serial.println(WET_VALUE04);
    Serial.print("soilMoisture04Value = ");
    Serial.println(soilMoisture04Value);

    Serial.print("soilMoisture04Percent = ");
    if(soilMoisture04Percent >= 100) {
      Serial.println("100 %");
    } else if(soilMoisture04Percent <=0) {
      Serial.println("0 %");
    } else if(soilMoisture04Percent >0 && soilMoisture04Percent < 100) {
      Serial.print(soilMoisture04Percent);
      Serial.println("%");
    }

    Serial.println("---------------------------------");

    Serial.print("DRY_VALUE05 = ");
    Serial.println(DRY_VALUE05);
    Serial.print("WET_VALUE05 = ");
    Serial.println(WET_VALUE05);
    Serial.print("soilMoisture05Value = ");
    Serial.println(soilMoisture05Value);

    Serial.print("soilMoisture05Percent = ");
    if(soilMoisture05Percent >= 100) {
      Serial.println("100 %");
    } else if(soilMoisture05Percent <=0) {
      Serial.println("0 %");
    } else if(soilMoisture05Percent >0 && soilMoisture05Percent < 100) {
      Serial.print(soilMoisture05Percent);
      Serial.println("%");
    }

    Serial.println("---------------------------------");

    Serial.print("DRY_VALUE06 = ");
    Serial.println(DRY_VALUE06);
    Serial.print("WET_VALUE06 = ");
    Serial.println(WET_VALUE06);
    Serial.print("soilMoisture06Value = ");
    Serial.println(soilMoisture06Value);

    Serial.print("soilMoisture06Percent = ");
    if(soilMoisture06Percent >= 100) {
      Serial.println("100 %");
    } else if(soilMoisture06Percent <=0) {
      Serial.println("0 %");
    } else if(soilMoisture06Percent >0 && soilMoisture06Percent < 100) {
      Serial.print(soilMoisture06Percent);
      Serial.println("%");
    }
    
    Serial.println("---------------------------------");
    Serial.println("---------------------------------");

    Serial.print("sunLightIR = ");
    Serial.println(sunLightIR);
    Serial.print("sunLightVisible = ");
    Serial.println(sunLightVisible);
    Serial.print("sunLightUV = ");
    Serial.println(sunLightUV);

    Serial.println("---------------------------------");
    Serial.println("---------------------------------");
    Serial.println("");
}