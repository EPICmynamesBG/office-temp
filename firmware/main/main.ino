#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "src/config.h"
#include "src/Temperature.h"
#include "src/Request.h"

void setup() {
  #ifdef DEBUG
  Serial.begin(115200);
  delay(100);
  Serial.println();
  #endif
  #ifdef READING_LED
  pinMode(READING_LED, OUTPUT);
  #endif
  #ifdef WIFI_LED
  pinMode(WIFI_LED, OUTPUT);
  #endif
  networkInit();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    #ifdef WIFI_LED
    digitalWrite(WIFI_LED, LOW);
    #endif
    getDHT();
    Serial.println("Sleeping...");
    ESP.deepSleep(SLEEP_TIME * 60 * 1e6, WAKE_RF_DEFAULT);
  } else {
    #ifdef WIFI_LED
    digitalWrite(WIFI_LED, HIGH);
    #endif
    Serial.println("WiFi not connected");
    ESP.deepSleep(60 * 1e6, WAKE_RF_DEFAULT); // Sleep 1 minute, then wake to try again
  }
  delay(2000);
}

void networkInit() {
  #ifdef WIFI_LED
  digitalWrite(WIFI_LED, HIGH);
  #endif
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
    delay(1000);
    #ifdef READING_LED
    digitalWrite(READING_LED, HIGH);
    #endif
    float h = TempMaster.getHumidity();
    float f = TempMaster.getFahrenheit();
    float c = TempMaster.getCelsius();
    sent = Req.post(f, c, h);
    delay(1000);
    #ifdef READING_LED
    digitalWrite(READING_LED, LOW);
    #endif
  }
  
}
