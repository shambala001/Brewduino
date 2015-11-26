#include <DallasTemperature.h>
#include <OneWire.h>
#include <IRremote.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

#define ONE_WIRE_BUS_PIN 10
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

boolean PrT1 = false;
boolean PrT2 = false;
boolean PrT3 = false;
boolean PrT4 = false;
boolean PrT5 = false;
int receiver = 11;
int blueled = 5;
int music = 6;
int purpleled = 5;
IRrecv irrecv(receiver); // create instance of 'irrecv'
decode_results results; // create instance of 'decode_results'

DeviceAddress Probe01 = { 0x28, 0xCD, 0x93, 0xA5, 0x04, 0x00, 0x00, 0x84 }; 
DeviceAddress Probe02 = { 0x28, 0x39, 0x6C, 0xA5, 0x04, 0x00, 0x00, 0xE3 };
DeviceAddress Probe03 = { 0x28, 0x05, 0xB5, 0x37, 0x04, 0x00, 0x00, 0x38 };
DeviceAddress Probe04 = { 0x28, 0x23, 0x05, 0x21, 0x05, 0x00, 0x00, 0xE9 };

byte tri_1[8] = {
        B00000,
        B00001,
        B00011,
        B00111,
        B01111,
        B11111,
        B00000,
        B00000
};

byte tri_2[8] = {
        B11000,
        B11100,
        B11110,
        B11111,
        B11111,
        B11111,
        B00000,
        B00000
};

byte tri_3[8] = {
        B00000,
        B00000,
        B00000,
        B00001,
        B10011,
        B11111,
        B00000,
        B00000
};

byte tri_4[8] = {
        B00110,
        B01111,
        B11111,
        B11111,
        B11111,
        B11111,
        B00000,
        B00000
};

byte tri_5[8] = {
        B00000,
        B00000,
        B10000,
        B11000,
        B11100,
        B11110,
        B00000,
        B00000
};

byte tri_6[8] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00001,
        B00011,
        B00111,
        B01111
};

byte tri_7[8] = {
        B00000,
        B00000,
        B01100,
        B11110,
        B11111,
        B11111,
        B11111,
        B11111
};

byte tri_8[8] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B10000,
        B11000,
        B11100
};

void setup()
{
  Serial.begin(9600);
  sensors.begin();
  sensors.setResolution(Probe01, 10);
  sensors.setResolution(Probe02, 10);
  sensors.setResolution(Probe03, 10);
  sensors.setResolution(Probe04, 10);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(blueled, OUTPUT);
  pinMode(music, OUTPUT);
  lcd.begin (20,4,LCD_5x8DOTS);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();
  lcd.createChar(0, tri_1);
  lcd.createChar(1, tri_2);
  lcd.createChar(2, tri_3);
  lcd.createChar(3, tri_4);
  lcd.createChar(4, tri_5);
  lcd.createChar(5, tri_6);
  lcd.createChar(6, tri_7);
  lcd.createChar(7, tri_8);
  lcd.setCursor(0,2);
  lcd.write(byte(0));
  lcd.setCursor(1,2);
  lcd.write(byte(1));
  lcd.setCursor(2,2);
  lcd.write(byte(2));
  lcd.setCursor(3,2);
  lcd.write(byte(3));
  lcd.setCursor(4,2);
  lcd.write(byte(4));
  lcd.setCursor(1,1);
  lcd.write(byte(5));
  lcd.setCursor(2,1);
  lcd.write(byte(6));
  lcd.setCursor(3,1);
  lcd.write(byte(7));
  lcd.setCursor(5,1);
  lcd.print("Welcome to");
  lcd.setCursor(6,2);
  lcd.print("Brewduino");
}


