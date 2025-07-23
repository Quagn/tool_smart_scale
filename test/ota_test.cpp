/*
Test file để demo chức năng OTA
Compile và upload code này để test OTA functionality
*/

#include <Arduino.h>
#include "service/ota/ota_handle.h"
#include "peripheral/ext/button/button.h"
#include "config/peripheral_config.h"

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("=== OTA Test Demo ===");
    Serial.println("Firmware Version: v1.0.0-test");
    
    // Check OTA entry condition
    if (ota_check_entry_condition()) {
        Serial.println("Entering OTA mode...");
        ota_init();
        ota_start();
    } else {
        Serial.println("Normal mode - OTA not triggered");
        Serial.println("To enter OTA: Hold Button 1 for 5s during boot");
    }
}

void loop() {
    if (ota_get_state() != OTA_STATE_DISABLED) {
        ota_handle();
    } else {
        Serial.println("Normal operation mode");
        delay(5000);
    }
} 