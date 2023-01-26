#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <DHT.h>   // Libraries To Include

// Undefined Or Comment it To Hide Serial Results
#define DEBUG

#define DHTPIN 9
#define DHTTYPE DHT11  

const byte Soil_Water_Sensor_Pin = A3;  
const int WaterPumpPin = 5;             

const int Led1 = 8;
const int Led2 = 7;
const int BoxLed = 13;   

const int lcd_Width = 16;
const int lcd_Height = 2;       // pins and constants we need

LiquidCrystal_I2C lcd(0x27, lcd_Width, lcd_Height);

DHT dht (DHTPIN, DHTTYPE);    // objects we need


#include "classes.h"    // Include The Extra Code For OOP (Object Orinted Programming)

DHTSensorControl DHTSensor;
SoilSensorControl SoilSensor;
LedsControl Leds;
PumpControl Pump;     // define all objects we need from The OOP

void setup() {
  // put your setup code here, to run once:
#ifdef DEBUG
  Serial.begin(9600);
#endif

  DHTSensor.begin();
  SoilSensor.begin(Soil_Water_Sensor_Pin);
  Pump.begin(WaterPumpPin);

  Serial.println("All Sensors Begin.");

  Leds.beginLeds(Led1, Led2 , BoxLed);  // Begin Every Thing

  lcd.begin();
  lcd.backlight();

  lcd.setCursor(1, 0);
  lcd.print("Auto Watering");
  lcd.setCursor(6, 1);
  lcd.print("System");   // Begin LCD And Print on it

  Serial.println("Printing on Lcd.");

  digitalWrite(Led1 , HIGH);
  digitalWrite(Led2 , HIGH);
  digitalWrite(BoxLed , HIGH);

  Serial.println("Leds Are Open.");

  delay(1500);
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
  int SoilData = map(analogRead(Soil_Water_Sensor_Pin), 1023, 0, 1000, 0);

  float TempData = DHTSensor.getTemp();  // get data we need

  Serial.print("Water Amount in Soil:  ");
  Serial.println(SoilData);

  Serial.print("Temp: ");
  Serial.println(TempData);

  if (SoilData >= 500) {  // Check if Water Needed or No

    lcd.setCursor(1, 0);
    lcd.print("Water Needed");

    Serial.println("Water is nedeed now for The Plant");

    Leds.FlashLeds(Led1 , Led2 , BoxLed);
    delay(3000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Watering....");
    Pump.WaterPlanet(WaterPumpPin);  // Water planet via Pump
    delay(700);
    Pump.StopWatering(WaterPumpPin);
    delay(1000);
    lcd.clear();

  } else {
    
    lcd.setCursor(1, 0);  // Don't water if every thing OK
    
    lcd.print("Water is Fine");
    Serial.println("All Fine Water is Good");
    Pump.StopWatering(WaterPumpPin);
    delay(500);
    lcd.clear();
  }


  if (TempData > 9.0 && TempData <= 36) {  // Check The Temprature
    lcd.setCursor(0, 1);
    lcd.print("Temp good: ");
    Serial.println("All Fine Temprature is Good");
    lcd.print(TempData);
    delay(500);
    lcd.clear();
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Temp not Fine: ");
    Serial.println("Temperature isn't Good for The Plant");
    lcd.print(TempData);
    Leds.FlashLeds(Led1 , Led2 , BoxLed);
    delay(500);
    lcd.clear();
  }


}
