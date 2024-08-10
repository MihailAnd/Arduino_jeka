
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10); // порты D9, D10: CSN CE

const uint32_t pipe = 111156789; // адрес рабочей трубы;
int potent_pin; //тут будем ъранить данные которые пришли с потенциометра

void setup() {
  Serial.begin(9600);
  Serial.println("ReceiverTester ON");

  radio.begin();  // инициализация
  delay(2000);
  radio.setDataRate(RF24_2MBPS); // скорость обмена данными RF24_1MBPS или RF24_2MBPS
  radio.setCRCLength(RF24_CRC_8); // размер контрольной суммы 8 bit или 16 bit
  //radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x6f);         // установка канала
  radio.setAutoAck(false);       // автоответ
  radio.enableDynamicPayloads();
  //radio.powerUp();
  radio.openReadingPipe(1, pipe); // открыть трубу на приём
  radio.startListening();        // приём
}

void loop() {
 
  
  radio.read(  &potent_pin, sizeof(potent_pin) );
  printf("сейчас значение потенциометра = " + potent_pin );
 
 
 
}
  
