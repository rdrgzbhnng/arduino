int gasSensorPin = A0;
int flameSensorPin = A1;
int relayPin = 3;

int flameValue;
int gasValue;

void setup() {
  Serial.begin(9600);

  pinMode(gasSensorPin, INPUT);
  pinMode(flameSensorPin, INPUT);
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

  // digitalWrite(relayPin, HIGH);
  // delay(300);
  // digitalWrite(relayPin, LOW);
}
