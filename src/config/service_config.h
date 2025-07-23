#ifndef SERVICE_CONFIG_H
#define SERVICE_CONFIG_H

// STA Wifi
#define WIFI_STA_SSID "QuangPhone"
#define WIFI_STA_PASSWORD "12341234"

// WEB Server Configuration
#define WEB_SERVER_PORT 80

// OTA WiFi Configuration
#define OTA_AP_SSID "SmartScale_OTA"
#define OTA_AP_PASSWORD "ota123456"
#define OTA_WEB_TITLE "Smart Weight Scale - OTA Update"
#define OTA_SERVER_PORT 80
#define OTA_WIFI_CONNECT_TIMEOUT    20000       // ms - 20 seconds timeout for STA mode
#define OTA_TIMEOUT_MS              300000      // ms - 5 minutes timeout

#endif