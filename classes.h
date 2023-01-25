class DHTSensorControl {
  public:

    void begin() {

      dht.begin();

    }

    float getTemp() {
      float Temp = dht.readTemperature();

      if (isnan(Temp)) {
        Serial.println("Error in temp");
        return 0.0;

      } else {
        return Temp;

      }

    }

    float getHumidity() {
      float Humidity = dht.readHumidity();

      if (isnan(Humidity)) {
        Serial.println("Error in Humidity");
        return 0.0;

      } else {

        return Humidity;
      }
    }

};



class SoilSensorControl {
  public:
    void begin(int pin) {
      pinMode(A0 , INPUT);

    }

     
};

class LedsControl {
  public:
    void beginLeds(int Led1Pin , int Led2Pin = 2 , int Led3Pin = 2) {
      pinMode(Led1Pin, OUTPUT);
      pinMode(Led2Pin, OUTPUT);
      pinMode(Led3Pin, OUTPUT);

    }

    void FlashLeds(int Led1Pin , int Led2Pin = 2 , int Led3Pin = 2) {
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


class PumpControl {
  public:

    void begin(int PumpPin) {
      pinMode(PumpPin, OUTPUT);
      StopWatering(PumpPin);
    }

    void WaterPlanet(int PumpPin) {
      digitalWrite(PumpPin, LOW);

    }

    void StopWatering(int PumpPin) {
      digitalWrite(PumpPin, HIGH);
    }
};
