
// ==========================================
// GLITCH STICK - SYSTEM ERROR 01
// Arduino Nano
// RGB + BUTTON + PHOTORESISTOR
// ==========================================

// PIN ASSIGNMENTS
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

const int buttonPin = 2;
const int photoPin = A1;

// PHOTORESISTOR
// Adjust after checking Serial Monitor!
int darkThreshold = 900;

// BUTTON
int lastButtonReading = HIGH;
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// MODES
const int NORMAL = 0;
const int PARTY = 1;
const int GLITCH = 2;
const int OFF = 3;

int currentMode = NORMAL;

// TIMERS
unsigned long previousEffectMillis = 0;
unsigned long previousPrintMillis = 0;

// ==========================================
// SETUP
// ==========================================

void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  randomSeed(analogRead(A3));

  setColor(0, 0, 0);

  Serial.println("GLITCH STICK ONLINE");
}

// ==========================================
// MAIN LOOP
// ==========================================

void loop() {

  unsigned long currentMillis = millis();

  int photoValue = analogRead(photoPin);

  // Print light sensor value
  if (currentMillis - previousPrintMillis >= 300) {
    previousPrintMillis = currentMillis;

    Serial.print("Light: ");
    Serial.print(photoValue);
    Serial.print(" | Mode: ");
    Serial.println(currentMode);
  }

  checkButton();

  // Darkness triggers CHAOS
  bool isDark = photoValue > darkThreshold;

  if (isDark) {
    chaosMode(currentMillis);
  }

  else {

    if (currentMode == NORMAL) {
      normalMode(currentMillis);
    }

    else if (currentMode == PARTY) {
      partyMode(currentMillis);
    }

    else if (currentMode == GLITCH) {
      glitchMode(currentMillis);
    }

    else if (currentMode == OFF) {
      setColor(0, 0, 0);
    }
  }
}

// ==========================================
// RGB COLOUR FUNCTION
// Active-low RGB module
// ==========================================

void setColor(int red, int green, int blue) {

  analogWrite(redPin, 255 - red);
  analogWrite(greenPin, 255 - green);
  analogWrite(bluePin, 255 - blue);
}

// ==========================================
// BUTTON: SWITCH MODES
// ==========================================

void checkButton() {

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {

    if (reading != buttonState) {

      buttonState = reading;

      if (buttonState == LOW) {

        currentMode++;

        if (currentMode > OFF) {
          currentMode = NORMAL;
        }

        previousEffectMillis = 0;

        Serial.print("NEW MODE: ");
        Serial.println(currentMode);
      }
    }
  }

  lastButtonReading = reading;
}

// ==========================================
// MODE 01: NORMAL
// Purple breathing light
// ==========================================

void normalMode(unsigned long currentMillis) {

  float wave = (sin(currentMillis / 700.0) + 1.0) / 2.0;

  int brightness = 30 + wave * 225;

  setColor(
    brightness / 2,
    0,
    brightness
  );
}

// ==========================================
// MODE 02: PARTY
// Random colourful flashes
// ==========================================

void partyMode(unsigned long currentMillis) {

  if (currentMillis - previousEffectMillis >= 250) {

    previousEffectMillis = currentMillis;

    setColor(
      random(0, 256),
      random(0, 256),
      random(0, 256)
    );
  }
}

// ==========================================
// MODE 03: GLITCH
// Random flashes + blackouts
// ==========================================

void glitchMode(unsigned long currentMillis) {

  if (currentMillis - previousEffectMillis >= random(60, 250)) {

    previousEffectMillis = currentMillis;

    if (random(0, 100) < 35) {

      // SYSTEM BLACKOUT
      setColor(0, 0, 0);
    }

    else {

      // RANDOM GLITCH COLOUR
      setColor(
        random(0, 256),
        random(0, 256),
        random(0, 256)
      );
    }
  }
}

// ==========================================
// MODE 04: OFF
// Completely turns off the RGB LED
// ==========================================

void offMode() {
  setColor(0, 0, 0);
}

// ==========================================
// AUTOMATIC CHAOS MODE
// Activated by darkness
// ==========================================

void chaosMode(unsigned long currentMillis) {

  if (currentMillis - previousEffectMillis >= random(40, 120)) {

    previousEffectMillis = currentMillis;

    if (random(0, 100) < 45) {

      setColor(0, 0, 0);
    }

    else {

      setColor(
        random(0, 256),
        random(0, 256),
        random(0, 256)
      );
    }
  }
}
