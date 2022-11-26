#include "init_vars.h"
#include "pin_list.h"

#include "Air_Quality_Sensor.h"
AirQualitySensor sensor(airQualitySensorPin);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Waiting to init..");
  delay(20000);

  if (sensor.init()) {
    Serial.println("Sensor ready.");
  } else {
    Serial.println("Sensor ERROR!");
  }
}

void loop() {
  sensorValue = analogRead(dustDetectionSensorPin);
  sensor_volt=(float)sensorValue/1024*5.0;
  RS_gas = (5.0-sensor_volt)/sensor_volt;

  ratio = RS_gas/0.165;

  Serial.print("sensor_volt = ");
  Serial.println(sensor_volt);
  Serial.print("RS_ratio = ");
  Serial.println(RS_gas);
  Serial.print("Rs/R0 = ");
  Serial.println(ratio);


  qualityAir = sensor.slope();

  Serial.print("Sensor value: ");
  Serial.println(sensor.getValue());

  if (qualityAir == AirQualitySensor::FORCE_SIGNAL) {
    Serial.println("High pollution! Force signal active.");
  } else if (qualityAir == AirQualitySensor::HIGH_POLLUTION) {
    Serial.println("High pollution!");
  } else if (qualityAir == AirQualitySensor::LOW_POLLUTION) {
    Serial.println("Low pollution!");
  } else if (qualityAir == AirQualitySensor::FRESH_AIR) {
    Serial.println("Fresh air.");
  }

  delay(3000);
}
