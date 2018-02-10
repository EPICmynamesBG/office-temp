#include "DHT.h"

#define DHTPIN D3
#define DHTTYPE DHT11

#define MAX_INT 2147483647

DHT dht(DHTPIN, DHTTYPE);
float humidity = 0;
float celsius = 0;
float fahrenheit = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool updated = getDHT();
  if (updated) {
    delay(10000);
  } else {
    delay(1000);
  }
}

bool getDHT() {
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  float c = dht.readTemperature();

  if (isnan(h) || isnan(c) || isnan(f)) {
    Serial.print("\nFailed to read from DHT sensor");
    return false;
  } else if (h == MAX_INT || c == MAX_INT || f == MAX_INT) {
    Serial.print("\nBad read from DHT sensor");
    return false;
  } else {
    humidity = h;
    celsius = c;
    fahrenheit = f;
    Serial.print("\nFahrenheit: ");
    Serial.print(fahrenheit);
    Serial.print("\tCelsius: ");
    Serial.print(celsius);
    Serial.print("\tHumidity: ");
    Serial.print(humidity);
    return true;
  }
}

