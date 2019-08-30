/*
 * MICROPROCESSORS
 */

void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(11, analogRead(A0)/4);
  analogWrite(10, analogRead(A1)/4);
  analogWrite(9, analogRead(A2)/4);
  delay(250);
}
