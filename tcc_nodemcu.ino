#include <EEPROM.h>
#include <ESP8266WiFi.h>
//DECLARAÇOES DE METODOS

//EEPROM
void EEPROM_limpaEEPROM();
void EEPROM_gravaNovaStringEEPROM(String novaEEPROM);
char * EEPROM_getEEPROM(char* buffer);

//EEPROM

// MODO DE OPERACAO DO CONTROLADOR
bool modoConfiguracao = false;
int eepromMax         = 250;

void setup() {
  //WiFi.softAP(ssid, password);

  Serial.begin(115200);
  EEPROM_limpaEEPROM();
  EEPROM_gravaNovaStringEEPROM("Venizao#venizao123#89#admin");
  delay(10);
  
  String config = String(EEPROM_getEEPROM(0));  
  Serial.println("Config:"+config);
  
  //#SE ESTIVER OPERANDO
  //INICIA UM SERVIDOR WEB PARA VERIFICAR SE VEM O COMANDO DE RESET E modoConfiguracao= true , em modo de operaçao ele eh false
  
  //#SE NAO TA OPERANDO
  //CRIA REDE ADHOC PARA UM DISPOSITIVO AUTENTICAR NA REDE E PODER ALTERAR O INGRESSO DO WIFI NO CONTROLADOR
  //ATIVAR REDE ADHOC E PERMITIR CONEXAO PARA EDIÇAO DOS PARAMETROS DO ADMIN

  //INICIA SERVIDOR INTERNO PARA CONFIGURAÇAO DO CONTROLADOR E GRAVAR DADOS NA EPROM
  //server.begin();
  //Serial.println("Iniciando servidor de administraçao");
    
}
 
void loop() {
  // Check if a client has connected
 /* WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
  /*
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }

// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");  */
}
