#include <ESP8266WiFi.h>

void modoAdmin(){
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("", "");
}
 
void modoOperacao(){
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("","");
}

