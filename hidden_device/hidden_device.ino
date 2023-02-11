const int FSR_PIN       =      A0;
const int RESET_PIN     =       7;
const int ALARM_PIN     =       9;
const int ALARM_CONTROL =      11;
const int SAMPLE_TIME   =   10000;

int fsrSensor;
int alarmDelay          =     500;
int alarmRunning        =  180000;
int beepDelay           =     100;

unsigned long duration;
unsigned long controlTime;


void setup() {
  digitalWrite(RESET_PIN, HIGH);
  digitalWrite(ALARM_PIN, HIGH);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ALARM_CONTROL, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(FSR_PIN, INPUT);

  controlTime = millis();
}


void loop() {
  if ((millis() - controlTime) > SAMPLE_TIME) {
    digitalWrite(LED_BUILTIN, HIGH);

    fsrSensor = analogRead(FSR_PIN);
    Serial.print("FSR reading: ");
    Serial.println(fsrSensor);
    Serial.print("Control time: ");
    Serial.println(controlTime);

    if (controlTime > 21600000) {
      reset();
    }

    if ((fsrSensor > 680) && (fsrSensor <= 920)) {
      beep();
    } else if ((fsrSensor > 550) && (fsrSensor <= 680)) {
      beep(); beep();
    } else {
      beep(); beep(); beep();
      siren();
    }

    controlTime = millis();
    digitalWrite(LED_BUILTIN, LOW);
  }
}


void beep() {
  tone(ALARM_CONTROL, 10);
  delay(beepDelay);
  tone(ALARM_CONTROL, 0);
  delay(alarmDelay);
}


void reset() {
  digitalWrite(RESET_PIN, LOW);
}


void siren() {
  digitalWrite(ALARM_PIN, LOW);
  Serial.println("THE ALARM IS GOING OFF!");
  delay(alarmRunning);
  digitalWrite(ALARM_PIN, HIGH);
}
