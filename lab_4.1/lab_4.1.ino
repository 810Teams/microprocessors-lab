/*
 * MICROPROCESSORS LAB
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte CUSTOM_CHAR[6][8] = {
  {B00000,B00000,B11111,B00010,B00000,B10000,B10000,B01111}, // こ
  {B00000,B00010,B00100,B00100,B01000,B01110,B10010,B10011}, // ん
  {B00000,B00000,B10000,B10111,B10000,B10100,B10011,B01000}, // に
  {B00000,B01000,B11111,B01000,B01110,B00001,B10001,B01110}, // ち
  {B00000,B00000,B10010,B10111,B10010,B10010,B10110,B10101}, // は
  {B00000,B00000,B00000,B00000,B00000,B00100,B01010,B00100} //。
};

void setup() {
  for (int i = 0; i < 6; i++) {
    lcd.createChar(i, CUSTOM_CHAR[i]);
  }
  lcd.begin(16, 2);

  pinMode(A2, INPUT);

  Serial.begin(9600);
}

void loop() {
  lcd.clear();
  for (int i = 0; i < 6; i++) {
    lcd.setCursor(i, 0);
    lcd.write(i);
  }

  lcd.setCursor(0, 1);
  lcd.print(analogRead(A2)); 
  Serial.println(analogRead(A2));

  delay(500);
}
