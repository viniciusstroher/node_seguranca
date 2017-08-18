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
void Controlador_resetaControlador();
//ADMIN

//VARIAVEIS
int  eepromMax         = 250;
String operacao;
//PINOS
int  PINO_RESET = 16;       //D0
int  PINO_FUNCAO_RESET = 5; //D1

void setup() {
  pinMode(PINO_RESET, INPUT);
  digitalWrite(PINO_RESET, LOW);
  pinMode(PINO_FUNCAO_RESET, OUTPUT);
  Serial.begin(115200);
    
  operacao        = EEPROM_getValueEEPROM(1); 
  delay(10);
  String ssid     = EEPROM_getValueEEPROM(2); 
  delay(10);
  String pass     = EEPROM_getValueEEPROM(3); 
   
  Serial.println("Operacao: "+operacao+" SSID: "+ssid+" PASSWORD: "+pass);
  
  //server = Controlador_modoAdmin();
  if(operacao.equals("A")){
    Serial.println("MODO ADMIN ATIVADO");
    Controlador_modoAdmin();

  }
  if(operacao.equals("O")){
    Serial.println("MODO OPERACAO ATIVADO");
    Controlador_modoOperacao();
  }

}
 
void loop() {
  int fazerReset = digitalRead(PINO_RESET);
  
  if(fazerReset == 1){
     //LIGADOR O PINO D0 NO 3V com um botao e ligado 10k no ground
     EEPROM_limpaEEPROM();
     EEPROM_gravaNovaStringEEPROM("#A#Venizao#venizao123#89#admin");
     delay(100);
     Serial.println("Resetando configs do controlador.");
     Controlador_resetaControlador();
  }
  
  if(operacao.equals("A")){
    server.handleClient();
  }
}



