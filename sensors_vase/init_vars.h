int airQualityPin = A0;
int gasDetectionPin = A6;
int ledPin = 4;

int quality;

float sensor_volt;
float RS_air;
float R0;
float sensorValue;
float RS_gas;
float ratio;
float humidity;
float temperature;
float hic;

uint8_t dustData[30];

const char* dustStr[] = {"sensor num: ",
                       "PM1.0 concentration(CF=1,Standard particulate matter, unit:ug/m3): ",
                       "PM2.5 concentration(CF=1,Standard particulate matter, unit:ug/m3): ",
                       "PM10. concentration(CF=1,Standard particulate matter, unit:ug/m3): ",
                       "PM1.0 concentration(Atmospheric environment, unit:ug/m3): ",
                       "PM2.5 concentration(Atmospheric environment, unit:ug/m3): ",
                       "PM10. concentration(Atmospheric environment, unit:ug/m3): ",
                      };
