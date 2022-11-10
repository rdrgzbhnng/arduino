int gasSensorPin = A0;
int flameSensorPin = A1;

int pirSensorPin = 2;
int relayPin = 3;
int buzzPin = 8;
int flameValue;
int gasValue;
int pirValue;

unsigned long duration;
unsigned long startTime;

const long SAMPLE_TIME = 60000;
const int GAS_WARNING = 300;
const int FLAME_WARNING = 400;
const long HARD_ALARM = 300000;
const int PIR_STATUS = 0;

unsigned long issue_01 = 0;
unsigned long issue_02 = 0;
unsigned long issue_03 = 0;

void setup() {
  Serial.begin(9600);

  pinMode(gasSensorPin, INPUT);
  pinMode(flameSensorPin, INPUT);
  pinMode(pirSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, LOW);
  noTone(buzzPin);

  startTime = millis();
}

void loop() {
  if ((millis() - startTime) > SAMPLE_TIME) {
    gasValue = analogRead(gasSensorPin);
    flameValue = analogRead(flameSensorPin);
    pirValue = digitalRead(pirSensorPin);

    if ((gasValue > GAS_WARNING) || (flameValue > FLAME_WARNING)) {
      soft_alarm();
      hard_alarm();
    }
    startTime = millis();
  }
}

void soft_alarm() {
  for (int i = 1; i <= 10; i += 1) {
    tone(buzzPin, 100, 300);
    delay(1000);
    noTone(buzzPin);
    delay(300);
  }
  noTone(buzzPin);
}

void hard_alarm() {
  issue_01 = issue_02;
  issue_02 = issue_03;
  issue_03 = millis();

  if (issue_01 > 0 ) {
    if ((issue_03 - issue_02) < (SAMPLE_TIME * 2)) {
      if ((issue_02 - issue_01) < (SAMPLE_TIME * 2)) {
        pirValue = digitalRead(pirSensorPin);
        if (pirValue == 0) {

          digitalWrite(relayPin, HIGH);
          delay(HARD_ALARM);
          digitalWrite(relayPin, LOW);
        }
      }
    }
  }
}
