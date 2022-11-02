int gasSensorPin = A0;
int gasValue;
int relayPin = 3;

void setup() {
  Serial.begin(9600);

  pinMode(gasSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  gasValue=analogRead(gasSensorPin);
  Serial.print("GasValue= ");
  Serial.println(gasValue);
  
  delay(10000);

  digitalWrite(relayPin, HIGH);
  delay(300);
  digitalWrite(relayPin, LOW);
}
