#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
void(* resetFunc) (void) = 0;
void handleRoot() {
  server.send(200, "text/html", "<center><h1>Pagina de adminstração.<br/><a href=\"\/admin\">Clique aqui para acessar o admin.</a></h1></center>");
}

void handleAdminGET(){
  String valorConfig = String(EEPROM_getEEPROM()); 
  delay(10);
  server.send(200, "text/html", "<form method=\"POST\" action=\"\/admin\"><center>String de configuração: <input type=\"text\" name=\"stringConfig\" value=\""+valorConfig+"\" /><input type=\"submit\" value=\"Salvar\"/> </center></form>    <br/><br/>     <form method=\"POST\" action=\"\/reiniciar\"><center><input type=\"submit\" value=\"Reiniciar\"/> </center></form>");
}

void handleAdminPOST(){
  String novaValorConfig = server.arg("stringConfig");
 
  EEPROM_gravaNovaStringEEPROM(novaValorConfig);
  delay(10);
  server.send(200, "text/html", "<center><h1>Configuração salva.<br/><a href=\"\/admin\">Volta para admin.</a></h1></center>");
}

void handleReiniciarPOST(){
  //reiniciar
  server.send(200, "text/html", "<center><h1>Voltar a adminstração.<br/><a href=\"\/admin\">Clique aqui para acessar o admin.</a></h1></center>");
  Controlador_resetaControlador();
}

void Controlador_modoAdmin(){
 
  Serial.println("MODO ADMIN ATIVADO");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("SYS_SEGURANCA");
  IPAddress myIP = WiFi.softAPIP();
  
  Serial.print("AP IP: ");
  Serial.println(myIP);
  
  server.on("/",      handleRoot);
  server.on("/admin",HTTP_GET, handleAdminGET);
  server.on("/admin",HTTP_POST,handleAdminPOST);
  server.on("/reiniciar",HTTP_POST,handleReiniciarPOST);
  server.begin();

}
 
void Controlador_modoOperacao(String ssid,String pass,String ip,String porta){
  Serial.begin(115200);
  Serial.println("EM DESENVOLVIMENTO");
  //Configs da EEPROM
  //WiFi.softAP("","");
  //WiFi.begin();
}

void Controlador_resetaControlador(){
  resetFunc();
}

