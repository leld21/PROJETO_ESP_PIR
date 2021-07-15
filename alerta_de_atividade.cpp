#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <time.h>


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

//configurações para o telegram
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


//Definindo o sensor no pino D5
const int sensor=D5;
//iniciando a variavel de movimento detectado como falso
bool mov_detectado = false;

//contador
int cont=0;

//Função para modificar a variavel de movimento para verdade ( utiliza o cache da RAM interna )
void IRAM_ATTR DetectaMovimento() {
  mov_detectado = true;
}

void setup() {
  //inicia o Serial junto com a definição de sua velocidade
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov"); // pega o horario atual e o contigura para UTC-3

  // coloca telegram como confiavel
  client.setTrustAnchors(&cert);

  // o pino do sensor é configurado como entrada
  pinMode(sensor, INPUT_PULLUP);
  //interrupção
  attachInterrupt(digitalPinToInterrupt(sensor), DetectaMovimento, RISING);

  // Entrando no wifi
  Serial.print("Conectando a: ");
  Serial.println(ID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ID, SENHA);

  //aguarda a conecção ao wi-fi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  //mostra o ip
  Serial.print("IP : ");
  Serial.println(WiFi.localIP());

  //sinaliza que o bot iniciou ( pelo telegram ).
  bot.sendMessage(CHAT_ID, "BOT INICIOU", "");

}

void loop(){
  //usa o contador para dizer se o animal saiu ou entrou;
  //se cont for par ele saiu, se for impar ele entrou.
  if(mov_detectado){
    if(cont%2==0){
    time_t now = time(nullptr);
    bot.sendMessage(CHAT_ID, "O pet saiu as:", "");
    // mostra o mês, dia e hora
    bot.sendMessage(CHAT_ID, ctime(&now), "");
    Serial.println("Movimento detectado");
    //reinicia
    mov_detectado = false;
    cont++;
    }else{
    time_t now = time(nullptr);
    bot.sendMessage(CHAT_ID, "O pet voltou as:", "");
    // mostra o mês, dia e hora
    bot.sendMessage(CHAT_ID, ctime(&now), "");
    Serial.println("Movimento detectado");
    //reinicia
    mov_detectado = false;
    cont++;
    }
  }
}
