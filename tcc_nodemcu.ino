#include <EEPROM.h>
#include <ESP8266WiFi.h>

const char* ssid     = "Venizao";
const char* password = "venizao123";
const int porta      = 80;

//servidor http
WiFiServer server(porta);

// INICIA struct e metodos do outro sketch util
// Configuraçao para EEprom
struct Configuration {
  //IN - sensores
  int pin1;
  int pin2;
  int pin3;
  int pin4;
  
  //OUT - BUZZER
  int pin5;
  
  //CONTROLADOR
  char* ssid_wifi_controlador;
  char* senha_wifi_controlador;
  char* senha_controlador;
  char* porta_controlador;
  char* ip_controlador;
  
  //API - APP - SMARTPHONE
  char* ip_server;
  char* porta_server;
  char* senha;
  
} configuration;

// MODO DE OPERACAO DO CONTROLADOR
bool modoConfiguracao = false;
void setup() {
  Serial.begin(115200);
  delay(10);
  
  uint8_t codeRunningForTheFirstTime = EEPROM_readAnything(0, configuration); // le da eeprom a estrutura de dados

  if (codeRunningForTheFirstTime) {
    modoConfiguracao = true;
    Serial.println("Ativando modo de configuraçao.");
    /* OK first time running, set defaults */
    configuration.pin1 = 0;
    configuration.pin2 = 0;
    configuration.pin3 = 0;
    configuration.pin4 = 0;
    configuration.pin5 = 0;

    configuration.ssid_wifi_controlador  = "";
    configuration.senha_wifi_controlador = "";
    configuration.senha_controlador = "";
    configuration.porta_controlador = "";
    configuration.ip_server         = "";
    configuration.porta_server      = "";
    configuration.senha_server      = "";

    EEPROM_writeAnything(0, configuration);


    //CRIA REDE ADHOC PARA UM DISPOSITIVO AUTENTICAR NA REDE E PODER ALTERAR O INGRESSO DO WIFI NO CONTROLADOR
    //ATIVAR REDE ADHOC E PERMITIR CONEXAO PARA EDIÇAO DOS PARAMETROS DO ADMIN

    //INICIA SERVIDOR INTERNO PARA CONFIGURAÇAO DO CONTROLADOR E GRAVAR DADOS NA EPROM
    //server.begin();
    //Serial.println("Iniciando servidor de administraçao");
    
  }
  //INICIA UM SERVIDOR WEB PARA VERIFICAR SE VEM O COMANDO DE RESET E modoConfiguracao= true , em modo de operaçao ele eh false
    
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
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
  */
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
  Serial.println("Client disonnected");
}
