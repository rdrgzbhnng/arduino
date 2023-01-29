char* oledMessage;

int airQualityPin = A0;
int potentiometerPin = A2;
int gasDetectionPin = A6;
int ledPin = 4;

int aqsData;
int potentiometerData;
int potentiometerMap;

float mq9Volt;
float mq9Data;
float mq9RsAir;
float mq9R0;
float mq9RsGas;
float mq9GasRatio;
float dhtHumidity;
float dhtTemperature;
float dhtHic;
float bmp280Pressure;

uint8_t hm330Data[30];

const char* hm330Str[] = {"sensor num: ",
                       "PM1.0 concentration(CF=1,Standard particulate matter, unit:ug/m3): ",
                       "PM2.5 concentration(CF=1,Standard particulate matter, unit:ug/m3): ",
                       "PM10. concentration(CF=1,Standard particulate matter, unit:ug/m3): ",
                       "PM1.0 concentration(Atmospheric environment, unit:ug/m3): ",
                       "PM2.5 concentration(Atmospheric environment, unit:ug/m3): ",
                       "PM10. concentration(Atmospheric environment, unit:ug/m3): ",
                      };
