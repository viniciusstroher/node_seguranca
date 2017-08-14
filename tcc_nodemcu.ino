#include <EEPROM.h>
#include <ESP8266WiFi.h>

const char* ssid     = "Venizao";
const char* password = "venizao123";
const int porta      = 80;

//servidor http
WiFiServer server(porta);

// INICIA struct e metodos do outro sketch util

// MODO DE OPERACAO DO CONTROLADOR
bool modoConfiguracao = false;
int eepromMax=250;
void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);
  delay(10);
  //CLEAR
  for (int i = 0 ; i < eepromMax ; i++) {
    EEPROM.write(i, 0);
  }
  
  
  
  //SSID_WIFI#SENHA_WIFI#PORTA_ADMIN#SENHA_ADMIN#PIN1#PIN2
  String configStringEEPROM = "Venizao#venizao123#89#admin";
  char configEEPROM[ eepromMax];
  configStringEEPROM.toCharArray(configEEPROM,sizeof(configEEPROM));  
  
  //WRITE
  for (int i2= 0 ; i2 < strlen(configEEPROM) ; i2++) {
    EEPROM.write(i2, configStringEEPROM[i2]);
  }
  
  
  
  //READ
  Serial.println("EEPROM");
  for (int i3 = 0; i3 < eepromMax; ++i3)
  {
    Serial.print(char(EEPROM.read(i3)));
  }

  EEPROM.commit();
  EEPROM.end();
  
  /*const char * eepromload = EEPROM.get(0, configStringEEPROM[i2]);
  

  if(strlen(wifiSSID) == 0){
    modoConfiguracao = true;
    Serial.println("Ativando modo de configuraçao.");

    String SSID = "Venizao";
    char SSID_CHAR[50];
    SSID.toCharArray(SSID_CHAR,sizeof(SSID_CHAR));
    EEPROM.put(0, SSID_CHAR);
    EEPROM.commit();

    //storeStruct(&configuration, sizeof(configuration));
  }else{
     Serial.println("Ativando modo de operação para ssid: ");
  }
  //#SE ESTIVER OPERANDO
  //INICIA UM SERVIDOR WEB PARA VERIFICAR SE VEM O COMANDO DE RESET E modoConfiguracao= true , em modo de operaçao ele eh false
  
  //#SE NAO TA OPERANDO
  //CRIA REDE ADHOC PARA UM DISPOSITIVO AUTENTICAR NA REDE E PODER ALTERAR O INGRESSO DO WIFI NO CONTROLADOR
  //ATIVAR REDE ADHOC E PERMITIR CONEXAO PARA EDIÇAO DOS PARAMETROS DO ADMIN

  //INICIA SERVIDOR INTERNO PARA CONFIGURAÇAO DO CONTROLADOR E GRAVAR DADOS NA EPROM
  //server.begin();
  //Serial.println("Iniciando servidor de administraçao");
    */
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
