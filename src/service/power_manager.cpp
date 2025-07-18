#include "power_manager.h"

// Current power mode
static power_mode_t current_power_mode = POWER_MODE_ACTIVE;

void power_init(void) 
{
    // Initialize power management
    #if WDT_ENABLE
        ESP.wdtEnable(WDT_TIMEOUT_MS);
    #else
        ESP.wdtDisable();
    #endif
    
    // Set CPU frequency
    system_update_cpu_freq(CPU_FREQ);
    
    current_power_mode = POWER_MODE_ACTIVE;
}

bool power_set_mode(power_mode_t mode) 
{
    bool result = true;
    
    switch (mode) {
        case POWER_MODE_ACTIVE:
            result = power_wake_up();
            break;
            
        case POWER_MODE_MODEM_SLEEP:
            result = power_modem_sleep();
            break;
            
        case POWER_MODE_LIGHT_SLEEP:
            result = power_light_sleep();
            break;
            
        case POWER_MODE_DEEP_SLEEP:
            // Deep sleep requires a time parameter, so this function
            // should not be used directly for deep sleep
            result = false;
            break;
            
        default:
            result = false;
            break;
    }
    
    if (result) {
        current_power_mode = mode;
    }
    
    return result;
}

power_mode_t power_get_mode(void) 
{
    return current_power_mode;
}

void power_deep_sleep(uint32_t sleep_time_ms) 
{
    #if DEEP_SLEEP_ENABLE
        // Prepare for deep sleep
        Serial.println("Entering deep sleep mode");
        Serial.flush();
        
        // ESP8266 deep sleep function (time in microseconds)
        ESP.deepSleep(sleep_time_ms * 1000);
        
        // Code after deepSleep() will not be executed
        current_power_mode = POWER_MODE_DEEP_SLEEP;
    #endif
}

bool power_light_sleep(void) 
{
    bool result = false;
    
    #if LIGHT_SLEEP_ENABLE
        // ESP8266 light sleep mode
        Serial.println("Entering light sleep mode");
        Serial.flush();
        
        // Disable WiFi
        WiFi.mode(WIFI_OFF);
        WiFi.forceSleepBegin();
        delay(1); // Allow WiFi to turn off
        
        // Enter light sleep mode
        wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
        wifi_fpm_open();
        wifi_fpm_do_sleep(0xFFFFFFF); // Sleep indefinitely until external event
        
        current_power_mode = POWER_MODE_LIGHT_SLEEP;
        result = true;
    #endif
    
    return result;
}

bool power_modem_sleep(void) 
{
    // Modem sleep (WiFi off, but CPU still running)
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    delay(1); // Allow WiFi to turn off
    
    current_power_mode = POWER_MODE_MODEM_SLEEP;
    return true;
}

bool power_wake_up(void) 
{
    bool result = true;
    
    switch (current_power_mode) {
        case POWER_MODE_MODEM_SLEEP:
            // Wake up from modem sleep
            WiFi.forceSleepWake();
            delay(1); // Give time for WiFi to wake up
            break;
            
        case POWER_MODE_LIGHT_SLEEP:
            #if LIGHT_SLEEP_ENABLE
                // Wake up from light sleep
                wifi_fpm_do_wakeup();
                wifi_fpm_close();
                WiFi.forceSleepWake();
                delay(1); // Give time for system to stabilize
            #endif
            break;
            
        case POWER_MODE_DEEP_SLEEP:
            // Cannot wake up from deep sleep programmatically
            // (system will reset)
            result = false;
            break;
            
        case POWER_MODE_ACTIVE:
        default:
            // Already active
            break;
    }
    
    if (result) {
        current_power_mode = POWER_MODE_ACTIVE;
    }
    
    return result;
}

uint8_t power_get_reset_reason(void) 
{
    return ESP.getResetInfoPtr()->reason;
}
