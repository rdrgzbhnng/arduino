const int FSR_PIN       =      A0;
const int RX_PIN        =       3;
const int TX_PIN        =       5;
const int RESET_PIN     =       7;
const int ALARM_PIN     =       9;
const int ALARM_CONTROL =      11;
const int SAMPLE_TIME   =   10000;
const int ALARM_DELAY   =    3000;
const int ALARM_RUNNING =  180000;
const int WIFI_TIMEOUT =     2000;
const int BEEP_DELAY    =       3;

int fsrSensor;

int alarmPoint          =     320;
int safeFrom            =     560;
int safeUntil           =     980;

unsigned long duration;
unsigned long controlTime;

long initial_time;
boolean response_end;
String message;
String requestHTTP;
char msg;

#include <SoftwareSerial.h>
SoftwareSerial SerialESP8266(RX_PIN, TX_PIN);

void setup() {
  digitalWrite(RESET_PIN, HIGH);
  digitalWrite(ALARM_PIN, LOW);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ALARM_CONTROL, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(FSR_PIN, INPUT);

  Serial.begin(9600);
  controlTime = millis();

  SerialESP8266.begin(9600);
  SerialESP8266.setTimeout(WIFI_TIMEOUT);

  SerialESP8266.println("AT");
  if (SerialESP8266.find("OK")) {
    Serial.println("Correct AT answer");
  } else {
    Serial.println("Error in ESP8266");
  }

  SerialESP8266.println("AT+UART_DEF=9600,8,1,0,0");
  if (SerialESP8266.find("AT+UART_DEF=9600,8,1,0,0")) {
    Serial.println("Correct speed response");
  } else {
    Serial.println("Speed error");
  }

  SerialESP8266.println("AT+CWMODE=1");
  if (SerialESP8266.find("")) {
    Serial.println("ESP8266 in Station mode");
  }

  SerialESP8266.setTimeout(WIFI_TIMEOUT*10);
  SerialESP8266.println("AT+CWJAP=\"MIWIFI_Fuyq\",\"uE3XGyUa\"");

  Serial.println("Connecting to the network");
  if (SerialESP8266.find("OK")) {
    Serial.println("WIFI connected");
  } else {
    Serial.println("Error connecting to the network");
  }

  SerialESP8266.setTimeout(WIFI_TIMEOUT);
  SerialESP8266.println("AT+CIPMUX=0");
  if (SerialESP8266.find("OK")) {
    Serial.println("Multi-connections disabled");
  }
}


void loop() {
  if ((millis() - controlTime) > SAMPLE_TIME) {
    digitalWrite(LED_BUILTIN, HIGH);

    fsrSensor = analogRead(FSR_PIN);
    Serial.print("FSR reading: ");
    Serial.println(fsrSensor);

    if (controlTime > 21600000) {
      reset();
    }

    if ((fsrSensor > safeFrom) && (fsrSensor < safeUntil)) {
      Serial.println("Beep!");
      beep();
    } else if ((fsrSensor > alarmPoint) && (fsrSensor <= safeFrom)) {
      Serial.println("Beep! Beep!");
      beep(); beep();
    } else {
      Serial.println("Beep! Beep! Beep!");
      beep(); beep(); beep();
      ifttt();
      siren();
    }

    controlTime = millis();
    Serial.print("Control time: ");
    Serial.println(controlTime);
    Serial.println("---------------------");

    digitalWrite(LED_BUILTIN, LOW);
  }
}


void beep() {
  digitalWrite(ALARM_CONTROL, HIGH);
  delay(BEEP_DELAY);
  digitalWrite(ALARM_CONTROL, LOW);
  delay(ALARM_DELAY);
}


void reset() {
  digitalWrite(RESET_PIN, LOW);
}


void siren() {
  digitalWrite(ALARM_PIN, HIGH);
  Serial.println("The alarm is going off!");
  delay(ALARM_RUNNING);
  digitalWrite(ALARM_PIN, LOW);
}


void ifttt() {
  if (SerialESP8266.available()) {

    SerialESP8266.println("AT+CIPSTART=\"TCP\",\"maker.ifttt.com\",80");
    if (SerialESP8266.find("CONNECT")) {
      Serial.println("Server connected");
    }

    requestHTTP= "GET /trigger/macStudio/with/key/dVJCyJon9DxP4MkPio8RH4 HTTP/1.1\r\n";
    requestHTTP = requestHTTP + "Host: maker.ifttt.com\r\n\r\n";

    SerialESP8266.print("AT+CIPSEND=");
    SerialESP8266.println(requestHTTP.length());
    if (SerialESP8266.find(">")) {
      Serial.println("Ready to send HTTP");
    }

    SerialESP8266.println(requestHTTP);
    if (SerialESP8266.find("SEND OK")) {
      Serial.println("HTTP request sent:");
      Serial.println(requestHTTP);
    }

    response_end = false;
    initial_time = millis();
    message = "";

    while (response_end==false) {
      while (SerialESP8266.available()>0) {
        msg=SerialESP8266.read();
        Serial.write(msg);
        message.concat(msg);
      }

      if (message.length() > 500) {
        Serial.println("The response to exceeded the maximum size");
        SerialESP8266.println("AT+CIPCLOSE");
        if (SerialESP8266.find("OK"))
          Serial.println("Connection terminated");
        response_end = true;
      }

      if ((millis()-initial_time) > 10000) {
        Serial.println("Timeout");
        SerialESP8266.println("AT+CIPCLOSE");
        if (SerialESP8266.find("OK"))
          Serial.println("Connection terminated");
        response_end = true;
      }

      if (message.indexOf("CLOSED") > 0) {
        Serial.println();
        Serial.println("Message received successfully, Connection terminated");
        response_end = true;
      }
    }
  } else {
    Serial.println("SerialESP8266 not available");
  }
}
