void setup() {
  pinMode(11, INPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(11) == LOW){
    digitalWrite(10, HIGH);
    //delay(5000);
  } else {
    digitalWrite(10, LOW);
    //delay(5000);
  }
}
