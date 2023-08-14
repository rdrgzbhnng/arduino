const int FSR_PIN       =      A0;
const int RESET_PIN     =       7;
const int ALARM_PIN     =       9;
const int ALARM_CONTROL =      11;
const int SAMPLE_TIME   =   10000;
const int ALARM_DELAY   =    3000;
const int ALARM_RUNNING =  180000;
const int BEEP_DELAY    =       3;

int fsrSensor;

int alarmPoint          =     320;
int safeFrom            =     560;
int safeUntil           =     980;

unsigned long duration;
unsigned long controlTime;

#include <SoftwareSerial.h>

void setup() {
  digitalWrite(RESET_PIN, HIGH);
  digitalWrite(ALARM_PIN, HIGH);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ALARM_CONTROL, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(FSR_PIN, INPUT);

  Serial.begin(9600);
  controlTime = millis();
}


void loop() {
  if ((millis() - controlTime) > SAMPLE_TIME) {
    digitalWrite(LED_BUILTIN, HIGH);

    fsrSensor = analogRead(FSR_PIN);
    Serial.print("FSR reading: ");
    Serial.println(fsrSensor);

    if (controlTime > 21600000) {
      reset();
    }

    if ((fsrSensor > safeFrom) && (fsrSensor < safeUntil)) {
      Serial.println("Beep!");
      beep();
    } else if ((fsrSensor > alarmPoint) && (fsrSensor <= safeFrom)) {
      Serial.println("Beep! Beep!");
      beep(); beep();
    } else {
      Serial.println("Beep! Beep! Beep!");
      beep(); beep(); beep();
      siren();
    }

    controlTime = millis();
    Serial.print("Control time: ");
    Serial.println(controlTime);
    Serial.println("---------------------");

    digitalWrite(LED_BUILTIN, LOW);
  }
}


void beep() {
  digitalWrite(ALARM_CONTROL, HIGH);
  delay(BEEP_DELAY);
  digitalWrite(ALARM_CONTROL, LOW);
  delay(ALARM_DELAY);
}


void reset() {
  digitalWrite(RESET_PIN, LOW);
}


void siren() {
  digitalWrite(ALARM_PIN, LOW);
  Serial.println("The alarm is going off!");
  delay(ALARM_RUNNING);
  digitalWrite(ALARM_PIN, HIGH);
}
