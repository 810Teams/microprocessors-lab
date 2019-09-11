/*
 * MICROPROCESSORS LAB
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);

  pinMode(9, OUTPUT);
  pinMode(8, INPUT);

  Serial.begin(9600);
}

void loop() {
  lcd.clear();

  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);
  
  int pulseWidth = pulseIn(8, HIGH);
  Serial.print("Pulse Width: "); Serial.println(pulseWidth);
  
  lcd.setCursor(0, 0);
  lcd.print("Pulse Width:"); 
  lcd.setCursor(12, 0);
  lcd.print(pulseWidth); 
  
  long distance = pulseWidth/29/2;
  Serial.print("Distance: "); Serial.println(distance);
  
  lcd.setCursor(0, 1);
  lcd.print("Distance:"); 
  lcd.setCursor(9, 1);
  lcd.print(distance); 
  
  delay(1000);
}
