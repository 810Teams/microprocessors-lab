//
// MICROPROCESSOR LAB 1.3
//

void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  int delayDuration = 8;
  int brightnessLimit = 32;
  int r = brightnessLimit;
  int g = 0;
  int b = 0;

  while (g < brightnessLimit) {
    g++;
    lightUp(r, g, b);
    delay(delayDuration);
  }

  while (r > 0) {
    r--;
    lightUp(r, g, b);
    delay(delayDuration);
  }

  while (b < brightnessLimit) {
    b++;
    lightUp(r, g, b);
    delay(delayDuration);
  }

  while (g > 0) {
    g--;
    lightUp(r, g, b);
    delay(delayDuration);
  }

  while (r < brightnessLimit) {
    r++;
    lightUp(r, g, b);
    delay(delayDuration);
  }

  while (b > 0) {
    b--;
    lightUp(r, g, b);
    delay(delayDuration);
  }
}

void lightUp(int r, int g, int b) {
  analogWrite(11, 255-r);
  analogWrite(10, 255-g);
  analogWrite(9,  255-b);
}
