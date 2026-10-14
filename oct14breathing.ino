const int PledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int maxBrightness = 0;
int currentBrightness = 0;
int fadingDirection = 1;
unsigned long previousMillis = 0;
int interval = 1000;

void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  maxBrightness = map(sensorValue, 0, 1023, 0, 255);

  unsigned long currentMillis = millis();
  int fadingAmount = fadingDirection * map(currentMillis - previousMillis, 0, interval, 0, maxBrightness);
  currentBrightness = currentBrightness + fadingAmount;
  if(currentBrightness >= 255){
    currentBrightness = 255;
    fadingDirection = -fadingDirection;
  }
  if(currentBrightness <= 0){
    cureentBrightness = 0;
    fadingDirection = -fadingDirection;
  }
  analogWrite(RledPin, currentBrightness);
  analogWrite(GledPin, currentBrightness);
  analogWrite(BledPin, currentBrightness);
  previosMillis = currentMillis;
  delay(1); 
}
