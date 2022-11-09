int dustSensorPin = 4;

unsigned long duration;
unsigned long startTime;

const long SAMPLE_TIME = 30000;
unsigned long lowPulseOccupancy = 0;

float ratio = 0;
float concentration = 0;

void setup() {
  Serial.begin(9600);

  pinMode(dustSensorPin, INPUT);

  startTime = millis();
}

void loop() {
  duration = pulseIn(dustSensorPin, LOW);
  lowPulseOccupancy = lowPulseOccupancy + duration;

  if ((millis()-startTime) > SAMPLE_TIME) {
    ratio = lowPulseOccupancy / (SAMPLE_TIME * 10.0);
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;
    
    Serial.print("lowpulseoccupancy = "); // remover
    Serial.println(lowPulseOccupancy); // remover
    Serial.print("ratio = "); // remover
    Serial.println(ratio); // remover
    Serial.print("concentration = "); // remover
    Serial.println(concentration); // remover
    
    lowPulseOccupancy = 0;
    
    startTime = millis();
  }
}
