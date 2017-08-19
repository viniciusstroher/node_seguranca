#include <EEPROM.h>
#define eepromMax 250

//MODO DE OPERACAO (A-ADMIN, O-OPERACAO)#SSID_WIFI#SENHA_WIFI#IP#PORTA#
#define configPadrao "#A#Venizao#venizao123#testesmart.ddns.net#10000#0"
void EEPROM_limpaEEPROM(){
  EEPROM.begin(512);

  for (int i = 0 ; i < eepromMax ; i++) {
    EEPROM.write(i, 0);
  }
  
  EEPROM.commit();
  EEPROM.end();
}

void EEPROM_gravaNovaStringEEPROM(String novaEEPROM){
   EEPROM.begin(512);
  char configEEPROM[ eepromMax];
  novaEEPROM.toCharArray(configEEPROM,sizeof(configEEPROM));  
  //WRITE
  for (int i2= 0 ; i2 < strlen(configEEPROM) ; i2++) {
    
    EEPROM.write(i2, configEEPROM[i2]);
  }
  
  EEPROM.commit();
  EEPROM.end();
}

char * EEPROM_getEEPROM(){
  EEPROM.begin(512);
 
  char eeprom[eepromMax];
  char b;
  for (int i3 = 0; i3 < eepromMax; ++i3)
  {
    b = char(EEPROM.read(i3));
    eeprom[i3]=b;
    
    ESP.wdtFeed();
  }
  EEPROM.commit();
  EEPROM.end();
  
  return eeprom;
}

String EEPROM_getValueEEPROM(int hash){
  EEPROM.begin(512);
  Serial.begin(115200);
  char eeprom[eepromMax],eepromRetorno[20];
  char b;
  eepromRetorno[0] = ' ';
  
  bool primeiroHash = false;
  int  hashCount=0;
  int eepromRetornoIndex =0;
  
  for (int i3 = 0; i3 < eepromMax; ++i3)
  {
    b = char(EEPROM.read(i3));
    if(b=='#'){
      hashCount++;
      if(!primeiroHash && hashCount==hash){
        primeiroHash=true;
      }else if(primeiroHash){
        eepromRetorno[eepromRetornoIndex] = '\0';
        break;
      }
    }
    
    if(primeiroHash && b!='#'){
      
      eepromRetorno[eepromRetornoIndex] = b;
      eepromRetornoIndex++;
    }
    ESP.wdtFeed();
  }
  EEPROM.commit();
  EEPROM.end();

  return String(eepromRetorno);
}
