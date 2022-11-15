int waterSensorPin = 2;
int dustSensorPin = 4;

int soilMoistureSensor01Pin = A0;
int soilMoisture01Value = 0;
int soilMoisture01Percent=0;
const int DRY_VALUE01 = 20;
const int WET_VALUE01 = 620;

int soilMoistureSensor02Pin = A1;
int soilMoisture02Value = 0;
int soilMoisture02Percent=0;
const int DRY_VALUE02 = 10;
const int WET_VALUE02 = 630;

int soilMoistureSensor03Pin = A2;
int soilMoisture03Value = 0;
int soilMoisture03Percent=0;
const int DRY_VALUE03 = 10;
const int WET_VALUE03 = 720;

int soilMoistureSensor04Pin = A3;
int soilMoisture04Value = 0;
int soilMoisture04Percent=0;
const int DRY_VALUE04 = 690;
const int WET_VALUE04 = 470;

int soilMoistureSensor05Pin = A4;
int soilMoisture05Value = 0;
int soilMoisture05Percent=0;
const int DRY_VALUE05 = 730;
const int WET_VALUE05 = 420;

int soilMoistureSensor06Pin = A5;
int soilMoisture06Value = 0;
int soilMoisture06Percent=0;
const int DRY_VALUE06 = 500;
const int WET_VALUE06 = 270;

unsigned long duration;
unsigned long startTime;

const long SAMPLE_TIME = 60000;
unsigned long lowPulseOccupancy = 0;

float ratio = 0;
float concentration = 0;

int waterValue;
String waterStatus;

void setup() {
  Serial.begin(9600);

  pinMode(soilMoistureSensor01Pin, INPUT);
  pinMode(soilMoistureSensor02Pin, INPUT);
  pinMode(soilMoistureSensor03Pin, INPUT);
  pinMode(soilMoistureSensor04Pin, INPUT);
  pinMode(soilMoistureSensor05Pin, INPUT);
  pinMode(soilMoistureSensor06Pin, INPUT);
  pinMode(waterSensorPin, INPUT);
  pinMode(dustSensorPin, INPUT);

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
      waterStatus = "Nops";
    } else {
      waterStatus = "Yep!";
    }

    Serial.println("---------------------------------");
    Serial.println("---------------------------------");

    Serial.print("lowpulseoccupancy = ");
    Serial.println(lowPulseOccupancy);
    Serial.print("ratio = ");
    Serial.println(ratio);
    Serial.print("concentration = ");
    Serial.println(concentration);
    Serial.print("there is water? ");
    Serial.println(waterStatus);
    
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

    Serial.println("---------------------------------");
    Serial.println("---------------------------------");

    Serial.print("DRY_VALUE01 = ");
    Serial.println(DRY_VALUE01);
    Serial.print("WET_VALUE01 = ");
    Serial.println(WET_VALUE01);
    Serial.print("soilMoisture01Value = ");
    Serial.println(soilMoisture01Value);

    Serial.print("soilMoisture01Percent = ");
    if(soilMoisture01Percent >= 100) {
      Serial.println("100 %");
    } else if(soilMoisture01Percent <=0) {
      Serial.println("0 %");
    } else if(soilMoisture01Percent >0 && soilMoisture01Percent < 100) {
      Serial.print(soilMoisture01Percent);
      Serial.println("%");
    }

    Serial.println("---------------------------------");

    Serial.print("DRY_VALUE02 = ");
    Serial.println(DRY_VALUE02);
    Serial.print("WET_VALUE02 = ");
    Serial.println(WET_VALUE02);
    Serial.print("soilMoisture02Value = ");
    Serial.println(soilMoisture02Value);
    
    Serial.print("soilMoisture02Percent = ");
    if(soilMoisture02Percent >= 100) {
      Serial.println("100 %");
    } else if(soilMoisture02Percent <=0) {
      Serial.println("0 %");
    } else if(soilMoisture02Percent >0 && soilMoisture02Percent < 100) {
      Serial.print(soilMoisture02Percent);
      Serial.println("%");
    }

    Serial.println("---------------------------------");

    Serial.print("DRY_VALUE03 = ");
    Serial.println(DRY_VALUE03);
    Serial.print("WET_VALUE03 = ");
    Serial.println(WET_VALUE03);
    Serial.print("soilMoisture03Value = ");
    Serial.println(soilMoisture03Value);

    Serial.print("soilMoisture03Percent = ");
    if(soilMoisture03Percent >= 100) {
      Serial.println("100 %");
    } else if(soilMoisture03Percent <=0) {
      Serial.println("0 %");
    } else if(soilMoisture03Percent >0 && soilMoisture03Percent < 100) {
      Serial.print(soilMoisture03Percent);
      Serial.println("%");
    }

    Serial.println("---------------------------------");

    Serial.print("DRY_VALUE04 = ");
    Serial.println(DRY_VALUE04);
    Serial.print("WET_VALUE04 = ");
    Serial.println(WET_VALUE04);
    Serial.print("soilMoisture04Value = ");
    Serial.println(soilMoisture04Value);

    Serial.print("soilMoisture04Percent = ");
    if(soilMoisture04Percent >= 100) {
      Serial.println("100 %");
    } else if(soilMoisture04Percent <=0) {
      Serial.println("0 %");
    } else if(soilMoisture04Percent >0 && soilMoisture04Percent < 100) {
      Serial.print(soilMoisture04Percent);
      Serial.println("%");
    }

    Serial.println("---------------------------------");

    Serial.print("DRY_VALUE05 = ");
    Serial.println(DRY_VALUE05);
    Serial.print("WET_VALUE05 = ");
    Serial.println(WET_VALUE05);
    Serial.print("soilMoisture05Value = ");
    Serial.println(soilMoisture05Value);

    Serial.print("soilMoisture05Percent = ");
    if(soilMoisture05Percent >= 100) {
      Serial.println("100 %");
    } else if(soilMoisture05Percent <=0) {
      Serial.println("0 %");
    } else if(soilMoisture05Percent >0 && soilMoisture05Percent < 100) {
      Serial.print(soilMoisture05Percent);
      Serial.println("%");
    }

    Serial.println("---------------------------------");

    Serial.print("DRY_VALUE06 = ");
    Serial.println(DRY_VALUE06);
    Serial.print("WET_VALUE06 = ");
    Serial.println(WET_VALUE06);
    Serial.print("soilMoisture06Value = ");
    Serial.println(soilMoisture06Value);

    Serial.print("soilMoisture06Percent = ");
    if(soilMoisture06Percent >= 100) {
      Serial.println("100 %");
    } else if(soilMoisture06Percent <=0) {
      Serial.println("0 %");
    } else if(soilMoisture06Percent >0 && soilMoisture06Percent < 100) {
      Serial.print(soilMoisture06Percent);
      Serial.println("%");
    }
    
    lowPulseOccupancy = 0;
    
    startTime = millis();
  }
}
