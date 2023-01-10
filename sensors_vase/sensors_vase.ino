#include "init_vars.h"

#include "Air_Quality_Sensor.h"
AirQualitySensor airSensor(airQualityPin);

#include <Seeed_HM330X.h>
HM330X dustSensor;
#include "hm330x_errors.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Waiting to init..");
  delay(20000);

  if (airSensor.init()) {
    Serial.println("Sensor ready.");
  } else {
    Serial.println("Sensor ERROR!");
  }

  Serial.println("Serial start");
  if (dustSensor.init()) {
    Serial.println("HM330X init failed!!");
    while (1);
  }
}


void loop() {
  airQuality();
  gasDetection();
  dustDetection();

  delay(10000);
}


void airQuality() {
  quality = airSensor.slope();

  Serial.print("Sensor value: ");
  Serial.println(airSensor.getValue());

  if (quality == AirQualitySensor::FORCE_SIGNAL) {
    Serial.println("High pollution! Force signal active.");
  } else if (quality == AirQualitySensor::HIGH_POLLUTION) {
    Serial.println("High pollution!");
  } else if (quality == AirQualitySensor::LOW_POLLUTION) {
    Serial.println("Low pollution!");
  } else if (quality == AirQualitySensor::FRESH_AIR) {
    Serial.println("Fresh air.");
  }
 
  Serial.println("------------------------");
}


void gasDetection() {
  for(int x = 0 ; x < 100 ; x++) {
    sensorValue = sensorValue + analogRead(gasDetectionPin);
  }
  sensorValue = sensorValue/100.0;
 
  sensor_volt = sensorValue/1024*5.0;
  RS_air = (5.0-sensor_volt)/sensor_volt;
  R0 = RS_air/9.9;
 
  Serial.print("sensor_volt = ");
  Serial.print(sensor_volt);
  Serial.println("V");
 
  Serial.print("R0 = ");
  Serial.println(R0);

  sensorValue = analogRead(A6);
  sensor_volt=(float)sensorValue/1024*5.0;
  RS_gas = (5.0-sensor_volt)/sensor_volt;
 
  ratio = RS_gas/R0;
 
  Serial.print("sensor_volt = ");
  Serial.println(sensor_volt);
  Serial.print("RS_ratio = ");
  Serial.println(RS_gas);
  Serial.print("Rs/R0 = ");
  Serial.println(ratio);
 
  Serial.println("------------------------");
}


void dustDetection() {
  if (dustSensor.read_sensor_value(dustData, 29)) {
    Serial.println("HM330X read result failed!");
  }
  parse_result_value(dustData);
  parse_result(dustData);
 
  Serial.println("------------------------");
}
