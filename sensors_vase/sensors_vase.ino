#include "init_vars.h"
#include "led_control.h"

#include <U8x8lib.h>
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);
#include "oled_display.h"

#include "Air_Quality_Sensor.h"
AirQualitySensor airSensor(airQualityPin);
#include "air_quality.h"

#include "gas_detection.h"

#include <Seeed_HM330X.h>
HM330X dustSensor;
#include "hm330x_errors.h"

#include <Tomoto_HM330X.h>
Tomoto_HM330X dustSensorLE;
#include "dust_detection.h"

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
#include "humidity_and_temperature.h"

#include "sensirion_common.h"
#include "sgp30.h"
#include "co2_and_tvoc_concentration.h"

#include "Seeed_BMP280.h"
BMP280 bmp280;
#include "barometer.h"

#include <Wire.h>
#include "test_sensors.h"

void setup() {
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
  delay(3000);

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
  dustDetectionLE();
  humidityAndTemperature();
  co2AndTvocConcentration();
  barometerSensor();
}
