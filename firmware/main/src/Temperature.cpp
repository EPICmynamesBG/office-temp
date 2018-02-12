#include "Temperature.h"

#define MAX_INT 2147483647

Temperature::Temperature() {
  this->fahrenheit = MAX_INT;
  this->celsius = MAX_INT;
  this->humidity = MAX_INT;
}

bool Temperature::isValid(float value = MAX_INT) {
  return (bool) value != MAX_INT;
}

float Temperature::getFahrenheit() {
  float fahrenheit = this->dht.readTemperature(true);
  if (this->isValid(fahrenheit)) {
    this->fahrenheit = fahrenheit;
    return this->fahrenheit;
  } else {
    return NULL;
  }
}

float Temperature::getCelsius() {
  float celsius = this->dht.readTemperature(false);
  if (this->isValid(celsius)) {
    this->celsius = celsius;
    return this->celsius;
  } else {
    return NULL;
  }
}

float Temperature::getHumidity() {
  float humidity = this->dht.readHumidity();
  if (this->isValid(humidity)) {
    this->humidity = humidity;
    return this->humidity;
  } else {
    return NULL;
  }
}

Temperature TempMaster;
