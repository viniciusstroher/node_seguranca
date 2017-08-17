#include <EEPROM.h>
#define eepromMax 250

//MODO DE OPERACAO (A-ADMIN, O-OPERACAO)#SSID_WIFI#SENHA_WIFI#PORTA_ADMIN#SENHA_ADMIN#PIN1#PIN2
#define configPadrao "Venizao#venizao123#89#admin"
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
    
   
  }
  EEPROM.commit();
  EEPROM.end();
  
  return eeprom;
}

char * EEPROM_getValueEEPROM(int hash){
  EEPROM.begin(512);
 
  char eeprom[eepromMax],eepromRetorno[20];
  char b;
  
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
        break;
      }
    }else{
      Serial.println("B:"+String(b));
      eepromRetorno[eepromRetornoIndex] = b;
      eepromRetornoIndex++;
    }

  }
  EEPROM.commit();
  EEPROM.end();
  
  return eepromRetorno;
}
