#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

//EEPROM
void EEPROM_limpaEEPROM();
void EEPROM_gravaNovaStringEEPROM(String novaEEPROM);
char * EEPROM_getEEPROM(char* buffer);
String EEPROM_getValueEEPROM(int hash);
//EEPROM

//ADMIN
ESP8266WebServer server(80);
void Controlador_modoAdmin();
//ADMIN

// MODO DE OPERACAO DO CONTROLADOR
bool modoConfiguracao = false;
int eepromMax         = 250;



void setup() {
  
  Serial.begin(115200);
  EEPROM_limpaEEPROM();
  EEPROM_gravaNovaStringEEPROM("#A#Venizao#venizao123#89#admin");
  delay(10);
  
  //String config = String(EEPROM_getEEPROM());  
  String operacao = EEPROM_getValueEEPROM(1); 
    delay(10);
  String ssid     = EEPROM_getValueEEPROM(2); 
      delay(10);
  String pass     = EEPROM_getValueEEPROM(3); 
   
  Serial.println("Operacao: "+operacao+" SSID: "+ssid+" PASSWORD: "+pass);
  
  //server = Controlador_modoAdmin();
  Serial.println("MODO ADMIN ATIVADO");
  Controlador_modoAdmin();

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

  server.handleClient();
}

