#include <ESP8266WiFi.h>

void Controlador_modoAdmin(){
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("Configuração do microcontrolador "+random(1000,9999), "admin");
}
 
void Controlador_modoOperacao(){
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("","");
}

