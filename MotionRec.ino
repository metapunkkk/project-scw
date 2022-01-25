
//if we have PIR on 2 contact, but we need to think about motion sensor and mb use some other type, fe microwave sensor. anyway, code will be the same

const int ledPin = LED_BUILTIN;  //for LED
const int inputPin = 2;          //for input

void setup() {
  pinMode (ledPin, OUTPUT);
  pinMode (inputPin, INPUT);

}

void loop() {
  int val = digitalRead(inputPin); //see for input value
  if (val = HIGH) {                //check for HIGH
    digitalWrite(ledPin, HIGH);    //turn LED on if motion
    delay (500);
    digitalWrite(ledPin, LOW);     //turn LED off (possibly we won't need this part)
  }

}
