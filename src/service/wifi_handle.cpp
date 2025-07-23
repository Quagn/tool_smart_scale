#include "wifi_handle.h"

void Wifi_Init(void) {
    // First try to connect to WiFi in STA mode
    Serial.println("Connecting to WiFi in STA mode...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_STA_SSID, WIFI_STA_PASSWORD);
    
    unsigned long wifi_connect_start = millis();
    bool sta_connected = false;
    
    // Try to connect for OTA_WIFI_CONNECT_TIMEOUT ms
    while (millis() - wifi_connect_start < OTA_WIFI_CONNECT_TIMEOUT) {
        if (WiFi.status() == WL_CONNECTED) {
            sta_connected = true;
            break;
        }
        delay(500);
        Serial.print(".");
    }
    
    if (sta_connected) {
        // Connected to WiFi in STA mode
        Serial.println("\nConnected to WiFi in STA mode!");
        Serial.print("OTA URL: http://");
        Serial.print(WiFi.localIP());
        Serial.println("/");
    } else {
        // Failed to connect in STA mode, start AP mode
        Serial.println("\nFailed to connect in STA mode. Starting Access Point...");
        WiFi.mode(WIFI_AP);
        
        bool ap_result = WiFi.softAP(OTA_AP_SSID, OTA_AP_PASSWORD);
        if (!ap_result) {
            Serial.println("Failed to start Access Point!");
            return;
        }
        
        // Print AP information
        IPAddress ap_ip = WiFi.softAPIP();
        Serial.println("Access Point started successfully!");
        Serial.print("SSID: ");
        Serial.println(OTA_AP_SSID);
        Serial.print("Password: ");
        Serial.println(OTA_AP_PASSWORD);
        Serial.print("IP Address: ");
        Serial.println(ap_ip);
        Serial.print("OTA URL: http://");
        Serial.print(ap_ip);
        Serial.println("/");
    }
}

