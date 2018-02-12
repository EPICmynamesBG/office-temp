#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "src/config.h"
#include "src/Temperature.h"
#include "src/Request.h"

void setup() {
  Serial.begin(115200);
  networkInit();
}

void loop() {
  delay(5000); // TODO: Make this a 5 minute sleep
  getDHT();
}

void networkInit() {
  WiFi.hostname(DNS_NAME);
  WiFiManager wifiManager;
//  wifiManager.setCustomHeadElement("<style>body{ background-color: blue; }</style>");
  wifiManager.setConfigPortalTimeout(180);
  wifiManager.autoConnect(AP_NAME, AP_PASSWORD);
}

void getDHT() {
  float h = TempMaster.getHumidity();
  float f = TempMaster.getFahrenheit();
  float c = TempMaster.getCelsius();
  Req.post(f, c, h);
}

