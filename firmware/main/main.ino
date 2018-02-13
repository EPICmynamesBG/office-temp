#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "src/config.h"
#include "src/Temperature.h"
#include "src/Request.h"

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println();
  networkInit();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    getDHT();
    Serial.println("Sleeping...");
    ESP.deepSleep(SLEEP_TIME * 60 * 1e6, WAKE_RF_DEFAULT);
  } else {
    Serial.println("WiFi not connected");
    ESP.deepSleep(60 * 1e6, WAKE_RF_DEFAULT); // Sleep 1 minute, then wake to try again
  }
  delay(2000);
}

void networkInit() {
  Serial.println("Network Initializing...");
  WiFi.hostname(DNS_NAME);
  WiFiManager wifiManager;
  #ifdef CUSTOM_CSS
  wifiManager.setCustomHeadElement(CUSTOM_CSS);
  #endif
  wifiManager.setConfigPortalTimeout(180);
  wifiManager.setMinimumSignalQuality(40); // Minimum signal strength 40%
  wifiManager.autoConnect(AP_NAME);
}

void getDHT() {
  bool sent = false;
  while (!sent) {
    float h = TempMaster.getHumidity();
    float f = TempMaster.getFahrenheit();
    float c = TempMaster.getCelsius();
    sent = Req.post(f, c, h);
    delay(1000);
  }
}
