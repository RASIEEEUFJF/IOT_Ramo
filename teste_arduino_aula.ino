#include <ESP8266WiFi.h>
char ssid [] = "IEEE";
char senha [] = "REieeeUFJF2023";
WiFiServer server (80);
void conectarWiFi (char SSID[],char SENHA[]){

Serial.print("conectando");
Serial.println(SSID);
WiFi.begin(SSID,SENHA);

while(WiFi.status () != WL_CONNECTED){
  delay(500);
  Serial.print(".");
}
Serial.println("wifi conectado");

Serial.println("Enderenço de ip: ");

Serial.println(WiFi.localIP());
}
void setup() {
  Serial.begin(115200);
  delay(10);
conectarWiFi(ssid,senha);
server.begin();
Serial.println("servidor inicializado");
}

void loop() {
WiFiClient client = server.available();
if(!client){
  return;
}
while(!client.available()){
  delay(1);
}
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<meta http-equiv='refresh' content='2'>");
client.println("<h1>Introducao ao iot com esp8266</h1>");
client.println("<h2>ola!</h2>");
client.println("</html>");
}
