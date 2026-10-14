const int buttonPin = 2;
const int RledPin = 3;
const int GledPin = 4;
const int BledPin = 5;

int buttonState = 0;
int ledcolor = 0;

bool ButtonPressed = false;
String currentcolor="led";

void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); //Baund rate setting
}

void loop() {

  buttonState = digitalRead(buttonPin);
  Serial.print("Current Color: ");
  Serial.println(currentcolor);
  if (buttonState == HIGH && !ButtonPressed) {
    ledcolor = ledcolor + 1;
    ButtonPressed = true;
    //delay(100);
  }

  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;
  }

  if (ledcolor == 0) {
    currentcolor="LED off";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }

  else if (ledcolor == 1) {
    currentcolor="Red";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }

  else if (ledcolor == 2) {
    currentcolor="Blue";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }

  else if (ledcolor == 3) {
    currentcolor="Green";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }

  else if (ledcolor == 4) {
    currentcolor="Yellow";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }

  else if (ledcolor == 5) {
    currentcolor="Cyan";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }

  else if (ledcolor == 6) {
    currentcolor="Purple";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }

  else if (ledcolor == 7) {
    currentcolor="White";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
    else if (ledcolor == 8) {
    // White
    ledcolor = 0;
  }
}