#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
char command;
int pausa = 0;
  RF24 radio(7, 8); // CE, CSN
  const byte addresses[][6] = {"00001", "00002"};
  int ledPin = 12;
  int button = 13;
  unsigned long mx_time=5000;
  unsigned long last=millis();
  bool activ=false;
  int drivePin=11;
  bool buttonState=0;
void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(drivePin, OUTPUT);

  pinMode(button,INPUT);
  
  if (!myDFPlayer.begin(mySoftwareSerial)){
    Serial.println(F("Not initialized:"));
    Serial.println(F("1. Check the DFPlayer Mini connections"));
    Serial.println(F("2. Insert an SD card"));
    while (true);
  }
  Serial.println();
  Serial.println(F("DFPlayer Mini module initialized!"));
  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(5);
  myDFPlayer.EQ(0);
  cli();
  TCCR1A = 0;   
  TCCR1B = 0;      
  TCCR1B |= B00000100;       
  TIMSK1 |= B00000010;
  OCR1A = 31250;           
  sei();
}
bool zet=false;
ISR(TIMER1_COMPA_vect){
  TCNT1  = 0;                
  if(activ==true && zet==false ) {
    digitalWrite(ledPin ,HIGH); 
    zet=true;
  }
  else if(activ==true && zet==true){
     digitalWrite(ledPin ,LOW); 
     zet=false;
  }
}
void loop() {
Serial.println(digitalRead(button));
if(activ==true && millis() - last >= mx_time){
    last=millis(); 
    sys_OFF();
  }
  else if( millis() - last >= mx_time){
    last=millis();  
  }
  
 // radio.stopListening();  
 // if(bat_ch<lim){
 //     int potValue = digitalRead(button);
//      if(activ==false)
//        sys_ON();
//      last = millis();
//      radio.write(&potValue, sizeof(potValue));
//  }
//  else{
      int potValue = digitalRead(button);
       Serial.println(potValue); 
     // int sensValue = digitalRead(sens);
      if(potValue==1){
         int angleValue = 1;
         if(activ==false){
            sys_ON();
            last = millis();
         }
         
        // radio.write(&angleValue, sizeof(angleValue));
      }
//  }
 /* radio.startListening();
  while (radio.available())  {
      radio.read(&buttonState, sizeof(buttonState));
      if(buttonState==1){
        if(activ==false)
          sys_ON();
        last = millis();
      }
  }*/
 }
 void sys_ON(){
  activ=true;
  digitalWrite(drivePin,HIGH);
  myDFPlayer.start();
  digitalWrite(ledPin,HIGH);
 }
 void sys_OFF(){
  activ=false;
  digitalWrite(ledPin,LOW);
  digitalWrite(drivePin,LOW);
  myDFPlayer.stop();
 }
