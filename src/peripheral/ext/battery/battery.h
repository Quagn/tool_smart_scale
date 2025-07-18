#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>
#include "config/peripheral_config.h"

typedef enum {
    BATTERY_CRITICAL = 0,  // < 20%
    BATTERY_LOW = 1,       // 20-40%
    BATTERY_MEDIUM = 2,    // 40-70%
    BATTERY_HIGH = 3,      // 70-90%
    BATTERY_FULL = 4       // > 90%
} battery_level_t;

typedef struct {
    uint8_t pin;
    uint16_t raw_value;
    float voltage;
    uint8_t percentage;
    battery_level_t level;
} battery_t;

void battery_init(battery_t* bat, uint8_t adc_pin);

uint16_t battery_read_raw(void);

float battery_read_voltage(void);

uint8_t battery_read_percentage(void);

battery_level_t battery_read_level(void);

bool battery_is_low(void);

#endif // BATTERY_H 