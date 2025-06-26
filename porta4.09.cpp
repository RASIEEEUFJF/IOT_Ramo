/*----------------------------------------------------------------------------------------------------------------------------------------
Código mais atualizado da porta e que roda na segurança simples apenas com a senha do wifi do esp.
Código funcionando e sendo utilizado no período desde de a implantação da porta até o momento atual (25/06/2025)
----------------------------------------------------------------------------------------------------------------------------------------*/





#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configuração do WiFi
const char* ssid = "IEEE_AP";  // SSID do ponto de acesso
const char* password = "123456789";  // Senha do ponto de acesso

// Variáveis de Server e Status do LED
ESP8266WebServer server(80); 

int conexao = 115200;
int lampada = 5; // d1 variável lâmpada
int porta = 4; // d2 variável porta
int botao_porta = 14; // d5
int botao_lampada = 12; // d6
int buzzer = 13; //d7
int led_conexao = 15; //d8
bool lampada_status = LOW;
bool porta_status = LOW;

void setup() {
  // Inicia Serial e LED
  Serial.begin(conexao);
  pinMode(porta, OUTPUT);
  pinMode(lampada, OUTPUT); 
  pinMode(botao_porta, INPUT_PULLUP); 
  pinMode(botao_lampada, INPUT_PULLUP); 
  pinMode(led_conexao, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.println("Iniciando ponto de acesso...");
  
  // Configura o NodeMCU como ponto de acesso
  digitalWrite(buzzer, HIGH);
  delay(100);
   digitalWrite(buzzer, LOW);
  delay(100);
   digitalWrite(buzzer, HIGH);
  delay(100);
   digitalWrite(buzzer, LOW);
  delay(100);
   digitalWrite(buzzer, HIGH);
  delay(100);
   digitalWrite(buzzer, LOW);
  delay(100);
  WiFi.softAP(ssid, password);
  Serial.println("Ponto de Acesso Configurado");
  Serial.print("IP do Ponto de Acesso: ");
  Serial.println(WiFi.softAPIP());

  // Configura Handles do Server e Inicia Server
  server.on("/", handle_OnConnect);
  server.on("/portaon", handle_portaon);
  server.on("/portaoff", handle_portaoff);
  server.on("/lampadaon",  handle_lampadaon);
  server.on("/lampadaoff", handle_lampadaoff);  
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("Servidor HTTP iniciado!");
}

void loop() {
  // Verifica dispositivos conectados
  server.handleClient();
 if (digitalRead (14) == LOW){
  handle_portaon();
  }
  if ((digitalRead (12) == LOW)&&(lampada_status==LOW)){
    handle_lampadaon();}
  if ((digitalRead (12) == LOW)&&(lampada_status==HIGH)){
    handle_lampadaoff();
   
  }
  }



// FUNÇÕES HANDLE PARA HTML SERVER

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(porta_status, lampada_status));
}

void handle_portaon() {
  porta_status = HIGH;
   digitalWrite(buzzer, HIGH);
   delay(100);
   digitalWrite(buzzer, LOW);
  digitalWrite(porta, porta_status);
  delay(5000);  
  handle_portaoff();
}

void handle_portaoff() {
  porta_status = LOW;
  digitalWrite(porta, porta_status);
  server.send(200, "text/html", SendHTML(porta_status, lampada_status));
}
void handle_lampadaon() {
  lampada_status = HIGH;
  digitalWrite(lampada, lampada_status);
  server.send(200, "text/html", SendHTML(porta_status, lampada_status));
}

void handle_lampadaoff() {
  lampada_status = LOW;
  digitalWrite(lampada, lampada_status);
  server.send(200, "text/html", SendHTML(porta_status, lampada_status));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
  digitalWrite(led_conexao, HIGH);
}

// Aqui estamos montando um site como uma string que ficará armazenado no IP do Roteador que conectamos.
String SendHTML(bool porta, bool lampada) {
  String ptr = "<!DOCTYPE html>\n";
  ptr += "<html>\n";
  ptr += "<head>\n";
  ptr += "<style>\n";
  ptr += "    body {\n";
  ptr += "        font-family: Arial, sans-serif;\n";
  ptr += "        background-color: #b9ffff;\n";
  ptr += "        text-align: center;\n";
  ptr += "        font-size: 40px;\n";
  ptr += "    }\n";
  ptr += "    h1 {\n";
  ptr += "        color: #333;\n";
  ptr += "    }\n";
  ptr += "    p {\n";
  ptr += "        color: #666;\n";
  ptr += "    }\n";
  ptr += "    input[type='button'] {\n";
  ptr += "        background-color: #086ca4;\n";
  ptr += "        border: none;\n";
  ptr += "        color: white;\n";
  ptr += "        padding: 40px 0;\n"; // Aumenta o padding para botões maiores
  ptr += "        text-align: center;\n";
  ptr += "        text-decoration: none;\n";
  ptr += "        display: block;\n"; // Faz com que os botões sejam exibidos como blocos
  ptr += "        font-size: 50px;\n"; // Aumenta o tamanho da fonte
  ptr += "        border-radius: 5px;\n";
  ptr += "        margin: 20px auto;\n"; // Centraliza os botões e adiciona margem
  ptr += "        width: 90%;\n"; // Define a largura dos botões para 90% da tela
  ptr += "        height: 200px;\n"; // Define a altura dos botões para 200px
  ptr += "    }\n";
  ptr += "</style>\n";
  ptr += "<title>Controle do LED</title>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1><img src='https://th.bing.com/th/id/OIP.K3it6ygEsOPHdB23WcRuEAHaCd?rs=1&pid=ImgDetMain'></h1>";
  ptr += "<h1>Gerenciamento via IOT</h1>\n";
  ptr += "<p>Botoes.</p>\n";
  ptr += "<form method=\"get\">\n";
  if (lampada)
    ptr += "<input type=\"button\" value=\"APAGAR LAMPADA\" onclick=\"window.location.href='/lampadaoff'\">\n";
  else
    ptr += "<input type=\"button\" value=\"ACENDER LAMPADA\" onclick=\"window.location.href='/lampadaon'\">\n";
  if (porta)
    ptr += "<input type=\"button\" value=\"FECHAR PORTA\" onclick=\"window.location.href='/portaoff'\">\n";
  else
    ptr += "<input type=\"button\" value=\"ABRIR PORTA\" onclick=\"window.location.href='/portaon'\">\n";
  ptr += "</form>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  //Serial.println(ptr); // Adiciona depuração para verificar o HTML gerado
  return ptr;
}
