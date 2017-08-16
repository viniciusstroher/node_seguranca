#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

ESP8266WebServer server;

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

ESP8266WebServer Controlador_modoAdmin(){
 
  Serial.println("MODO ADMIN ATIVADO");
  WiFi.softAP("SYS_SEGURANCA", "teste");
  
  ESP8266WebServer server(80);
  IPAddress myIP = WiFi.softAPIP();
  
  Serial.print("AP IP: ");
  Serial.println(myIP);
  
  server.on("/", handleRoot);
  server.begin();

  return server;
}
 
void Controlador_modoOperacao(){
  WiFi.mode(WIFI_STA);
  //Configs da EEPROM
  WiFi.softAP("","");
  WiFi.begin();
}

