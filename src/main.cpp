/*
Auth: Quang Minh
Date: 18/07/2025
*/
//----------------------------------------------------------------------------------// INCLUDES
#include <Arduino.h>                                                        // Arduino core library

#include "config/peripheral_config.h"                                       // Config peripheral
#include "config/service_config.h"                                          // Config service
#include "config/sys_core_config.h"                                         // Config system core
#include "config/sys_app_config.h"                                          // Config system app

#include "peripheral/int/init.h"                                            // Init peripheral
#include "peripheral/ext/button/button.h"                                   // Button
#include "peripheral/ext/battery/battery.h"                                 // Battery
#include "peripheral/ext/servo/servo.h"                                     // Servo

#include "service/power_manager.h"                                          // Power manager
#include "service/wifi_handle.h"                                            // Wifi manager
#include "service/ota/ota_handle.h"                                         // OTA handler

#include "application/event_handle.h"                                       // Event handler
#include "application/state_machine.h"                                      // State machine

//----------------------------------------------------------------------------------// Global variables


//----------------------------------------------------------------------------------// TypeDef
button_t button1;
button_t button2;
servo_t servo;
battery_t battery;

//----------------------------------------------------------------------------------// SETUP
void setup() {   
    power_init();                                                           // Internal peripherals init
    GPIO_Init();   
    I2C_Init();
    UART_Init();
    // ADC_Init();
    // PWM_Init();
    Serial.println("Internal peripherals initialized");

    button_init(&button1, BUTTON_1_PIN, BUTTON_ACTIVE_LOW);                 // External peripherals init
    button_init(&button2, BUTTON_2_PIN, BUTTON_ACTIVE_LOW);
    battery_init(&battery, BATTERY_ADC_PIN);
    servo_init(&servo, SERVO_PIN);
    Serial.println("External peripherals initialized");

    Wifi_Init();
    
    Serial.println("Checking if we should enter OTA mode...");
    // Check if we should enter OTA mode
    //if (button_check_ota_mode_entry(&button1, BUTTON_OTA_HOLD_TIME)) 
    if (true) 
    {
        ota_init();
        ota_start();
        ota_loop();
    } else {
        // Only initialize WiFi in normal mode
        Serial.println("Smart Weight Scale ready!");
    }
}

//----------------------------------------------------------------------------------// LOOP
void loop() {
    // Web handle
    button_update(&button1);
    button_update(&button2);
    
}
