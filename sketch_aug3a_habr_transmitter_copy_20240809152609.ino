#define potent_pin 1
#include <SPI.h>
#include <RF24.h>
RF24 radio(9, 10); // порты D9, D10: CSN CE
const uint32_t pipe = 111156789; // адрес рабочей трубы;

int data;
byte pwm;

void setup() {
  Serial.begin(9600);
  Serial.println("TransmitterTester ON");

  radio.begin();                // инициализация
  delay(2000);
  radio.setDataRate(RF24_2MBPS); // скорость обмена данными RF24_1MBPS или RF24_2MBPS
  radio.setCRCLength(RF24_CRC_8); // размер контрольной суммы 8 bit или 16 bit
  radio.setPALevel(RF24_PA_MAX); // уровень питания усилителя RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setChannel(0x6f);         // установка канала
  radio.setAutoAck(false);       // автоответ
  radio.powerUp();               // включение или пониженное потребление powerDown - powerUp
  radio.stopListening();  //радиоэфир не слушаем, только передача
  radio.openWritingPipe(pipe);   // открыть трубу на отправку
}

void loop() {
  data = analogRead(potent_pin);
  data = map(data, 0, 1023, 0, 255);
  pwm = data;
  
  radio.write(&pwm, sizeof(pwm));
  Serial.println("data= " + String(data));
}