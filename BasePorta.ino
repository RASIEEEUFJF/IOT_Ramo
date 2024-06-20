/*código de desenvolvimento do projeto de IOT do capítulo de robótica eletrônica do IEEE da UFJF 

*/
// Inclusão das bibliotecas
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configração do WiFi
char ssid []= "IEEE";  // SSID Wifi
char senha []= "REieeeUFJF2023";  // Senha Wifi

// Variáveis de Server e Status do LED
ESP8266WebServer server(80); 

bool LEDstatus = LOW;
int luz = 5; // variável lâmpada 
// afim de evitar error evite usar as portas genéricas do nodemcu 1,2,3,15,13
bool lampada_status = LOW;
int conexao = 115200;

void conectarWiFi(char SSID[], char SENHA[]){
  
  Serial.print("Conectando a rede");
  Serial.println(SSID);

  WiFi.begin(SSID, SENHA);
  while(WiFi.status () != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
    
  Serial.println(" ");
  Serial.println("WiFi Conectado");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
  }


void setup(){
  // Inicia Serial e LED
  Serial.begin(conexao);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(luz, OUTPUT); 
  Serial.println("iniciado");
  conectarWiFi(ssid, senha);
  // Configura Handles do Server e Inicia Server
      //Nesta função aqui, toda vez que o botão é apertado no site ele chama essa função que atualiza o estatus da variável.
  
  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.on("/lampadaon", handle_lampadaon);
  server.on("/lampadaoff", handle_lampadaoff);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("Servidor HTTP iniciado!");
}
  
void loop(){
  //Serial.println("teste");
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
//Aqui estamos montando um site como uma string que ficará armazenado no IP do Roteador que conectamos.
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
// muito interessante observar que o site é todo um bloco de String que que adicionamos itens com funções.
