#pragma once

#include "config.h";
#include <Arduino.h>;
#include <ESP8266HTTPClient.h>

class Request {

public:

  /**
  * Constructor
  */
  Request();

  void post(float& fahrenheit, float& celsius, float& humidity);


private:
  String buildJson(float fahrenheit, float celsius, float humidity);
};

extern Request Req;
