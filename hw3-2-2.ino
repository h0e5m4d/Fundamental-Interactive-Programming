// PART 2: DIFFERENT STATES
// Arduino Nano

const int buttonPin = 5;
const int ledPin = 3;

// Button variables
int lastButtonReading = HIGH;
int buttonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// LED modes
int currentMode = 0;

// LED timer
unsigned long previousMillis = 0;
int ledState = LOW;

// =================================
// SETUP
// =================================

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // Initial state: STEADY ON
  digitalWrite(ledPin, LOW);

  Serial.println("Mode: STEADY");
}

// =================================
// MAIN LOOP
// =================================

void loop() {

  checkButton();

  unsigned long currentMillis = millis();

  // MODE 0: STEADY LIGHT
  if (currentMode == 0) {
    digitalWrite(ledPin, LOW);
  }

  // MODE 1: SLOW BLINK
  else if (currentMode == 1) {
    blinkLED(currentMillis, 500);
  }

  // MODE 2: MEDIUM BLINK
  else if (currentMode == 2) {
    blinkLED(currentMillis, 250);
  }

  // MODE 3: FAST BLINK
  else if (currentMode == 3) {
    blinkLED(currentMillis, 100);
  }
}

// =================================
// BUTTON FUNCTION
// =================================

void checkButton() {

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {

    if (reading != buttonState) {

      buttonState = reading;

      // Detect button press
      if (buttonState == LOW) {

        currentMode++;

        // Fourth press returns to steady
        if (currentMode > 3) {
          currentMode = 0;
        }

        // Reset blink timing
        previousMillis = millis();
        ledState = LOW;

        digitalWrite(ledPin, LOW);

        // Print current mode
        if (currentMode == 0) {
          Serial.println("Mode: STEADY");
        }
        else if (currentMode == 1) {
          Serial.println("Mode: SLOW BLINK");
        }
        else if (currentMode == 2) {
          Serial.println("Mode: MEDIUM BLINK");
        }
        else if (currentMode == 3) {
          Serial.println("Mode: FAST BLINK");
        }
      }
    }
  }

  lastButtonReading = reading;
}

// =================================
// BLINK FUNCTION
// =================================

void blinkLED(unsigned long currentMillis, int interval) {

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    // Switch LED ON and OFF
    if (ledState == LOW) {
      ledState = HIGH;
    }
    else {
      ledState = LOW;
    }

    digitalWrite(ledPin, ledState);
  }
}