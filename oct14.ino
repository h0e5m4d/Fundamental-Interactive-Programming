const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int moodd = 0;
const int neutralMood = 10;

void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  mood = neutralMood;
}

void loop() {

  float brightnessInterval = 255 / 10.0;
  if (mood >= neutralMood) {
    analogWrite(RledPin, 255);
    analogWrite(GledPin, brightnessInterval * (mood - neutralMood));
    analogWrite(BledPin, 255 - brightnessInterval * (mood - neutralMood));
  }
  else {
    analogWrite(RledPin, 255 - brightnessInterval * (neutralMood - mood));
    analogWrite(GledPin, brightnessInterval * (neutralMood - mood));
    analogWrite(BledPin, 255);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > 1000) {
    mood = mood + fadingDirection;
    if (mood >=20 || mood <= 0)
      fadingDirection = -fadingDirection;
    previousMillis = currentMillis;
  }
}