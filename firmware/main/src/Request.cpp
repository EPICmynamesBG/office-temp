#include "Request.h";

Request::Request() {
  // do nothing
};


String Request::buildJson(float fahrenheit, float celsius, float humidity) {
  String json = "{";
  json.concat("\"fahrenheit\":" + String(fahrenheit) + ", ");
  json.concat("\"celsius\":" + String(celsius) + ", ");
  json.concat("\"humidity\":" + String(humidity) + " ");
  json.concat("}");
  return json;
}

void Request::post(float& fahrenheit, float& celsius, float& humidity) {
  // this->net.createConnection(net.TCP, (int) HTTPS);
  if (isnan(fahrenheit) || isnan(celsius) || isnan(humidity)) {
    Serial.println("NaN found. Not sending");
    return;
  }

  String json = this->buildJson(fahrenheit, celsius, humidity);
  Serial.println(json);

  HTTPClient http;    //Declare object of class HTTPClient

  http.begin(POST_URL, HTTPS_FINGERPRINT);
  // http.addHeader("POST", "HTTP/1.1");
  if (DNS_NAME) {
    http.addHeader("Host", DNS_NAME);
  }
  http.addHeader("Accept", "application/json");
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(json);
  Serial.printf("[HTTP] POST... code: %d\n", httpCode);
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

Request Req;
