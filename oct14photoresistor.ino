int Photoresistor = 2;
int led = 9;

void setup() {
  Serial.begin(9600);

  pinMode(Photoresistor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {

  int PhotoresistorState = digitalRead(Photoresistor);
  digitalWrite(led, PhotoresistorState);

  Serial.println(PhotoresistorState);
  delay(1);
}
