const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;      // the PWM pin the LED is attached to
int brightness = 0;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by
int ledcolor = 0;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  if(ledcolor == 0) {
    analogWrite(RledPin, brightness);
    analogWrite(GledPin, 255);
    analogWrite(BledPin, 255);
  }
  if(ledcolor == 1) {
    analogWrite(RledPin, 255);
    analogWrite(GledPin, brightness);
    analogWrite(BledPin, 255);
  }
  if(ledcolor == 2) {
    analogWrite(RledPin, 255);
    analogWrite(GledPin, 255);
    analogWrite(BledPin, brightness);
  }

  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    if(brightness >= 255) {
      ledcolor = ledcolor + 1;
      if(ledcolor > 2)
        ledcolor = 0;
    }
  }

  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
