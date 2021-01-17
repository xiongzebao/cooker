
#include <ArduinoJson.h>
#define LED 13
#define COOKER 2 //D2


// Toggle LED on pin 13 each second
#include <MsTimer2.h>
char json[] = "{\"type\":\"gps\", \"result_data\":[{\'name\':\'xb\',\'time\':60},{\'name\':\'obug\',\'time\':120}]}";
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

DynamicJsonDocument doc(1024);


unsigned count = 0;
void flash() {
  count++;
  long  on  = doc["result_data"][0]["time"];
  long off = doc["result_data"][1]["time"];
  Serial.println(count);
    Serial.println(on);
  if(on == count) {
    digitalWrite(COOKER, LOW);
  }
  if(off ==count) {
    digitalWrite(COOKER, HIGH);
  }
}

void setup() {
  deserializeJson(doc, json);
  MsTimer2::set(1000, flash); // 500ms period
  MsTimer2::start();
  pinMode(COOKER, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(COOKER, HIGH);
  Serial.begin(115200);
}

void loop() {
  if (stringComplete) {
    Serial.println(inputString);
    inputString = "";
    stringComplete = false;
  }
}

void parseData() {

}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
