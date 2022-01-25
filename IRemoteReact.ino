
#include <IRremote.h>

const int irReceiverPin = 2;
const int ledPin = LED_BUILTIN;

IRrecv irrecv(irReceiverPin);
decode_results decodedSignal;

void setup() {
  bool lightState = LOW;         //checking LED
  unsigned long last = millis(); //store time when last signal was received

}

void loop() {
  if (irrecv.decode(&decodedSignal) == true) {
    if (millis() - last > 250) {
      if (lightState == LOW)
      lighState = HIGH;
      else
      lightState = LOW;
      lightState = lightState; 
      digitalWrite(ledPin, lightState);
    }
    last = millis();
    irrecv.resume(); //waiting for signal
  }
}
