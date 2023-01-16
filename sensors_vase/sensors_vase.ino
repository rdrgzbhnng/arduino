#include "init_vars.h"

#include <U8x8lib.h>
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

#include "Air_Quality_Sensor.h"
AirQualitySensor airSensor(airQualityPin);

#include <Seeed_HM330X.h>
HM330X dustSensor;
#include "hm330x_errors.h"

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#include "sensirion_common.h"
#include "sgp30.h"

#include "Seeed_BMP280.h"
#include <Wire.h>
BMP280 bmp280;


void setup() {
  pinMode(ledPin, OUTPUT);

  s16 err;
  u16 scaled_ethanol_signal, scaled_h2_signal;

  Serial.begin(115200);
  while (!Serial);

  Serial.println("Waiting to init...");
  delay(30000);

  u8x8.begin();
  u8x8.setFlipMode(1);

  if (airSensor.init() == 0) {
    Serial.println("airSensor failed!");
  }

  if (dustSensor.init() == -2) {
    Serial.println("HM330X failed!");
  }

  if (sgp_probe() == -1) {
    Serial.println("SGP failed!");
  }

  if(!bmp280.init()){
    Serial.println("Device error!");
  }

  dht.begin();
}


void loop() {
  airQuality();
  gasDetection();
  dustDetection();
  humidityAndTemperature();
  co2AndTvocConcentration();
  barometerSensor();
  ledControl();
  oledDisplay();

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


void humidityAndTemperature() {

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  hic = dht.computeHeatIndex(temperature, humidity, false);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.println(F("%"));

  Serial.print(F("Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C"));

  Serial.print(F("Heat index: "));
  Serial.print(hic);
  Serial.println(F("°C"));

  Serial.println("------------------------");
}


void co2AndTvocConcentration() {
    s16 err = 0;
    u16 tvoc_ppb, co2_eq_ppm;
    err = sgp_measure_iaq_blocking_read(&tvoc_ppb, &co2_eq_ppm);
    if (err == STATUS_OK) {
        Serial.print("tVOC Concentration: ");
        Serial.print(tvoc_ppb);
        Serial.println("ppb");

        Serial.print("CO2eq Concentration: ");
        Serial.print(co2_eq_ppm);
        Serial.println("ppm");
    } else {
        Serial.println("error reading IAQ values\n");
    }

    Serial.println("------------------------");
}


void oledDisplay() {
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0, 0);
  u8x8.print("Hello World!");

  Serial.println("------------------------");
}


void ledControl() {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);

  Serial.println("------------------------");
}


void barometerSensor() {
  Serial.print("Temp: ");
  Serial.print(bmp280.getTemperature());
  Serial.println("C");

  Serial.print("Pressure: ");
  Serial.print(pressure = bmp280.getPressure());
  Serial.println("Pa");

  Serial.print("Altitude: ");
  Serial.print(bmp280.calcAltitude(pressure));
  Serial.println("m");

  Serial.println("------------------------");
}
