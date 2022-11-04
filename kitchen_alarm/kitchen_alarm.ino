int gasSensorPin = A0;
int flameSensorPin = A1;
int pirSensorPin = 2;
int relayPin = 3;
int buzzPin = 8;

int flameValue;
int gasValue;
int pirValue;

void setup() {
  Serial.begin(9600);

  pinMode(gasSensorPin, INPUT);
  pinMode(flameSensorPin, INPUT);
  pinMode(pirSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  gasValue=analogRead(gasSensorPin);
  Serial.print("GasValue= ");
  Serial.println(gasValue);
  
  flameValue=analogRead(flameSensorPin);
  Serial.print("FlameValue= ");
  Serial.println(flameValue);

  delay(10000);

  digitalWrite(relayPin, HIGH);
  delay(300);
  digitalWrite(relayPin, LOW);

  pirValue = digitalRead(pirSensorPin);
  Serial.print("PirValue= ");
  Serial.println(pirValue);

  noTone(buzzPin);
  delay(200);
  tone(buzzPin,100,300);
  delay(1000);
  tone(buzzPin,100,300);
  delay(1000);
  tone(buzzPin,100,300);
  delay(1000);
  noTone(buzzPin);

}