void loop() {
  if (irrecv.decode(&results)) { // have we received an IR signal?
    Serial.println(results.value, HEX);  //UN Comment to see raw values
    if (results.value == 0xD7E84B1B)
      {
        Serial.println(" OK");
        digitalWrite(blueled, HIGH);
        delay(500);
        digitalWrite(blueled, LOW);
        lcd.clear();
        lcd.setCursor(0,2);
        lcd.write(byte(0));
        lcd.setCursor(1,2);
        lcd.write(byte(1));
        lcd.setCursor(2,2);
        lcd.write(byte(2));
        lcd.setCursor(3,2);
        lcd.write(byte(3));
        lcd.setCursor(4,2);
        lcd.write(byte(4));
        lcd.setCursor(1,1);
        lcd.write(byte(5));
        lcd.setCursor(2,1);
        lcd.write(byte(6));
        lcd.setCursor(3,1);
        lcd.write(byte(7));
        lcd.setCursor(5,1);
        lcd.print("Welcome to");
        lcd.setCursor(6,2);
        lcd.print("Brewduino");
        PrT1 = false;
        PrT2 = false;
        PrT3 = false;
        PrT4 = false;
        PrT5 = false;
      }
    if (results.value == 0x3CABD517 || results.value == 0xC101E57B)
      {
        Serial.println(" 1");
        digitalWrite(blueled, HIGH);
        delay(500);
        digitalWrite(blueled, LOW);
        lcd.clear();
        lcd.print("Wort Tempature: ");
        lcd.setCursor(0,1);
        lcd.print("Water Intake: ");
        lcd.setCursor(0,2);
        lcd.print("Water Output: ");
        lcd.setCursor(0,3);
        lcd.print("Wort Output: ");
        PrT1 = true;
        PrT2 = false;
        PrT3 = false;
        PrT4 = false;
        PrT5 = false;
      }
    if (results.value == 0x97483BFB)
      {
        Serial.println(" 2");
        digitalWrite(blueled, HIGH);
        delay(500);
        digitalWrite(blueled, LOW);
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("Wort Tempature: ");
        PrT1 = false;
        PrT2 = true;
        PrT3 = false;
        PrT4 = false;
        PrT5 = false;
      }
    if (results.value == 0x98213AE4 || results.value == 0xF0C41643)
      {
        Serial.println(" 3");
        digitalWrite(blueled, HIGH);
        delay(500);
        digitalWrite(blueled, LOW);
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("Water Intake: ");
        PrT1 = false;
        PrT2 = false;
        PrT3 = true;
        PrT4 = false;
        PrT5 = false;
      }
    if (results.value == 0xE8C5640E || results.value == 0x9716BE3F)
      {
        Serial.println(" 4");
        digitalWrite(blueled, HIGH);
        delay(500);
        digitalWrite(blueled, LOW);
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("Water Output: ");
        PrT1 = false;
        PrT2 = false;
        PrT3 = false;
        PrT4 = true;
        PrT5 = false;
      }
    if (results.value == 0x4DB5DAAB || results.value == 0x3D9AE3F7)
      {
        Serial.println(" 5");
        digitalWrite(blueled, HIGH);
        delay(500);
        digitalWrite(blueled, LOW);
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("Wort Output: ");
        PrT1 = false;
        PrT2 = false;
        PrT3 = false;
        PrT4 = false;
        PrT5 = true;
      }
    irrecv.resume(); // receive the next value
  }
  if (PrT1 == true) {
    sensors.requestTemperatures(); // Send the command to get temperatures
    lcd.setCursor(15,0);
    printTemperature(Probe01);
    lcd.setCursor(15,1);
    printTemperature(Probe02);
    lcd.setCursor(15,2);
    printTemperature(Probe03);
    lcd.setCursor(15,3);
    printTemperature(Probe04);
    delay(1000);
  }
  if (PrT2 == true) {
    sensors.requestTemperatures(); // Send the command to get temperatures
    lcd.setCursor(15,1);
    printTemperature(Probe01);
    delay(1000);
  }
  if (PrT3 == true) {
    sensors.requestTemperatures(); // Send the command to get temperatures
    lcd.setCursor(14,1);
    printTemperature(Probe02);
    delay(1000);
  }
  if (PrT4 == true) {
    sensors.requestTemperatures(); // Send the command to get temperatures
    lcd.setCursor(14,1);
    printTemperature(Probe03);
    delay(1000);
  }
  if (PrT5 == true) {
    sensors.requestTemperatures(); // Send the command to get temperatures
    lcd.setCursor(14,1);
    printTemperature(Probe04);
    delay(1000);
  }
}

void printTemperature(DeviceAddress deviceAddress)
{

float tempC = sensors.getTempC(deviceAddress);

   if (tempC != -127.00) 
   {
   lcd.print(DallasTemperature::toFahrenheit(tempC));
   }
}
