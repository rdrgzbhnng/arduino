#include <Arduino.h>
#include <Wire.h>
#include "SHT31.h"
#include "Si115X_SAMD21.h"
#include <SPI.h>
#include <WiFiNINA.h>

#include "init_vars.h"
#include "pin_list.h"
#include "sensors_settings.h"
#include "status_report.h"
#include "wifi_secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;
char server[] = "maker.ifttt.com";
WiFiClient client;

Si115X si1151;
SHT31 sht31 = SHT31();

void setup() {
  Serial.begin(115200);
  uint8_t conf[4];

  if (!si1151.Begin())
    Serial.println("Si1151 is not ready!");
  else
    Serial.println("Si1151 is ready!");

  pinMode(soilMoistureSensor01Pin, INPUT);
  pinMode(soilMoistureSensor02Pin, INPUT);
  pinMode(soilMoistureSensor03Pin, INPUT);
  pinMode(soilMoistureSensor04Pin, INPUT);
  pinMode(soilMoistureSensor05Pin, INPUT);
  pinMode(soilMoistureSensor06Pin, INPUT);
  pinMode(waterSensorPin, INPUT);
  pinMode(dustSensorPin, INPUT);

  pinMode(relayPin01, OUTPUT);
  pinMode(relayPin02, OUTPUT);

  digitalWrite(relayPin01, HIGH);
  digitalWrite(relayPin02, HIGH);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  sht31.begin();
  startTime = millis();
}

void loop() {
  duration = pulseIn(dustSensorPin, LOW);
  lowPulseOccupancy = lowPulseOccupancy + duration;

  if ((millis()-startTime) > SAMPLE_TIME) {

    ratio = lowPulseOccupancy / (SAMPLE_TIME * 10.0);
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;

    waterValue = (digitalRead(waterSensorPin));
    waterStatus = "";

    if (waterValue == 1) {
      waterStatus = "Nothing detected";
    } else {
      waterStatus = "Water detected";
    }

    float temperatureValue = sht31.getTemperature();
    float humidityValue = sht31.getHumidity();

    soilMoisture01Value = analogRead(soilMoistureSensor01Pin);
    soilMoisture02Value = analogRead(soilMoistureSensor02Pin);
    soilMoisture03Value = analogRead(soilMoistureSensor03Pin);
    soilMoisture04Value = analogRead(soilMoistureSensor04Pin);
    soilMoisture05Value = analogRead(soilMoistureSensor05Pin);
    soilMoisture06Value = analogRead(soilMoistureSensor06Pin);

    soilMoisture01Percent = map(soilMoisture01Value, DRY_VALUE01, WET_VALUE01, 0, 100);
    soilMoisture02Percent = map(soilMoisture02Value, DRY_VALUE02, WET_VALUE02, 0, 100);
    soilMoisture03Percent = map(soilMoisture03Value, DRY_VALUE03, WET_VALUE03, 0, 100);
    soilMoisture04Percent = map(soilMoisture04Value, DRY_VALUE04, WET_VALUE04, 0, 100);
    soilMoisture05Percent = map(soilMoisture05Value, DRY_VALUE05, WET_VALUE05, 0, 100);
    soilMoisture06Percent = map(soilMoisture06Value, DRY_VALUE06, WET_VALUE06, 0, 100);

    sunLightIR = si1151.ReadHalfWord();
    sunLightVisible = si1151.ReadHalfWord_VISIBLE();
    sunLightUV = si1151.ReadHalfWord_UV();

    if (soilMoisture01Percent > 80) {
      digitalWrite(relayPin01, LOW);
      sendAlertMessage();
    } else {
      digitalWrite(relayPin01, HIGH);
    }

    printStatusReport();

    lowPulseOccupancy = 0;
    startTime = millis();
  }
}

void sendAlertMessage () {
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect... ");
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.println("Connected to WiFi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  if (client.connect(server, 80)) {
    Serial.println("connected to server;");
    client.println("GET /trigger/HuertoAlert/with/key/dVJCyJon9DxP4MkPio8RH4 HTTP/1.1");
    client.println("Host: maker.ifttt.com");
    client.println("Connection: close");
    client.println();
    Serial.println("connection closed.");
   }
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
