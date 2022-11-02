int gasSensorPin = A0;
int gasValue;


void setup() {
  Serial.begin(9600);

  pinMode(gasSensorPin, INPUT);
}

void loop() {
  gasValue=analogRead(gasSensorPin);
  Serial.print("GasValue= ");
  Serial.println(gasValue);
  delay(500);
}
