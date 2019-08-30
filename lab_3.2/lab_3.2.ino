/*
 * MICROPROCESSORS
 */

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  float output = ((float)analogRead(A0)/1023)*5;
  
  Serial.println(((float)750/7) * (output - 1) + 50 + 5);


  
  delay(1000);
}
