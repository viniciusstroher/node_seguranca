#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

//EEPROM
void   EEPROM_limpaEEPROM();
void   EEPROM_gravaNovaStringEEPROM(String novaEEPROM);
char * EEPROM_getEEPROM(char* buffer);
String EEPROM_getValueEEPROM(int hash);
//EEPROM

//ADMIN
ESP8266WebServer server(80);
void Controlador_modoAdmin();
//ADMIN

//VARIAVEIS
int  eepromMax         = 250;
//PINOS
int  PINO_RESET = 16;


void setup() {
  pinMode(PINO_RESET, INPUT_PULLUP);

  Serial.begin(115200);
 
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
  int fazerReset = digitalRead(PINO_RESET);
  if(fazerReset == 1){
     //LIGADOR O PINO D0 NO 3V com um botao e ligado 10k no ground
     EEPROM_limpaEEPROM();
     EEPROM_gravaNovaStringEEPROM("#A#Venizao#venizao123#89#admin");
     Serial.println("Resetando configs do controlador.");
  }
   
  server.handleClient();
}

