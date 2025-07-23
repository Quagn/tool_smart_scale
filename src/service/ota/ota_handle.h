#ifndef OTA_HANDLE_H
#define OTA_HANDLE_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <functional>
#include "FS.h"
#include "LittleFS.h"
#include "Updater.h"
#include "StreamString.h"
#include "config/peripheral_config.h"
#include "config/service_config.h"
#include "service/wifi_handle.h"

// Function declarations
void ota_init(void);
void ota_start(void);
void ota_loop(void);
void ota_end(void);

#endif // OTA_HANDLE_H