
#include <ArduinoJson.h>
#define LED 13
char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete


DynamicJsonDocument doc(1024);
const char* sensor = doc["sensor"];
long time          = doc["time"];
double latitude    = doc["data"][0];
double longitude   = doc["data"][1];



void setup() {
  

deserializeJson(doc, json);
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (stringComplete) {
    Serial.println(inputString);
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void parseData(){
  
}



void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
