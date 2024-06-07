/*
      Programa Aciona LED via WiFI
      Conexão do NodeMCU no Wifi e aciona o Built-In LED por uma página Http local

      Componentes:
        - NodeMCU ESP8266

      Versão 1.0 - Versão inicial via HTTP Local - 28/Jan/2021

 *    * Criado por Cleber Borges - FunBots - @cleber.funbots  *     *

      Instagram: https://www.instagram.com/cleber.funbots/
      Facebook: https://www.facebook.com/cleber.funbots
      YouTube: https://www.youtube.com/channel/UCKs2l5weIqgJQxiLj0A6Atw
      Telegram: https://t.me/cleberfunbots

*/

// Inclusão das bibliotecas
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configração do WiFi
const char* ssid = "IEEE";  // SSID Wifi
const char* password = "REieeeUFJF2023";  // Senha Wifi

// Variáveis de Server e Status do LED
ESP8266WebServer server(80);
bool LEDstatus = LOW;
int luz = 1;
bool lampada_status = LOW;
void setup() {
  // Inicia Serial e LED
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(luz,OUTPUT);

  // Inicia Conexão WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Aguarda Conexão e Informa IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Rede WiFi: ");
  Serial.println(ssid);
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  delay(100);

  // Configura Handles do Server e Inicia Server
  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.on("/lampadaon", handle_lampadaon);
  server.on("/lampadaoff", handle_lampadaoff);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("Servidor HTTP iniciado!");

}

void loop() {
  server.handleClient();    // Faz o Handle
  if (LEDstatus)            // Checa se LED deve acender
    digitalWrite(LED_BUILTIN, HIGH);  
    
   else
    digitalWrite(LED_BUILTIN, LOW);
    

  if(lampada_status)
    digitalWrite(luz,HIGH);
  else
    digitalWrite(luz,LOW);

}

// FUNÇÕES HANDLE PARA HTML SERVER

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(LEDstatus, lampada_status));
}

void handle_ledon() {
  LEDstatus = HIGH;
  server.send(200, "text/html", SendHTML(LEDstatus, lampada_status));
}

void handle_lampadaon(){
  lampada_status = HIGH;
  server.send(200, "text/html", SendHTML(LEDstatus, lampada_status));
}

void handle_lampadaoff(){
  lampada_status = LOW;
  server.send(200, "text/html", SendHTML(LEDstatus, lampada_status));
}

void handle_ledoff() {
  LEDstatus = LOW;
  server.send(200, "text/html", SendHTML(LEDstatus, lampada_status));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(bool led, bool lampada) {
  String ptr = "<!DOCTYPE html>\n";
  ptr += "<html>\n";
  ptr += "<head>\n";
  ptr += "<title>Controle do LED</title>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>PORTA</h1>\n";
  ptr += "<p>OI, TRABALHE AQUI PARA ABRIR E FECHAR A PORTA.</p>\n";
  ptr += "<form method=\"get\">\n";
  
  if (lampada)
     ptr += "<input type=\"button\" value=\"APAGAR LAMPADA\" onclick=\"window.location.href='/lampadaoff'\">\n";
  else
      ptr += "<input type=\"button\" value=\"ACENDER LAMPADA\" onclick=\"window.location.href='/lampadaon'\">\n";
  if (led)
    ptr += "<input type=\"button\" value=\"ABRIR PORTA\" onclick=\"window.location.href='/ledoff'\">\n";
  else
    ptr += "<input type=\"button\" value=\"FECHAR PORTA\" onclick=\"window.location.href='/ledon'\">\n";
  ptr += "</form>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
