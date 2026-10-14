const int RledPin = 3;
const int GledPin = 4;
const int BledPin = 5;

void setup() {
  Serial.begin(9600);

  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
}

void loop() {

  int sensorValue = analogRead(A0);

  Serial.println(sensorValue);

  if (sensorValue <= 511) {

    // Red → Green
    int red = map(sensorValue, 0, 511, 255, 0);
    int green = map(sensorValue, 0, 511, 0, 255);
    int blue = 0;

    analogWrite(RledPin, 255 - red);
    analogWrite(GledPin, 255 - green);
    analogWrite(BledPin, 255 - blue);

  }

  else {

    // Green → Blue
    int red = 0;
    int green = map(sensorValue, 512, 1023, 255, 0);
    int blue = map(sensorValue, 512, 1023, 0, 255);

    analogWrite(RledPin, 255 - red);
    analogWrite(GledPin, 255 - green);
    analogWrite(BledPin, 255 - blue);
  }

  delay(10);
}