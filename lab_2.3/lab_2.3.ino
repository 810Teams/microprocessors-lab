void serial();

void setup() {
  pinMode(9, INPUT);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(13, digitalRead(8));
  digitalWrite(12, digitalRead(7));
  digitalWrite(11, digitalRead(6));
  
  serial();
  delay(250);
}

void serial() {
  Serial.print(digitalRead(9));
  Serial.print(" ");
  Serial.print(digitalRead(8));
  Serial.print(" ");
  Serial.print(digitalRead(7));
  Serial.print(" ");
  Serial.print(digitalRead(6));
  Serial.print(" ");
  Serial.print(digitalRead(5));
  Serial.print(" ");
  Serial.print(digitalRead(4));
  Serial.print(" ");
  Serial.print(digitalRead(3));
  Serial.print(" ");
  Serial.print(digitalRead(2));
  Serial.println("");
}
