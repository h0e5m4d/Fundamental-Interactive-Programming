const int buttonPin = 2;

const int RledPin = 3;
const int GledPin = 4;
const int BledPin = 5;

int buttonState = 0;
int ledState = 0;
int ledcolor = 0;
bool ButtonPressed = false;
String currentcolor = "led";
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {

  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  pinMode(buttonPin, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Read button
  buttonState = digitalRead(buttonPin);
  Serial.print("Current Color: ");
  Serial.println(currentcolor);

  if (buttonState == HIGH && ButtonPressed == false) {

    ledcolor = ledcolor + 1;
    ButtonPressed = true;

    if (ledcolor > 7) {
      ledcolor = 0;
    }
  }

  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;
  if (ledState == LOW)  {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
  }

  // LED colors

  if (ledcolor == 0) {

    currentcolor = "LED off";

    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }

  else if (ledcolor == 1) {

    currentcolor = "Red";

    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);

    delay(1000);

    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);

    delay(1000);
  }

  else if (ledcolor == 2) {

    currentcolor = "Blue";

    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);

    delay(1000);

    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);

    delay(1000);
  }

  else if (ledcolor == 3) {

    currentcolor = "Green";

    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);

    delay(1000);

    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);

    delay(1000);
  }

  else if (ledcolor == 4) {

    currentcolor = "Yellow";

    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);

    delay(1000);

    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);

    delay(1000);
  }

  else if (ledcolor == 5) {

    currentcolor = "Cyan";

    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);

    delay(1000);

    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);

    delay(1000);
  }

  else if (ledcolor == 6) {

    currentcolor = "Purple";

    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);

    delay(1000);

    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);

    delay(1000);
  }

  else if (ledcolor == 7) {

    currentcolor = "White";

    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);

    delay(1000);

    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);

    delay(1000);
  }
}