#include <LiquidCrystal_I2C.h>

#include <DHT.h>

// Undefined Or Comment it To Hide Serial Results
#define DEBUG

#define DHTPIN 9
#define DHTTYPE DHT11

const int Soil_Water_Sensor_Pin = A0;

const int Led1 = 8;
const int Led2 = 7;
const int BoxLed = 13;

const int lcd_Width = 16;
const int lcd_Height = 2;

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht (DHTPIN, DHTTYPE);

#include "classes.h"

DHTSensorControl DHTSensor;
SoilSensorControl SoilSensor;
LedsControl Leds;

void setup() {
  // put your setup code here, to run once:
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  DHTSensor.begin();
  SoilSensor.begin(Soil_Water_Sensor_Pin);

  Serial.println("All Sensor Begin");

  Leds.beginLeds(Led1, Led2 , BoxLed);

  lcd.begin();
  lcd.backlight();

  lcd.setCursor(1, 0);
  lcd.print("Auto Watering");
  lcd.setCursor(6, 1);
  lcd.print("System");

  Serial.println("Printing on Lcd");

  digitalWrite(Led1 , HIGH);
  digitalWrite(Led2 , HIGH);
  digitalWrite(BoxLed , HIGH);

  Serial.println("Leds Are Open");

  delay(1500);
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
  int SoilData = SoilSensor.getData(Soil_Water_Sensor_Pin);

  int SoilData_After_Mapping = map(SoilData, 1023, 0, 1000, 0);

  float TempData = DHTSensor.getTemp();


  if (SoilData_After_Mapping >= 400) {

    lcd.setCursor(1, 0);
    lcd.print("Water Needed");
    
    Serial.println("Water is nedeed now for The Plant");
    
    Leds.FlashLeds(Led1 , Led2 , BoxLed);
    delay(500);
    lcd.clear();

  } else {

    lcd.setCursor(1, 0);
    lcd.print("Water is Fine");
    Serial.println("All Fine Water is Good");

    delay(500);
    lcd.clear();
  }


  if (TempData > 9.0 && TempData <= 36) {
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
