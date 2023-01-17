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

  Serial.begin(115200);
  while (!Serial);
  delay(30000);

  s16 err;
  u16 scaled_ethanol_signal, scaled_h2_signal;

  u8x8.begin();
  u8x8.setFlipMode(1);

  dht.begin();
  testSensors();
}


void loop() {
  airQuality();
  gasDetection();
  dustDetection();
  humidityAndTemperature();
  co2AndTvocConcentration();
  barometerSensor();
  ledControl();
  oledDisplay("Hello World!");

  delay(60000);
}


void airQuality() {
  aqsData = airSensor.slope();

  Serial.print("Sensor value: ");
  Serial.println(airSensor.getValue());

  if (aqsData == AirQualitySensor::FORCE_SIGNAL) {
    Serial.println("High pollution! Force signal active.");
  } else if (aqsData == AirQualitySensor::HIGH_POLLUTION) {
    Serial.println("High pollution!");
  } else if (aqsData == AirQualitySensor::LOW_POLLUTION) {
    Serial.println("Low pollution!");
  } else if (aqsData == AirQualitySensor::FRESH_AIR) {
    Serial.println("Fresh air.");
  }
 
  Serial.println("------------------------");
}


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
 
  Serial.println("------------------------");
}


void dustDetection() {
  if (dustSensor.read_sensor_value(hm330Data, 29)) {
    Serial.println("HM330X read result failed!");
  }
  parse_result_value(hm330Data);
  parse_result(hm330Data);
 
  Serial.println("------------------------");
}


void humidityAndTemperature() {

  dhtHumidity = dht.readHumidity();
  dhtTemperature = dht.readTemperature();
  dhtHic = dht.computeHeatIndex(dhtTemperature, dhtHumidity, false);

  if (isnan(dhtHumidity) || isnan(dhtTemperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(dhtHumidity);
  Serial.println(F("%"));

  Serial.print(F("Temperature: "));
  Serial.print(dhtTemperature);
  Serial.println(F("°C"));

  Serial.print(F("Heat index: "));
  Serial.print(dhtHic);
  Serial.println(F("°C"));

  Serial.println("------------------------");
}


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

    Serial.println("------------------------");
}


void oledDisplay(char* msg) {
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0, 0);
  u8x8.print(msg);

  Serial.println("------------------------");
}


void ledControl() {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);

  Serial.println("------------------------");
}


void barometerSensor() {
  Serial.print("Temperature: ");
  Serial.print(bmp280.getTemperature());
  Serial.println("C");

  Serial.print("Pressure: ");
  Serial.print(bmp280Pressure = bmp280.getPressure());
  Serial.println("Pa");

  Serial.print("Altitude: ");
  Serial.print(bmp280.calcAltitude(bmp280Pressure));
  Serial.println("m");

  Serial.println("------------------------");
}


void testSensors() {
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

  Serial.println("Sensors okay!");

  Serial.println("------------------------");
}
