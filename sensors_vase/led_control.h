void ledControl(int n) {
  digitalWrite(ledPin, HIGH);
  if (n == 0) {
    delay(200);
    digitalWrite(ledPin, LOW);
  } else if ( n == 1 ) {
    delay(2000);
    digitalWrite(ledPin, LOW);
  } else if ( n == 2) {
    delay(5000);
    digitalWrite(ledPin, LOW);
  } else if ( n == 3 ) {
    delay(30000);
    digitalWrite(ledPin, LOW);
  }
}
