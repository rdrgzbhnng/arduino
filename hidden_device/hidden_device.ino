const int FSR_PIN        = A0;
const int ALARM_PIN      =  9;
const int ALARM_CONTROL  = 11;

int fsrSensor;
int controlDelay     =   3000;
int alarmDelay      =     600;
int alarmRunning    =  3000; // 180000
int beepDelay       =     100;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ALARM_CONTROL, OUTPUT);
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(FSR_PIN, INPUT);

  digitalWrite(ALARM_PIN, HIGH);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(alarmDelay);
  digitalWrite(LED_BUILTIN, LOW);
  delay(alarmDelay);

  fsrSensor = analogRead(FSR_PIN);
  Serial.print("FSR reading: ");
  Serial.println(fsrSensor);

  if ((fsrSensor > 720) && (fsrSensor <= 970)) {
  beep();
  delay(controlDelay);

  } else if ((fsrSensor > 550) && (fsrSensor < 720)) {
  beep(); beep();
  delay(controlDelay);

  } else {
  beep(); beep(); beep();

  digitalWrite(ALARM_PIN, LOW);
  Serial.println("THE ALARM IS GOING OFF!");
  delay(alarmRunning);
  digitalWrite(ALARM_PIN, HIGH);
  }
}


void beep() {
  tone(ALARM_CONTROL, 10);
  delay(beepDelay);
  tone(ALARM_CONTROL, 0);
  delay(alarmDelay);
}
