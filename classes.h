class DHTSensorControl {
  public:

    void begin() {

      dht.begin();

    }

    float getTemp() {
      float Temp = dht.readTemperature();

      if (isnan(Temp)) {
        Serial.print("Error in temp");
        return 0.0;

      } else {
        return Temp;

      }

    }

    float getHumidity() {
      float Hum = dht.readHumidity();

      if (isnan(Hum)) {
        Serial.println("Error in Humidity");
        return 0.0;

      } else {

        return Hum;
      }
    }

};



class SoilSensorControl {
  public:
    void begin(int pin) {
      pinMode(pin, INPUT);

    }

    int getData(int pin) {
      int Data = analogRead(pin);
      return Data;

    }
};

class LedsControl {
  public:
    void beginLeds(int Led1Pin , int Led2Pin , int Led3Pin) {
      pinMode(Led1Pin, OUTPUT);
      pinMode(Led2Pin, OUTPUT);
      pinMode(Led3Pin, OUTPUT);
      
    }

    void FlashLeds(int Led1Pin , int Led2Pin , int Led3Pin = 2) {
      digitalWrite(Led1Pin , LOW);
      digitalWrite(Led2Pin , LOW);
      digitalWrite(Led3Pin , LOW);
      delay(500);
      digitalWrite(Led1Pin , HIGH);
      digitalWrite(Led2Pin , HIGH);
      digitalWrite(Led3Pin , HIGH);
      delay(500);
      digitalWrite(Led1Pin , LOW);
      digitalWrite(Led2Pin , LOW);
      digitalWrite(Led3Pin , LOW);
      delay(500);
      digitalWrite(Led1Pin , HIGH);
      digitalWrite(Led2Pin , HIGH);
      digitalWrite(Led3Pin , HIGH);


    }
};
