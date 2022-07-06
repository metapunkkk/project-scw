
int button = 2;
int led1 = 3;
int led2 = 4;
SoftwareSerial mySoftwareSerial(10, 11 );
DFRobotDFPlayerMini myDFPlayer;
RF24 radio(7, 8); // CE, CSN

const byte addresses[][6] = {"00001", "00002"};

unsigned long mx_time = 5000;

unsigned int reload = 0x2904; 

int sys_active = 0;
int timer=0;


ISR(TIMER0_COMPA_vect){ 
  if(sys_active)
    timer++;
}

ISR(TIMER1_COMPA_vect)
{
  static boolean output = HIGH;
  digitalWrite(led1, output);
  output = !output;
}
