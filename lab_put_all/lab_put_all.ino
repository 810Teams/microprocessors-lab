///
/// MICROPROCESSORS
/// Put it all together
///

// PORTS
// A0 - Temperature IN
// A1 - 
// A2 - 
// A3 - 
// A4 - Temperature I2C Essential
// A5 - Temperature I2C Essential
// 13 - PIR Sensor
// 12 - LCD Display Essential
// 11 - LCD Display Essential
// 10 - 
// 9  - 
// 8  - 
// 7  - Ultrasonic OUT
// 6  - Ultrasonic IN
// 5  - LCD Display Essential
// 4  - LCD Display Essential
// 3  - LCD Display Essential
// 2  - LCD Display Essential
// 1  - 

#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <stdlib.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args) write(args);
#else
#define printByte(args) print(args, BYTE);
#endif

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int REFRESH_RATE = 1000;

byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xEE };
char server[] = "10.30.4.180";
//char server[] = "10.30.4.199";

EthernetClient ethClient;
PubSubClient client(ethClient);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  setupPIR();
  setupTemperature();
  setupUltrasonic();
  setupTemperatureI2C();
  setupEthernet();
  
  findAddress();
}

void loop() {
   Serial.println("");
   lcd.clear();

   loopEthernet();
   loopPIR();
   loopTemperature();
   loopUltrasonic();
   loopTemperatureI2C();
   
   delay(REFRESH_RATE);
}

// PIR SENSOR
void setupPIR() {
  pinMode(13, INPUT);
}

void loopPIR() {
  Serial.print("PIR Sensor\t");
  lcd.setCursor(0, 0);
  lcd.print("PIR"); 
  lcd.setCursor(4, 0);
  
  if (digitalRead(13)) {
    Serial.println("YES");
    lcd.print("YES");
    client.publish("810teams/pir", "YES");
  } else {
    Serial.println("NO");
    lcd.print("NO");
    client.publish("810teams/pir", "NO");
  }
}

// TEMPERATURE
void setupTemperature() {
  pinMode(A0, INPUT);
}

void loopTemperature() {
  float output = ((float) analogRead(A0)/1023)*5;
  float temp = ((float)750/7) * (output - 1) + 50 + 2.5; // +2.5 is calibration
  Serial.print("Temperature\t"); Serial.println(temp); 

  lcd.setCursor(8, 0);
  lcd.print("TMP"); 
  lcd.setCursor(12, 0);
  lcd.print(temp);

  char buff[10];
  dtostrf(temp, 4, 2, buff);
  client.publish("810teams/temperature", buff);
}

// ULTRASONIC
void setupUltrasonic() {
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
}

void loopUltrasonic() {
  digitalWrite(7, HIGH);
  delayMicroseconds(10);
  digitalWrite(7, LOW);
  
  int pulseWidth = pulseIn(6, HIGH);
  Serial.print("Pulse Width\t"); Serial.println(pulseWidth);
  
  lcd.setCursor(0, 1);
  lcd.print("PW"); 
  lcd.setCursor(3, 1);
  lcd.print(pulseWidth); 

  char buff[10];
  dtostrf(pulseWidth, 4, 0, buff);
  client.publish("810teams/pulseWidth", buff);
  
  long distance = pulseWidth/29/2;
  Serial.print("Distance\t"); Serial.println(distance);
  
  lcd.setCursor(8, 1);
  lcd.print("Dst"); 
  lcd.setCursor(12, 1);
  lcd.print(distance);

  dtostrf(distance, 4, 0, buff);
  client.publish("810teams/distance", buff);
}

// TEMPERATURE I2C
void setupTemperatureI2C() {
  Wire.begin();
  Wire.beginTransmission(0x48);
  Wire.write(0xAC);
  Wire.write(0x02);
  Wire.beginTransmission(0x48);
  Wire.write(0xEE);
  Wire.endTransmission();
}

void loopTemperatureI2C() {
  int8_t firstByte;
  int8_t secondByte;
  float temp = 0;

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
  Serial.print("Temperature I2C\t"); Serial.println(temp);

  char buff[10];
  dtostrf(temp, 4, 2, buff);
  client.publish("810teams/temperatureI2C", buff);
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
      delay(10);
    }
  }

  Serial.println("Done.");
  Serial.print("Found ");
  Serial.print(count, DEC);
  Serial.println(" device(s).");
}

// ETHERNET
void setupEthernet() {
  client.setServer(server, 1883);
  client.setCallback(callback);
  Ethernet.begin(mac);
  Serial.print("Local IP: "); Serial.println(Ethernet.localIP());

  delay(1500);
}

void loopEthernet() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("810teams")) {
      Serial.println("connected");
      client.publish("810teams/default","Client 810teams connected.");
//      client.subscribe("test");
    } else {
      Serial.print("failed, rc="); Serial.print(client.state()); Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
  Serial.println("");
}
