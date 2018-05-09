#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Adafruit_Trellis.h"

#define MAX_STANDBY_TIME  60000
#define MAX_RANDOM_ANIMATION_TIME  1000
#define NUM_KEYS  16

const char* ssid = "";
const char* password = "";
char* mqttServer = "192.168.1.133";
const int mqttPort = 1883;
const char* mqttUser = "admin";
const char* mqttPassword = "admin";
const char* mqttPubTopic = "fromAtreyu";
const char* mqttSubTopic = "toAtreyu";

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);
int currentPage = 0;
long lastPress = 0;
long lastRandomAnimation = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("ATREYU - Applescript TREllis keYboard bUddy");
  randomSeed(analogRead(0));
  trellis.begin(0x70);
  trellis.setBrightness(15);
  displayInitAnimation();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    displayWifiAnimation();
  }
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    if(client.connect("ESP8266Client", mqttUser, mqttPassword)) {
      displayConnectionSuccessAnimation();
    } else {
      displayConnectionErrorAnimation();
      if (trellis.readSwitches() && trellis.isKeyPressed(15)) {
        changeIPMode();  
      }
    }
  }
  client.subscribe(mqttSubTopic);
}

void changeIPMode() {  
  displayNumPad();
  int keyPresses = 0;
  while (keyPresses < 4) {
    if (trellis.readSwitches()) {
      for (int key = 0; key < NUM_KEYS; key++) {
        if (trellis.isKeyPressed(key)) {
          int ipNumber = -1;
          if (key >= 0 && key <= 2) {
            ipNumber = key + 1;
          } else if (key >= 4 && key <= 6) {
            ipNumber = key;
          } else if (key >= 8 && key <= 10) {
            ipNumber = key - 1;
          } else if (key == 13) {
            ipNumber = 0;
          }
          if (ipNumber > -1) {
            if (keyPresses == 0) { 
              mqttServer[8] = ipNumber + '0';
            } else {
              mqttServer[9 + keyPresses] = ipNumber + '0';
            } 
            keyPresses++;
          }
        }
      }    
    }
    delay(30);
  }
  for (int i = 0; i < 3; i++) {
    displayWifiAnimation();  
  }
}

void callback(char* topic, byte* payload, unsigned int length) {  
  String message;
  for(int i = 0; i < length; i++) {
     message = message + (char)payload[i];
  }
  Serial.println(message);
  if (message == "develop") {
    currentPage = 1;
  } else if (message == "browser") {
    currentPage = 2;
  } else if (message == "edit") {
    currentPage = 3;
  } else {
    currentPage = 0;
  }
  displayChangePageAnimation();
  lastPress = millis();
}

void loop() {    
  if (millis() - lastPress > MAX_STANDBY_TIME) {
    if (millis() - lastRandomAnimation > MAX_RANDOM_ANIMATION_TIME) {      
      trellis.clear();
      displayRandomAnimation();
      lastRandomAnimation = millis();
    }
  } else {
    trellis.clear();
    trellis.setLED(currentPage);
  }
  if (trellis.readSwitches()) {
    for (int key = 0; key < NUM_KEYS; key++) {      
      if (key < 4 && trellis.justReleased(key)) {
        if (millis() - lastPress < MAX_STANDBY_TIME) {
          currentPage = key;
        }
        lastPress = millis();
      } else {
        if (trellis.justPressed(key)) {
          trellis.setLED(key);          
        }
        if (trellis.justReleased(key)) {
          trellis.clrLED(key);   
          if (millis() - lastPress < MAX_STANDBY_TIME) {
            displayButtonReleaseAnimation(key);
            char buf[8];
            itoa((currentPage * (NUM_KEYS - 4)) + (key - 4), buf, 10);  
            client.publish(mqttPubTopic, buf);      
          }
          lastPress = millis();
        }
      }
    }
  }
  trellis.writeDisplay();
  client.loop();
  delay(30);
}

void displayInitAnimation() {
  for (uint8_t i=0; i<NUM_KEYS; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
  for (uint8_t i=0; i<NUM_KEYS; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
}

void displayWifiAnimation() {
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

void displayConnectionSuccessAnimation() {
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

void displayConnectionErrorAnimation() {
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

void displayNumPad() {
  trellis.clear();
  trellis.setLED(0);
  trellis.setLED(1);
  trellis.setLED(2);
  trellis.setLED(4);
  trellis.setLED(5);
  trellis.setLED(6);
  trellis.setLED(8);
  trellis.setLED(9);
  trellis.setLED(10);
  trellis.setLED(13);
  trellis.writeDisplay();
}

void displayRandomAnimation() {
  for (int i = 0; i < NUM_KEYS; i++) {
    if (random(0, 2) == 1) {
      trellis.setLED(i);
    } else {
      trellis.clrLED(i);
    }
  }
}

void displayButtonReleaseAnimation(int button) {
  int row = button / 4;
  int column = button % 4;  
  for (int i = 1; i < 4; i++) {
    trellis.clear();
    trellis.setLED(currentPage);
    if (row + i < 4) {
      trellis.setLED(button + (i * 4));
    }
    if (row - i >= 0) {
      trellis.setLED(button - (i * 4));
    }
    if (column + i < 4) {
      trellis.setLED(button + i);
    }
    if (column - i >= 0) {
      trellis.setLED(button - i); 
    }
    trellis.writeDisplay();
    delay(100);
  }
  trellis.clear();
  trellis.setLED(currentPage);
  trellis.writeDisplay();
}

void displayChangePageAnimation() {  
  for (int i = 0; i < 4; i++) {
    trellis.clear();
    trellis.setLED(i);
    trellis.setLED(4 + i);
    trellis.setLED(8 + i);
    trellis.setLED(12 + i);
    trellis.writeDisplay();
    delay(50);
  }    
}
