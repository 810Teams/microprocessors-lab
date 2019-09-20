/*
 * MICROPROCESSORS LAB
 */

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args) write(args);
#else
#define printByte(args) print(args, BYTE);
#endif

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void findAddress();

void setup() {
  // I2C Setup
  Wire.begin();
  Wire.beginTransmission(0x48);
  Wire.write(0xAC);
  Wire.write(0x02);
  Wire.beginTransmission(0x48);
  Wire.write(0xEE);
  Wire.endTransmission();

  // LCD Setup
  Wire.beginTransmission(0x3F);
  lcd.begin();
  lcd.clear();
  for (int i = 0; i < 5; i++) {
    lcd.backlight();
    delay(200);
    lcd.noBacklight();
    delay(200);
  }
  lcd.backlight();

  // Serial Monitor Setup
  Serial.begin(9600);
  findAddress();
}

 void loop() {
  int8_t firstByte;
  int8_t secondByte;
  float temp = 0;
  
  delay(500);
  Wire.beginTransmission(0x48);
  Wire.write(0xAA);
  Wire.endTransmission();
  Wire.requestFrom(0x48, 2);
  firstByte = Wire.read();
  secondByte = Wire.read();
  temp = firstByte;
  if (secondByte) {
    temp += 0.5 ;
  }
  Serial.println(temp);

  Wire.beginTransmission(0x3F);
  lcd.clear();
  lcd.print("Temperature(?)");
  lcd.setCursor(0, 1);
  lcd.print(temp);
}

void findAddress () {
  while (!Serial) {
  }
  
  Serial.println();
  Serial.println("I2C scanner. Scanning ...");
  byte count = 0;
  
  Wire.begin();
  for (byte i = 8; i < 120; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found address: ");
      Serial.print(i, DEC);
      Serial.print(" (0x");
      Serial.print(i, HEX);
      Serial.println(")");
      count++;
      delay(10); // maybe unneeded?
    }
  }

  Serial.println("Done.");
  Serial.print("Found ");
  Serial.print(count, DEC);
  Serial.println(" device(s).");
}
