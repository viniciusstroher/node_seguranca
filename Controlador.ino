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
  //remover se der problema
  WiFi.mode(WIFI_STA);
  Serial.println("MODO OPERAÇÃO ATIVADO");
  //Configs da EEPROM
   WiFi.begin(ssid.c_str(), pass.c_str());
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
  
}

void Controlador_enviaDadosServer(String nomeDoControlador,String ip,String porta,String senhaApi,String hook,String data){
  if (!client.connect(ip.c_str(), porta.toInt())) {
    Serial.println("Falha de conexao no servidor "+ip+":"+porta+" "+hook);
    return;
  }else{
    Serial.println("Enviando dados ao servidor "+ip+":"+porta+" "+hook);
    String httpPost = "POST " + hook + " HTTP/1.1\r\n" +
                 "Host: " + ip + "\r\n" +
                 "User-Agent: MICROCONTROLADOR\r\n" +
                 "Connection: close\r\n"
                 "Api-Key: "+senhaApi+"\r\n"+
                 "agente:"+nomeDoControlador+"\r\n"+ 
                 "Content-Type: application/json\r\n"+
                 "Content-Length: "+data.length()+"\r\n\r\n"+
                  data;
    client.print(httpPost);
               
    Serial.println(httpPost);
    Serial.println("Recebendo dados ao servidor");
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        break;
      }
    }
    String line = client.readStringUntil('\n');
    Serial.println("RETORNO SERVER: "+line);
  }
  
}

void Controlador_resetaControlador(){
  resetFunc();
}

