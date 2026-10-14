const int rLEDPin = 4;
const int gLEDPin = 5;
const int bLEDPin = 6;

void setup() {
  pinMode(rLEDPin, OUTPUT);
  pinMode(gLEDPin, OUTPUT);
  pinMode(bLEDPin, OUTPUT);
}

void loop() {
  // red
  digitalWrite(rLEDPin, LOW);
  digitalWrite(gLEDPin, HIGH);
  digitalWrite(bLEDPin, HIGH); 
  delay(1000); 
// turn off
  digitalWrite(rLEDPin, HIGH);
  digitalWrite(gLEDPin, HIGH);
  digitalWrite(bLEDPin, HIGH);
  delay(1000);  
// green
  digitalWrite(rLEDPin, HIGH);
  digitalWrite(gLEDPin, LOW);
  digitalWrite(bLEDPin, HIGH); 
  delay(1000);
// turn off
  digitalWrite(rLEDPin, HIGH);
  digitalWrite(gLEDPin, HIGH);
  digitalWrite(bLEDPin, HIGH);
  delay(1000);
// blue
  digitalWrite(rLEDPin, HIGH);
  digitalWrite(gLEDPin, HIGH);
  digitalWrite(bLEDPin, LOW); 
  delay(1000);
// turn off
  digitalWrite(rLEDPin, HIGH);
  digitalWrite(gLEDPin, HIGH);
  digitalWrite(bLEDPin, HIGH);
  delay(1000);
}
