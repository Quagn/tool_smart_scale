#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include "config/sys_core_config.h"
#include <ESP8266WiFi.h>

typedef enum {
    POWER_MODE_ACTIVE = 0,     // Normal operation mode
    POWER_MODE_MODEM_SLEEP,    // Modem sleep mode (WiFi off, CPU on)
    POWER_MODE_LIGHT_SLEEP,    // Light sleep mode (WiFi off, CPU paused)
    POWER_MODE_DEEP_SLEEP      // Deep sleep mode (WiFi off, CPU off, only RTC active)
} power_mode_t;

void power_init(void);

bool power_set_mode(power_mode_t mode);

power_mode_t power_get_mode(void);

void power_deep_sleep(uint32_t sleep_time_ms);

bool power_light_sleep(void);

bool power_modem_sleep(void);

bool power_wake_up(void);

uint8_t power_get_reset_reason(void);

#endif // POWER_MANAGER_H