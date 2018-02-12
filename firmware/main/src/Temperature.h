#pragma once

#include "DHT.h"
#include "config.h";

class Temperature {

public:

  /**
  * Constructor
  */
  Temperature();

  float getFahrenheit();

  float getCelsius();

  float getHumidity();


private:

  DHT dht{DHTPIN, DHTTYPE};
  float fahrenheit;
  float celsius;
  float humidity;

  bool isValid(float val);
};

extern Temperature TempMaster;
