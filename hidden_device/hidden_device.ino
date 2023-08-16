const int FSR_PIN       =       A0;
const int RX_PIN        =        3;
const int TX_PIN        =        5;
const int RESET_PIN     =        7;
const int ALARM_PIN     =        9;
const int ALARM_CONTROL =       11;
const int SAMPLE_TIME   =    10000;
const int ALARM_DELAY   =     3000;
const int ALARM_RUNNING =    30000;
const int WIFI_TIMEOUT  =     2000;
const int BEEP_DELAY    =        3;
const int BUZZ_DELAY    =     3000;
const int WAITING_TIME =         5;
const int RESET_DELAY   = 21600000;

int fsrSensor;
int controlFSR;
int fsrSensorReload;

int alarmPoint          =      320;
int safeFrom            =      560;
int safeUntil           =      980;

unsigned long duration;
unsigned long controlTime;

long initial_time;
char msg;
boolean response_end;
String message;
String requestHTTP;

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

  controlTime = millis();
  Serial.begin(9600);

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
  SerialESP8266.println("AT+CWMODE?");
  if (SerialESP8266.find("1")) {
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
    if (controlTime > RESET_DELAY) {
      reset();
      Serial.println("Control time was reset");
    }

    digitalWrite(LED_BUILTIN, HIGH);

    fsrSensor = analogRead(FSR_PIN);
    Serial.print("FSR reading: ");
    Serial.println(fsrSensor);

    digitalWrite(LED_BUILTIN, LOW);

    if ((fsrSensor > safeFrom) && (fsrSensor < safeUntil)) {
      Serial.println("Beep!");
      beep();
    } else if ((fsrSensor > alarmPoint) && (fsrSensor <= safeFrom)) {
      Serial.println("Beep! Beep!");
      beep(); beep();
    } else {
      trigger();
    }

    controlTime = millis();
    Serial.print("Control time: ");
    Serial.println(controlTime);
    Serial.println("---------------------");
  }
}


void reset() {
  Serial.println("Reseting");
  digitalWrite(RESET_PIN, LOW);
}


void beep() {
  digitalWrite(ALARM_CONTROL, HIGH);
  delay(BEEP_DELAY);
  digitalWrite(ALARM_CONTROL, LOW);
  delay(ALARM_DELAY);
}


void buzz() {
  digitalWrite(ALARM_CONTROL, HIGH);
  delay(BUZZ_DELAY);
  digitalWrite(ALARM_CONTROL, LOW);
  delay(ALARM_DELAY);
}


void siren() {
  digitalWrite(ALARM_PIN, HIGH);
  Serial.println("The alarm is going off!");
  delay(ALARM_RUNNING);
  reset();
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


void trigger() {
  controlFSR = 0;
  fsrSensorReload = 0;

  while ((fsrSensorReload < alarmPoint) || (fsrSensorReload > safeUntil)) {
    Serial.println("Reading FSR again");
    fsrSensorReload = analogRead(FSR_PIN);
    Serial.print("fsrSensorReload: ");
    Serial.println(fsrSensorReload);

    controlFSR++;
    Serial.print("controlFSR: ");
    Serial.println(controlFSR);
    buzz();

    if (controlFSR >= WAITING_TIME) {
      ifttt();
      siren();
    }
  }
}
