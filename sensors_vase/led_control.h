void ledControl(int n) {
  digitalWrite(ledPin, HIGH);
  if (n == 0) {
    delay(300);
    digitalWrite(ledPin, LOW);
  } else if ( n == 1 ) {
    delay(600);
    digitalWrite(ledPin, LOW);
  } else if ( n == 2) {
    delay(3000);
    digitalWrite(ledPin, LOW);
  } else if ( n == 3 ) {
    delay(60000);
    digitalWrite(ledPin, LOW);
  }
}
