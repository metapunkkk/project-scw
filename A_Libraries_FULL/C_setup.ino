
void setup() {
 
  Serial.begin(115200);
  mySoftwareSerial.begin(9600);
  Serial.println();
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    while (true);
  }
  myDFPlayer.volume(15);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button,INPUT_PULLUP);
  attachInterrupt(0, sys_start, FALLING);
  cli();
  TCCR0A=(1<<WGM01);    //Set the CTC mode   
  OCR0A=0xF9; //Value for ORC0A for 1ms 
  TIMSK0|=(1<<OCIE0A);   //Set the interrupt request
  TCCR0B|=(1<<CS01);    //Set the prescale 1/64 clock
  TCCR0B|=(1<<CS00);
  sei();
  Serial.println("Timer0 Setup finished");
  cli();
  TCCR1A = 0;
  TCCR1B = 0; 
  TCNT1 = 0;\
  OCR1A = reload;
  TCCR1B = (1<<WGM12) | (1<<CS12); 
  //TIMSK1 = (1<<OCIE1A); 
  TIMSK1 &= ~(1 << OCIE1A);
  sei(); 
  Serial.println("TIMER1 Setup Finished.");

}
