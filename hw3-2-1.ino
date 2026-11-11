// PART 1: BUTTON CONTROLS LED
// Arduino Nano

const int buttonPin = 5;
const int ledPin = 3;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {

  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    digitalWrite(ledPin, LOW);  // LED ON

  }

  else {
    digitalWrite(ledPin, HIGH);   // LED OFF
    Serial.println("button pressed");
  }
}
