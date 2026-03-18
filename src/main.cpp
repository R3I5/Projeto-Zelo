/*******************************************************************************
* Real Time Clock com Pinos Customizados no ESP32
*******************************************************************************/
  
//Inclui as bibliotecas
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc; //Objeto rtc da classe DS1307

// Definindo nossos pinos customizados
#define PINO_SDA 27
#define PINO_SCL 14
  
char diasDaSemana[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"}; //Dias da semana

void setup () {
  Serial.begin(115200);                        // Ajustado para o padrão do ESP32
  delay(2000);                                 // Tempo para o monitor serial do Ubuntu conectar
  
  Serial.println("Iniciando o sistema...");
  
  // INICIA O I2C NOS PINOS ESCOLHIDOS ANTES DE CHAMAR O RTC
  Wire.begin(PINO_SDA, PINO_SCL); 

  if (! rtc.begin()) {                         
    Serial.println("RTC NAO INICIALIZADO - Verifique as conexoes!");    
    while (1);                                 
  }
  
  rtc.adjust(DateTime(2026, 3, 17, 20, 58, 00)); 
  
  Serial.println("RTC conectado ");
  delay(100);                                  
}

void loop () {
  DateTime agora = rtc.now();                             
  Serial.print("Data: ");
  Serial.print(agora.day(), DEC);                         
  Serial.print('/');                                      
  Serial.print(agora.month(), DEC);                       
  Serial.print('/');                                      
  Serial.print(agora.year(), DEC);                        
  Serial.print(" / Dia da semana: ");                     
  Serial.print(diasDaSemana[agora.dayOfTheWeek()]);       
  Serial.print(" / Horas: ");                             
  Serial.print(agora.hour(), DEC);                        
  Serial.print(':');                                      
  Serial.print(agora.minute(), DEC);                      
  Serial.print(':');                                      
  Serial.print(agora.second(), DEC);                      
  Serial.println();                                       
  delay(1000);                                            
}