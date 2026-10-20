// Interactive Toy: Mood RGB LED + Button

// Button pin
const int buttonPin = 2;

// RGB LED pins
const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

// Mood settings
int mood = 10;
const int neutralMood = 10;
const int maxMood = 20;
const int minMood = 0;

// Button settings
int buttonState = LOW;
bool ButtonPressed = false;

// Timers
unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;

// Time intervals
const unsigned long unTouchInterval = 5000;  // 5 seconds
const unsigned long reducedInterval = 1000;  // 1 second

// Your yellow common wire is connected to 5V.
// This assumes your RGB LED is common-anode.
const bool commonAnode = true;


void setup() {
  // Set button pin
  pinMode(buttonPin, INPUT);

  // Set RGB LED pins
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  // Start Serial Monitor
  Serial.begin(9600);

  // Initialize timers
  touchedTimer = millis();
  reducedTimer = millis();

  // Display starting mood
  showLEDState(mood);

  Serial.println("My little pet is awake!");
  Serial.println("Press the button to make me happier!");
}


void loop() {
  unsigned long currentMillis = millis();

  // Read the button
  buttonState = digitalRead(buttonPin);

  // Make the toy happier when the button is pressed
  if (buttonState == HIGH && !ButtonPressed) {
    ButtonPressed = true;

    mood++;

    // Keep mood at or below the maximum
    if (mood > maxMood) {
      mood = maxMood;
    }

    // Reset timers after being petted
    touchedTimer = currentMillis;
    reducedTimer = currentMillis;

    Serial.print("You petted me! Mood: ");
    Serial.println(mood);
  }

  // Allow another press after the button is released
  if (buttonState == LOW) {
    ButtonPressed = false;
  }

  // Check whether the toy has been left alone for 5 seconds
  if (currentMillis - touchedTimer >= unTouchInterval) {

    // Reduce mood once every second
    if (currentMillis - reducedTimer >= reducedInterval) {

      if (mood > minMood) {
        mood--;
      }

      reducedTimer = currentMillis;

      Serial.print("I'm getting sad... Mood: ");
      Serial.println(mood);
    }
  }

  // Update the RGB LED to match the current mood
  showLEDState(mood);
}


// Set RGB brightness
void setRGB(int red, int green, int blue) {

  // Invert brightness for a common-anode RGB LED
  if (commonAnode) {
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  }

  analogWrite(RledPin, red);
  analogWrite(GledPin, green);
  analogWrite(BledPin, blue);
}


// Display the toy's mood using color
void showLEDState(int currentMood) {

  int red = 0;
  int green = 0;
  int blue = 0;

  if (currentMood < neutralMood) {

    // Sad mood: transition from red to blue
    red = map(currentMood, minMood, neutralMood, 255, 0);
    blue = map(currentMood, minMood, neutralMood, 0, 255);

  } else {

    // Happy mood: transition from blue to green
    green = map(currentMood, neutralMood, maxMood, 0, 255);
    blue = map(currentMood, neutralMood, maxMood, 255, 0);

  }

  setRGB(red, green, blue);
}