# Office Temp

a Slack webhook/slash command + IoT device


## Server ##

Setup:

in the `server` directory, create a `config.php` file like:
```php
<?php

  define('DB_USERNAME', '');
  define('DB_PASSWORD', '');
  define('SLASH_TOKEN', '')

?>
```


## Firmware ##

Designed for NodeMCU v1

Libraries:
- Adafruit Unified Sensor - required by DHT sensor library
- DHT sensor Library (Adafruit) - for communicating with DHT11 module
- WiFiManager - used for connecting the NodeMCU to a Wifi network

Setup:

In `firmware/main/src` create a `config.h` file
```h
#pragma once

#define DHTPIN D1

#define DHTTYPE DHT11

#define READING_LED D2 //Optional

#define WIFI_LED D3 //Optional

#define POST_URL "https://example.com"

#define HTTPS_FINGERPRINT "" //Optional

#define DNS_NAME "NodeMCU-Temp"

#define AP_NAME "NodeMCU-Temp"

#define SLEEP_TIME 5 // minutes

/* #define DEBUG true */

#define CUSTOM_CSS "" // Optional

```
