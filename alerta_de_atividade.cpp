#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ID = "PORTALNET_D088";
const char* SENHA = "18008920";

const int sensor=11;
bool mov_detectado = false;

void ICACHE_RAM_ATTR DetectaMovimento() {
  mov_detectado = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(sensor, INPUT_PULLUP);


}

void loop(){
    
}


  
