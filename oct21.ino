const int buttonPin = 2;
const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int buttonState = 0;
bool buttonPressed = false;

unsigned long pressingTime = 0;
const unsigned long longPressInterval = 2000;

int lightNum = 4;
int RLightColor = 0;
int GLightColor = 0;
int BLightColor = 0;

// Current LED output color
int RCurrentColor = 0;
int GCurrentColor = 0;
int BCurrentColor = 0;

// Modes: 0 = steady, 1 = blink, 2 = breathing, 3 = fading
int currentMode = 0;

// Blink settings
unsigned long blinkTimer = 0;
const unsigned long blinkInterval = 500;
bool blinkOn = true;

// Breathing settings
unsigned long breathingTimer = 0;
const unsigned long breathingInterval = 10;
int brightness = 255;
int breathingDirection = -1;

// Fading settings
unsigned long fadingTimer = 0;
const unsigned long fadingInterval = 20;
const int fadeAmount = 2;
int fadingBrightness = 255;
int fadingDirection = -1;


void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  changeLEDColor();
}


void loop() {
  checkButton();
  updateLEDColor();

  setRGBLEDColor(
    RCurrentColor,
    GCurrentColor,
    BCurrentColor
  );
}


void checkButton() {
  buttonState = digitalRead(buttonPin);

  // Detect button press
  if (buttonState == HIGH && !buttonPressed) {
    pressingTime = millis();
    buttonPressed = true;
  }

  // Detect button release
  if (buttonState == LOW && buttonPressed) {
    unsigned long currentTime = millis();

    if (currentTime - pressingTime < longPressInterval) {
      // Short press: change color
      changeLEDColor();
    } else {
      // Long press: change mode
      changeMode();
    }

    buttonPressed = false;
  }
}


void changeMode() {
  currentMode++;

  if (currentMode >= 4) {
    currentMode = 0;
  }

  // Reset animation timers and values
  blinkTimer = millis();
  blinkOn = true;

  breathingTimer = millis();
  brightness = 255;
  breathingDirection = -1;

  fadingTimer = millis();
  fadingBrightness = 255;
  fadingDirection = -1;
}


void updateLEDColor() {
  // MODE 0: Steady light
  if (currentMode == 0) {
    RCurrentColor = RLightColor;
    GCurrentColor = GLightColor;
    BCurrentColor = BLightColor;
  }

  // MODE 1: Blink light
  else if (currentMode == 1) {
    unsigned long currentTime = millis();

    if (currentTime - blinkTimer >= blinkInterval) {
      blinkOn = !blinkOn;
      blinkTimer = currentTime;
    }

    if (blinkOn) {
      RCurrentColor = RLightColor;
      GCurrentColor = GLightColor;
      BCurrentColor = BLightColor;
    } else {
      RCurrentColor = 0;
      GCurrentColor = 0;
      BCurrentColor = 0;
    }
  }

  // MODE 2: Breathing light
  else if (currentMode == 2) {
    unsigned long currentTime = millis();

    if (currentTime - breathingTimer >= breathingInterval) {
      breathingTimer = currentTime;

      brightness += breathingDirection;

      if (brightness <= 0) {
        brightness = 0;
        breathingDirection = 1;
      }

      if (brightness >= 255) {
        brightness = 255;
        breathingDirection = -1;
      }
    }

    RCurrentColor = (RLightColor * brightness) / 255;
    GCurrentColor = (GLightColor * brightness) / 255;
    BCurrentColor = (BLightColor * brightness) / 255;
  }

  // MODE 3: Fading light
  else if (currentMode == 3) {
    unsigned long currentTime = millis();

    if (currentTime - fadingTimer >= fadingInterval) {
      fadingTimer = currentTime;

      fadingBrightness += fadingDirection * fadeAmount;

      if (fadingBrightness <= 0) {
        fadingBrightness = 0;
        fadingDirection = 1;
      }

      if (fadingBrightness >= 255) {
        fadingBrightness = 255;
        fadingDirection = -1;
      }
    }

    RCurrentColor = (RLightColor * fadingBrightness) / 255;
    GCurrentColor = (GLightColor * fadingBrightness) / 255;
    BCurrentColor = (BLightColor * fadingBrightness) / 255;
  }
}


void changeLEDColor() {
  lightNum++;

  if (lightNum > 4) {
    lightNum = 0;
  }

  switch (lightNum) {
    case 0: // White
      RLightColor = 255;
      GLightColor = 255;
      BLightColor = 255;
      break;

    case 1: // Red
      RLightColor = 255;
      GLightColor = 0;
      BLightColor = 0;
      break;

    case 2: // Green
      RLightColor = 0;
      GLightColor = 255;
      BLightColor = 0;
      break;

    case 3: // Blue
      RLightColor = 0;
      GLightColor = 0;
      BLightColor = 255;
      break;

    case 4: // Yellow
      RLightColor = 255;
      GLightColor = 255;
      BLightColor = 0;
      break;
  }

  // Update output immediately in steady mode
  RCurrentColor = RLightColor;
  GCurrentColor = GLightColor;
  BCurrentColor = BLightColor;

  // Restart animation when changing color
  brightness = 255;
  breathingDirection = -1;

  fadingBrightness = 255;
  fadingDirection = -1;
}


void setRGBLEDColor(int r, int g, int b) {
  // Common-anode LED: invert brightness values
  analogWrite(RledPin, 255 - r);
  analogWrite(GledPin, 255 - g);
  analogWrite(BledPin, 255 - b);
}