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
// 9  - LED Greens
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
#include <string.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args) write(args);
#else
#define printByte(args) print(args, BYTE);
#endif

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int REFRESH_RATE = 500;
int IS_ON = 1;

byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress server(10, 30, 4, 181);

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

  pinMode(8, OUTPUT);
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
    client.publish("810teams", "pir:YES");
  } else {
    Serial.println("NO");
    lcd.print("NO");
    client.publish("810teams", "pir:NO");
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

  String buff_str = "temperature:" + String(temp);
  char buff[100];
  buff_str.toCharArray(buff, 100);
  client.publish("810teams", buff);
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

  String buff_str = "pulseWidth:" + String(pulseWidth);
  char buff[100];
  buff_str.toCharArray(buff, 100);
  client.publish("810teams", buff);
  
  long distance = pulseWidth/29/2;
  Serial.print("Distance\t"); Serial.println(distance);
  
  lcd.setCursor(8, 1);
  lcd.print("Dst"); 
  lcd.setCursor(12, 1);
  lcd.print(distance);

  buff_str = "distance:" + String(distance);
  buff_str.toCharArray(buff, 100);
  client.publish("810teams", buff);
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

  String buff_str = "temperatureI2C:" + String(temp);
  char buff[100];
  buff_str.toCharArray(buff, 100);
  client.publish("810teams", buff);
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

  if (strcmp(topic, "810teams/led/value") == 0) {
    if (IS_ON) {
      payload[length] = '\0';
      String payload_str = String((char*)payload);
      int val = payload_str.toInt();
      analogWrite(9, val);
    } else {
      analogWrite(9, 0);
    }
  } else if (strcmp(topic, "810teams/led/switch") == 0) {
     payload[length] = '\0';
     
     if (strcmp((char*)payload, "on") == 0) {
        IS_ON = 1;
     } else {
        IS_ON = 0;
     }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("810teams")) {
      Serial.println("connected");
      client.publish("810teams","Client 810teams connected.");
      client.subscribe("810teams/led/value");
      client.subscribe("810teams/led/switch");
    } else {
      Serial.print("failed, rc="); Serial.print(client.state()); Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
  Serial.println("");
}
