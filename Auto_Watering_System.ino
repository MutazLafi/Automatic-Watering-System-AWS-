#include <LiquidCrystal_I2C.h>

#include <DHT.h>



#define DHTPIN 9
#define DHTTYPE DHT11

const int Soil_Water_Sensor_Pin = A0;

const int Led1 = 8;
const int Led2 = 7;

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
  Serial.begin(9600);
  DHTSensor.begin();
  SoilSensor.begin(Soil_Water_Sensor_Pin);

  Leds.beginLeds(Led1, Led2);

  lcd.begin();
  lcd.backlight();

  lcd.setCursor(1, 0);
  lcd.print("Auto Watering");
  lcd.setCursor(6, 1);
  lcd.print("System");

  digitalWrite(Led1 , HIGH);
  digitalWrite(Led2 , HIGH);

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
    Leds.FlashLeds(Led1 , Led2);
    delay(500);
    lcd.clear();

  } else {

    lcd.setCursor(1, 0);
    lcd.print("Water is Fine");
    delay(500);
    lcd.clear();
  }


  if (TempData > 9.0 && TempData <= 36) {
    lcd.setCursor(0, 1);
    lcd.print("Temp good: ");
    lcd.print(TempData);
    delay(500);
    lcd.clear();
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Temp not Fine: ");
    lcd.print(TempData);
    Leds.FlashLeds(Led1 , Led2);
    delay(500);
    lcd.clear();
  }


}
