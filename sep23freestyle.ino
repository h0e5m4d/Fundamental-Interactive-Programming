int red = 3;
int green = 4;
int blue = 5;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {

  // Fade from red to purple
  for (int i = 0; i <= 255; i++) {
    analogWrite(red, 255);
    analogWrite(blue, i);
    analogWrite(green, 0);
    delay(5);
  }

  // Fade from purple to blue
  for (int i = 255; i >= 0; i--) {
    analogWrite(red, i);
    analogWrite(blue, 255);
    analogWrite(green, 0);
    delay(5);
  }

  // Fade from blue to cyan
  for (int i = 0; i <= 255; i++) {
    analogWrite(red, 0);
    analogWrite(blue, 255);
    analogWrite(green, i);
    delay(5);
  }
}