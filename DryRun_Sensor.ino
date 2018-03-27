/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/ 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00002";
void setup() {
  radio.begin();
  Serial.begin(9600);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  //radio.stopListening();
  
  pinMode(6,INPUT); //Dry run Sensor 
  
}
void loop() {
//Serial.println("Hellos");
  if(digitalRead(6) == HIGH){
    Serial.println("DRY Sensor is high");
    radio.stopListening();

    const char text[] = "D";
    radio.write(&text, sizeof(text));
    delay(5);
}

  else if(digitalRead(6) == LOW){
    Serial.println("DRY Sensor is LOW");
    radio.stopListening();

    const char text[] = "L";
    radio.write(&text, sizeof(text));
    delay(5);
}
}
