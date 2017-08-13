#include <EEPROM.h>
#include <Arduino.h>  // for type definitions

// Configuraçao para EEprom
typedef struct Configuration {
  //IN - sensores
  int pin1;
  int pin2;
  int pin3;
  int pin4;
  
  //OUT - BUZZER
  int pin5;
  
  //CONTROLADOR
  char* ssid_controlador;
  char* senha_controlador;
  char* porta_controlador;
  char* ip_controlador;
  
  //API - APP - SMARTPHONE
  char* ip_server;
  char* porta_server;
  char* senha;
  
} configuration;

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}
