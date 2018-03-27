/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN

//for bydirectional we have to crete 2 addresses
const byte address[6] = {"00001"};
char  x[10];
void setup() {
  Serial.begin(9600);
  
  
  // for Reading the value
  
  radio.begin();
  radio.openWritingPipe(address); //00001
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
 
  Serial.println("Welcome to Water top Level Controller");

  // end of reading Values

  
  //pins for Sensors
  //s1 for level 1, S2 for level 2 and S3 for 3rd level
//  
  pinMode(6,INPUT); //S1 top sensor
  pinMode(5,INPUT); //S2 middle sensor
  pinMode(4,INPUT); //S3 low level sensor
}
void loop() {

if(digitalRead(6) == HIGH ){
  Serial.println("Water Tank full");
  //send("F");
  radio.stopListening();
  
  const char text[] = "F";
  radio.write(&text, sizeof(text));
  delay(5);
  
  }
else if ( digitalRead(5) == HIGH){
  Serial.println("Water Tank Half full");
  //send("H");
   radio.stopListening();
  
  const char text[] = "H";
  radio.write(&text, sizeof(text));
  delay(5);  
}
else if(digitalRead(4) == HIGH){
  Serial.println("Water tank Low");
  //send("E");
   radio.stopListening();
  
  const char text[] = "E";
  radio.write(&text, sizeof(text));
  delay(5);
}
}




