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
WiFiClient client;
//CONTROLADOR
void Controlador_modoAdmin();
void Controlador_resetaControlador();
void Controlador_enviaDadosServer(String ip,String porta,String hook,String data);


//VARIAVEIS
int    estadoPorta       = 1;
String nomeControlador   = "SYS_SEG_1";
int    eepromMax         = 250;
String operacao;
String ssid;
String pass;
String ip;
String porta;
String senhaApi;

//PINOS RESET
int  PINO_RESET = 16;       //D0

//PINOS SENSORES
int PINO_SENSOR_MAGNETICO = 5;
int PINO_SENSOR_PIR       = 4;


void setup() {
  pinMode(PINO_RESET, INPUT);
  digitalWrite(PINO_RESET, LOW);
  Serial.begin(115200);

  fazerReset();
    
  operacao        = EEPROM_getValueEEPROM(1); 
  delay(10);
  Serial.println("Operacao: "+operacao);
  /*
   *  
  
  delay(10);
  String porta    = EEPROM_getValueEEPROM(5); 
  Serial.println(" SSID: "+ssid+" PASSWORD: "+pass+" IP: "+ip+" Porta: "+porta);*/

  if(operacao.equals("A")){
    Serial.println("MODO ADMIN ATIVADO");
    
    //CONFIGURA MODO ADMIN
    Controlador_modoAdmin();

  }
  
  if(operacao.equals("O")){
    Serial.println("MODO OPERACAO ATIVADO");
    ssid     = EEPROM_getValueEEPROM(2); 
    delay(10);
    pass     = EEPROM_getValueEEPROM(3); 
    delay(10);
    ip       = EEPROM_getValueEEPROM(4);  
    delay(10);
    porta    = EEPROM_getValueEEPROM(5);  
    delay(10);
    senhaApi = EEPROM_getValueEEPROM(6);  
    delay(10);
    Serial.println("SSID: "+ssid+" Pass: "+pass+" IP:"+ip+" Porta: "+porta+" Senha api: "+senhaApi);

    //CONFIGURA MODO DE OPERACAO
    Controlador_modoOperacao(ssid,pass,ip,porta);
    
    //SETAR PINAGEM DE SENSORES AQUI
    pinMode(PINO_SENSOR_MAGNETICO, INPUT_PULLUP);
    pinMode(PINO_SENSOR_PIR, INPUT_PULLUP);
    digitalWrite(PINO_SENSOR_MAGNETICO,HIGH);
    estadoPorta = digitalRead(PINO_SENSOR_MAGNETICO);
  }

}
 
void loop() {
  fazerReset();
  
  if(operacao.equals("A")){
    server.handleClient();
  }

  if(operacao.equals("O")){
    capturaSensores();
  }
}

void capturaSensores(){
  int estadoSensorMagnetico = digitalRead(PINO_SENSOR_MAGNETICO);
  int estadoSensorPir       = digitalRead(PINO_SENSOR_PIR);
    
  Serial.println("Porta aberta : "+String(estadoSensorMagnetico));
  Serial.println("Movimentacao : "+String(estadoSensorPir));

    
  //VERIFICA SE O SENSOR DA PORTA ESTA ABERTO
  //NO MEU CASO O zero significa o circuito aberto
  if(estadoSensorMagnetico == 0 || estadoSensorPir == 0){  
    if(estadoPorta != estadoSensorMagnetico){
       estadoPorta = estadoSensorMagnetico;
       if(estadoPorta == 0){
          Controlador_enviaDadosServer(nomeControlador,ip,porta,senhaApi,"/pir","{\"pir\":true}");  
       }else{
         Controlador_enviaDadosServer(nomeControlador,ip,porta,senhaApi,"/pir","{\"pir\":false}");  
       }
       Controlador_enviaDadosServer(nomeControlador,ip,porta,senhaApi,"/porta_aberta","{\"magnetico\":true}");  
    }
  
    //VERIFICA SE O SENSOR PIR ESTA CAPTANDO MOVIMENTO
    //NO MEU CASO O zero significa o presença no pir
    if(estadoPorta == 0){
       Controlador_enviaDadosServer(nomeControlador,ip,porta,senhaApi,"/pir","{\"pir\":true}");  
    }
    delay(5000);
  }
}
void fazerReset(){
  int fazerReset = digitalRead(PINO_RESET);
  if(fazerReset == 1){
     //LIGADOR O PINO D0 NO 3V com um botao e ligado 10k no ground
     EEPROM_limpaEEPROM();
     delay(100);
     EEPROM_gravaNovaStringEEPROM("#A#Venizao#venizao123#testesmart.ddns.net#10000#teste#0");
     delay(100);
     Serial.println("Resetando configs do controlador.");
     Controlador_resetaControlador();
  }
}


