/*
* Automatic Water Level Controller Using NRF
*     
*                
*
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
//for bydirectional we have to crete 2 addresses
const byte address[6] = {"00001"};
const byte address1[6] = {"00002"};
int flag1,flag2 ;
void setup() {
  
  Serial.begin(9600);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  radio.begin();
  
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  
  //moto relay Switch
  pinMode(9 , OUTPUT); // 1st motor Pin Relay
  pinMode(10, OUTPUT); // 2nd Relay Pin
  //Led pin configuration
  pinMode(5 , OUTPUT); //led 1
  pinMode(4 , OUTPUT); //led 2
  pinMode(3 , OUTPUT); //led 3

  //For manual Mode
  pinMode(2 ,INPUT); // Low means Automatic Mode
  pinMode(6, INPUT); // Switch Manual Work Operation
 
}
void loop() {

radio.openReadingPipe(0,address1);
radio.startListening();

if(radio.available()){
  char text1[32] = "";
  radio.read(&text1, sizeof(text1));
  Serial.println(text1);

  if(text1[0] == 'D'){
    
  radio.stopListening();
  delay(3000);

  radio.openReadingPipe(0,address);

  
  radio.startListening();
  //For Automatic Mode
 
if(digitalRead(2) == LOW){
  radio.startListening();
  delay(1000);
  Serial.println("Inside Automatioc mode");
 if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    
    if(text[0] == 'F'){
      //digitalWrite(10 , LOW); // Turn off the relay
      digitalWrite(5, LOW); // Turn on all the Led Showing the status 
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
    }

     

     if(text[0] == 'E'){
      
      digitalWrite(9, LOW);// Turn off the relay
      delay(5000); //delay for starter
      digitalWrite(9,HIGH);
      while(text[0] != 'F')
      {
      radio.read(&text, sizeof(text)); 
      digitalWrite(5, LOW); // Turn on all the Led Showing the status 
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
      

      if(text[0] == 'F'){
      digitalWrite(10, LOW); // Active Low turn on
      delay(5000);
      digitalWrite(10, HIGH);
      digitalWrite(5, HIGH); // Turn on all the Led Showing the status 
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      
    }
    }

    
  }
}
}

// For Manual Mode
 if(digitalRead(2) == HIGH){
  //Serial.println("Inside Manual mode");
  Serial.println(flag1);
  Serial.println(flag2);
    if(digitalRead(6) == HIGH)
    {
      if(flag1 == 0){
      Serial.println("Inside this");
      digitalWrite(9, LOW);// Turn off the relay
      delay(5000); //delay for starter
      digitalWrite(9, HIGH);
      
      flag1 = 1;
      flag2 = 0;
     
      }
    } 
    if(digitalRead(6) == LOW){
      if(flag2 == 0)
      {
        Serial.println("Outside this");
        digitalWrite(10, LOW);// Turn off the relay
        delay(5000); //delay for starter
        digitalWrite(10,HIGH);
        delay(2000);
        flag2 = 1;
        flag1 = 0;
      }
    }

    
    if (radio.available()) {
   char text[32] = "";
    radio.read(&text, sizeof(text));
    //Serial.println(text);
    
   if(text[0] == 'F'){

      digitalWrite(5, LOW); // Turn on all the Led Showing the status 
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
    }

    if(text[0] == 'H'){
     //digitalWrite(6, HIGH);// Turn off the relay
      digitalWrite(5, LOW); // Turn on all the Led Showing the status 
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
    }

     if(text[0] == 'E'){
      //digitalWrite(6, HIGH);// Turn off the relay
     digitalWrite(5, LOW); // Turn on all the Led Showing the status 
     digitalWrite(4, LOW);
     digitalWrite(3, HIGH);
   }
 }

 }

}

if(text1[0] == 'L'){
  Serial.println("Well is getting Empty");
}
}
}
