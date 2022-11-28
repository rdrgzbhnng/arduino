#include "Air_Quality_Sensor.h"
AirQualitySensor sensor(A0);

#include <Seeed_HM330X.h>

#ifdef  ARDUINO_SAMD_VARIANT_COMPLIANCE
  #define SERIAL_OUTPUT SerialUSB
#else
  #define SERIAL_OUTPUT Serial
#endif

HM330X dustSensor;
uint8_t buf[30];

const char* str[] = {"sensor num: ", "PM1.0 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                     "PM2.5 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                     "PM10 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                     "PM1.0 concentration(Atmospheric environment,unit:ug/m3): ",
                     "PM2.5 concentration(Atmospheric environment,unit:ug/m3): ",
                     "PM10 concentration(Atmospheric environment,unit:ug/m3): ",
                    };

HM330XErrorCode print_result(const char* str, uint16_t value) {
  if (NULL == str) {
    return ERROR_PARAM;
  }
  SERIAL_OUTPUT.print(str);
  SERIAL_OUTPUT.println(value);
  return NO_ERROR;
}

HM330XErrorCode parse_result(uint8_t* data) {
  uint16_t value = 0;
  if (NULL == data) {
    return ERROR_PARAM;
  }
  for (int i = 1; i < 8; i++) {
    value = (uint16_t) data[i * 2] << 8 | data[i * 2 + 1];
    print_result(str[i - 1], value);
  }
  return NO_ERROR;
}

HM330XErrorCode parse_result_value(uint8_t* data) {
  if (NULL == data) {
    return ERROR_PARAM;
  }
  for (int i = 0; i < 28; i++) {
    SERIAL_OUTPUT.print(data[i], HEX);
    SERIAL_OUTPUT.print("  ");
    if ((0 == (i) % 5) || (0 == i)) {
      SERIAL_OUTPUT.println("");
    }
  }
  uint8_t sum = 0;
  for (int i = 0; i < 28; i++) {
    sum += data[i];
  }
  if (sum != data[28]) {
    SERIAL_OUTPUT.println("wrong checkSum!!");
  }
  SERIAL_OUTPUT.println("");
  return NO_ERROR;
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Waiting to init..");
  delay(20000);

  if (sensor.init()) {
    Serial.println("Sensor ready.");
  } else {
    Serial.println("Sensor ERROR!");
  }

  SERIAL_OUTPUT.println("Serial start");
  if (dustSensor.init()) {
    SERIAL_OUTPUT.println("HM330X init failed!!");
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
  int quality = sensor.slope();

  Serial.print("Sensor value: ");
  Serial.println(sensor.getValue());

  if (quality == AirQualitySensor::FORCE_SIGNAL) {
    Serial.println("High pollution! Force signal active.");
  } else if (quality == AirQualitySensor::HIGH_POLLUTION) {
    Serial.println("High pollution!");
  } else if (quality == AirQualitySensor::LOW_POLLUTION) {
    Serial.println("Low pollution!");
  } else if (quality == AirQualitySensor::FRESH_AIR) {
    Serial.println("Fresh air.");
  }
 
  Serial.print("\n\n");
  delay(1000);
}


void gasDetection() {
  float sensor_volt;
  float RS_air;
  float R0;
  float sensorValue;
 
  for(int x = 0 ; x < 100 ; x++) {
    sensorValue = sensorValue + analogRead(A6);
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

  float RS_gas;
  float ratio;
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
 
  Serial.print("\n\n");
  delay(1000);
}

void dustDetection() {
  if (dustSensor.read_sensor_value(buf, 29)) {
    SERIAL_OUTPUT.println("HM330X read result failed!!");
  }
  parse_result_value(buf);
  parse_result(buf);
 
  Serial.print("\n\n");
  delay(1000);
}
