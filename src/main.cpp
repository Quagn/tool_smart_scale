/*
Auth: Quang Minh
Date: 18/07/2025
*/
//----------------------------------------------------------------------------------// INCLUDES
#include <Arduino.h>                                                        // Arduino core library

#include "config/peripheral_config.h"                                       // Config peripheral
#include "config/sys_core_config.h"                                         // Config system core

#include "peripheral/int/init.h"                                            // Init peripheral
#include "peripheral/ext/button/button.h"                                  // Button
#include "peripheral/ext/battery/battery.h"                                // Battery
#include "peripheral/ext/servo/servo.h"                                    // Servo

#include "service/power_manager.h"                                          // Power manager
// #include <ESPAsyncWebServer.h>
// #include <ElegantOTA.h>

//----------------------------------------------------------------------------------// Global variables

//----------------------------------------------------------------------------------// TypeDef
button_t button;
servo_t servo;
battery_t battery;

//AsyncWebServer server(80);

//----------------------------------------------------------------------------------// Function

//----------------------------------------------------------------------------------// SETUP
void setup() 
{
    Serial.begin(9600);
    // Init power manager
    power_init();
    Serial.println("System initialized");

    // Init internal peripheral
    GPIO_Init();
    I2C_Init();
    UART_Init();
    ADC_Init();
    PWM_Init();
    Serial.println("Internal peripheral initialized");

    // Init OTA
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    //     request->send(200, "text/plain", "Hi! This is ElegantOTA AsyncDemo.");
    // });

    // ElegantOTA.begin(&server);    // Start ElegantOTA
    // server.begin();
    // Serial.println("HTTP server started");

    
    Serial.println("OTA initialized");

    // Init external peripheral
    button_init(&button, BUTTON_1_PIN, BUTTON_ACTIVE_LOW);
    battery_init(&battery,  BATTERY_ADC_PIN);
    servo_init(&servo, SERVO_PIN);
    Serial.println("External peripheral initialized");
    
}

//----------------------------------------------------------------------------------// LOOP
void loop() 
{
    button_update(&button);
    Serial.println(button_read_state(&button));
    //ElegantOTA.loop();
    //delay(1000);
}
