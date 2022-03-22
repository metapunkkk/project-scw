#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define button 4
//global parametres
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
int buttonState = 0;//Состояние входящего сигнала
const int lim=40;//Нижний лимит заряда
bool activ=false;//Состояние системы сигнализации
bool flag=false;//Состояние зарядки
bool fl=false;//Состояние LED знака
const int hlim=100;//Верхний лимит зарядки
int mx_time=5000;//Значение задержки таймера
int ledPin=13;//Вывод на проектор глобо
int drivePin=12;//Вывод на знак для водителей
int soundPin=11;//Вывод на звук для пешеходов
int batPin=10;//Вывод на батарею контроллера
int GOBOPin=9;//Вывод на бетарею GOBO
int hlim_GLOBO=100;//Верхний лимит зарядки GLOBO;
 unsigned long last=millis();
 
void setup() {
  pinMode(button, INPUT);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
 
}

void sys_ON(){
  digitalWrite(ledPin, HIGH);
  digitalWrite(drivePin, HIGH);
  digitalWrite(soundPin, HIGH);
  activ=true;
}
void sys_OFF(){
  digitalWrite(ledPin, LOW);
  digitalWrite(drivePin, LOW);
  digitalWrite(soundPin, LOW);
  activ=false;
}

void loop() {
  if(activ==true && millis() - last > mx_time){
    last=millis();  
    sys_OFF();
  }
  else if( millis() - last >= mx_time){
    last=millis();  
  }
  int bat_ch=analogRead(A1);
  int bat_ch_GLOBO=analogRead(A2);
  if(bat_ch<hlim && flag==false){
    digitalWrite(batPin, HIGH);
    flag=true;
  }
  if(bat_ch==hlim && flag==true){
    digitalWrite(batPin, LOW);
    flag=false;
  }
  if(bat_ch_GLOBO<hlim_GLOBO && fl==false){
    digitalWrite(GOBOPin, HIGH);
    fl=true;
  }
  if(bat_ch_GLOBO==hlim_GLOBO && fl==true){
    digitalWrite(GOBOPin, LOW);
    fl=false;
  }
  radio.startListening();
  if (radio.available()) {
      radio.read(&buttonState, sizeof(buttonState));
      if(buttonState==1){
        if(activ==false)
          sys_ON();
        last = millis();
      }
  }
  radio.stopListening();  
  if(bat_ch<lim){
      int potValue = analogRead(A3);
      if(potValue==1){
          int angleValue=map(1, 0, 1023, 0, 180);
          if(activ==false)
            sys_ON();
          last = millis();
          radio.write(&angleValue, sizeof(angleValue));
      }
  }
  else{
      int potValue = analogRead(A3);
      int sensValue = analogRead(A4);
      if(potValue==1 || sensValue==1){
         int angleValue = map(1, 0, 1023, 0, 180);
         if(activ==false)
          sys_ON();
         last = millis();
         radio.write(&angleValue, sizeof(angleValue));
      }
  }

}
