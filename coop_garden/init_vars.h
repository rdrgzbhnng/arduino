int soilMoisture01Value = 0;
int soilMoisture01Percent = 0;
int soilMoisture02Value = 0;
int soilMoisture02Percent = 0;
int soilMoisture03Value = 0;
int soilMoisture03Percent = 0;
int soilMoisture04Value = 0;
int soilMoisture04Percent = 0;
int soilMoisture05Value = 0;
int soilMoisture05Percent= 0;
int soilMoisture06Value = 0;
int soilMoisture06Percent = 0;

unsigned long duration;
unsigned long startTime;

const long SAMPLE_TIME = 60000;
unsigned long lowPulseOccupancy = 0;

float ratio = 0;
float concentration = 0;

int waterValue;
String waterStatus;

float temperatureValue;
float humidityValue;

float sunLightIR;
float sunLightVisible;
float sunLightUV;

String fullMessage;
String messageTitle;
String messageTarget;
String messageValue;

String baselineValue;
int carbonDioxide;
int tVolatileOrganicCompounds;
