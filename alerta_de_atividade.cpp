#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

/* Leandro Santana
    Projeto final da matéria Fundamentos de Sistemas Embarcados
    Utilizando ESP8266, sensor PIR e um BOT do Telegram.
*/


//ID e senha do wifi
const char* ID = "PORTALNET_D088";
const char* SENHA = "18008920";

// token do BOT que criei no telegram. ( controla o mesmo )
#define BOTtoken "1785103108:AAHu0x9comV_b9O19VHauldebgOPuJMmaws"

//meu ID do telegram
#define CHAT_ID "848773169"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


//Definindo o sensor no pino D5
const int sensor=D5;
//iniciando a variavel de movimento detectado como falso
bool mov_detectado = false;

//Função para modificar a variavel de movimento para verdade ( utiliza o cache da RAM interna )
void IRAM_ATTR DetectaMovimento() {
  mov_detectado = true;
}

void setup() {
  Serial.begin(115200);

  // coloca telegram como confiavel
  client.setTrustAnchors(&cert);

  pinMode(sensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor), DetectaMovimento, RISING);

  // Entrando no wifi
  Serial.print("Conectando a: ");
  Serial.println(ID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ID, senha);

  //ip
  Serial.print("IP : ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "BOT INICIOU", "");

}

void loop(){
    
}


  
