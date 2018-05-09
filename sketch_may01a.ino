#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Adafruit_Trellis.h"

const char* ssid = "";
const char* password = "";
char* mqttServer = "192.168.1.133";
const int mqttPort = 1883;
const char* mqttUser = "admin";
const char* mqttPassword = "admin";
const int numKeys = 16;

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);
bool shutDownPressed = false;

void setup() {
  Serial.begin(115200);
  trellis.begin(0x70);
  trellis.setBrightness(15);
  displayInit();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    displayWifi();
  }
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    if(client.connect("ESP8266Client", mqttUser, mqttPassword)) {
      displayConnectionSuccess();
    } else {
      displayConnectionError();
      delay(2000);
    }
  }
  client.subscribe("toTrellis");
  client.publish("fromTrellis","1");
  
}

void displayInit() {
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
}

void displayWifi() {
  trellis.setLED(0);
  trellis.writeDisplay();    
  delay(50);
  trellis.clear();
  trellis.setLED(1);
  trellis.setLED(4);
  trellis.writeDisplay();    
  delay(50);
  trellis.clear();
  trellis.setLED(2);
  trellis.setLED(5);
  trellis.setLED(8);
  trellis.writeDisplay();    
  delay(50);
  trellis.clear();
  trellis.setLED(3);
  trellis.setLED(6);
  trellis.setLED(9);
  trellis.setLED(12);
  trellis.writeDisplay();    
  delay(50);
  trellis.clear();
  trellis.setLED(7);
  trellis.setLED(10);
  trellis.setLED(13);
  trellis.writeDisplay();    
  delay(50);
  trellis.clear();
  trellis.setLED(11);
  trellis.setLED(14);
  trellis.writeDisplay();    
  delay(50);
  trellis.clear();
  trellis.setLED(15);
  trellis.writeDisplay();    
  delay(50);
  trellis.clear();
  trellis.writeDisplay();  
  delay(50);
}

void displayConnectionSuccess() {
  for (int i = 4; i < 8; i++) {
    trellis.clear();
    trellis.setLED(i);  
    trellis.writeDisplay();  
    delay(50);
  }
  trellis.clear();    
  trellis.writeDisplay();  
  delay(50);
  for (int i = 11; i >= 8; i--) {
    trellis.clear();
    trellis.setLED(i);  
    trellis.writeDisplay();  
    delay(50);
  }
  trellis.clear();    
  trellis.writeDisplay();  
  delay(50);
}

void displayConnectionError() {
  trellis.clear();
  trellis.setLED(0);
  trellis.setLED(3);
  trellis.setLED(5);
  trellis.setLED(6);
  trellis.setLED(9);
  trellis.setLED(10);
  trellis.setLED(12);
  trellis.setLED(15);
  trellis.writeDisplay();  
  delay(1000);
  trellis.clear();
  trellis.writeDisplay();
}

void callback(char* topic, byte* payload, unsigned int length) {  
  String message;
  for(int i = 0; i < length; i++) {
     message = message + (char)payload[i];
  }
  if (message == "1") {
    trellis.clear();
    trellis.setLED(0);
    trellis.writeDisplay();
  }
  Serial.println(message);
}

void loop() {  
  if (trellis.readSwitches()) {
    for (int i = 0; i < numKeys; i++) {
      if (trellis.justPressed(i)) {
        trellis.setLED(i);
      } 
      if (trellis.justReleased(i)) {
        trellis.clrLED(i);   
        char buf[8];
        itoa(i, buf, 10);
        client.publish("fromTrellis", buf);      
      }
    }    
    trellis.writeDisplay();
  }
  client.loop();
  delay(30);
}
