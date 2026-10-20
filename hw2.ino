
const int buttonPin = 2;

const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

const int photoresistorPin = A0;

// Mood settings
int mood = 10;
const int neutralMood = 10;
const int maxMood = 20;
const int minMood = 0;

// Photoresistor thresholds
// These are starting values; calibrate them for your sensor.
const int DARK_THRESHOLD = 400;
const int VERY_DARK_THRESHOLD = 200;

// Button settings
int buttonState = LOW;
bool ButtonPressed = false;

// Timers
unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;
unsigned long darkTimer = 0;
unsigned long sensorPrintTimer = 0;

// Time intervals
const unsigned long unTouchInterval = 5000;
const unsigned long darkDelay = 3000;
const unsigned long normalReducedInterval = 1000;
const unsigned long darkReducedInterval = 500;
const unsigned long veryDarkReducedInterval = 1000;

// Assumes the yellow common wire connects to 5V
const bool commonAnode = true;


void setup() {
  pinMode(buttonPin, INPUT);

  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  Serial.begin(9600);

  touchedTimer = millis();
  reducedTimer = millis();
  darkTimer = millis();

  showLEDState(mood);

  Serial.println("My little pet is awake!");
  Serial.println("Pet me to make me happier!");
}


void loop() {
  unsigned long currentMillis = millis();

  // Read button and light sensor
  buttonState = digitalRead(buttonPin);
  int lightValue = analogRead(photoresistorPin);

  // Is the environment dark?
  bool isDark = lightValue < DARK_THRESHOLD;
  bool isVeryDark = lightValue < VERY_DARK_THRESHOLD;

  // Track how long the environment has been dark
  if (isDark) {
    // Start the timer when darkness begins
    if (darkTimer == 0) {
      darkTimer = currentMillis;
    }
  } else {
    // Reset the timer when the environment becomes bright
    darkTimer = 0;
  }

  bool darkForLongEnough = false;

  if (isDark && darkTimer != 0 &&
      currentMillis - darkTimer >= darkDelay) {
    darkForLongEnough = true;
  }

  // Pet the toy: increase mood by one
  if (buttonState == HIGH && !ButtonPressed) {
    ButtonPressed = true;

    mood++;

    if (mood > maxMood) {
      mood = maxMood;
    }

    touchedTimer = currentMillis;
    reducedTimer = currentMillis;

    Serial.print("You petted me! Mood: ");
    Serial.println(mood);
  }

  // Allow the next press after releasing the button
  if (buttonState == LOW) {
    ButtonPressed = false;
  }

  // Decide how quickly the toy loses mood
  unsigned long decayInterval = normalReducedInterval;
  int moodLoss = 1;

  if (darkForLongEnough) {
    if (isVeryDark) {
      // Very dark: lose 2 mood points per second
      decayInterval = veryDarkReducedInterval;
      moodLoss = 2;
    } else {
      // Dark for more than 3 seconds: lose mood faster
      decayInterval = darkReducedInterval;
      moodLoss = 1;
    }
  }

  // In bright conditions, normal sadness starts after 5 seconds
  bool shouldLoseMood = false;

  if (darkForLongEnough) {
    shouldLoseMood = true;
  } else if (currentMillis - touchedTimer >= unTouchInterval) {
    shouldLoseMood = true;
  }

  // Reduce mood at the appropriate interval
  if (shouldLoseMood &&
      currentMillis - reducedTimer >= decayInterval) {

    mood = mood - moodLoss;

    if (mood < minMood) {
      mood = minMood;
    }

    reducedTimer = currentMillis;

    Serial.print("Mood: ");
    Serial.println(mood);
  }

  // Print light readings twice per second for calibration
  if (currentMillis - sensorPrintTimer >= 500) {
    sensorPrintTimer = currentMillis;

    Serial.print("Light value: ");
    Serial.print(lightValue);
    Serial.print(" | ");

    if (isVeryDark) {
      Serial.println("Very dark");
    } else if (isDark) {
      Serial.println("Dark");
    } else {
      Serial.println("Bright");
    }
  }

  // Update the RGB LED
  showLEDState(mood);
}


// Set RGB brightness
void setRGB(int red, int green, int blue) {
  if (commonAnode) {
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  }

  analogWrite(RledPin, red);
  analogWrite(GledPin, green);
  analogWrite(BledPin, blue);
}


// Display mood as a color transition
void showLEDState(int currentMood) {
  int red = 0;
  int green = 0;
  int blue = 0;

  if (currentMood < neutralMood) {
    // Sad: red -> blue
    red = map(currentMood, minMood, neutralMood, 255, 0);
    blue = map(currentMood, minMood, neutralMood, 0, 255);
  } else {
    // Happy: blue -> green
    green = map(currentMood, neutralMood, maxMood, 0, 255);
    blue = map(currentMood, neutralMood, maxMood, 255, 0);
  }

  setRGB(red, green, blue);
}
