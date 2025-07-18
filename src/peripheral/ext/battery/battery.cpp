#include "battery.h"

void battery_init(battery_t* bat, uint8_t adc_pin) {
    bat->pin = adc_pin;
    bat->raw_value = 0;
    bat->voltage = 0;
    bat->percentage = 0;
    bat->level = BATTERY_FULL;

    pinMode(bat->pin, INPUT);
}

uint16_t battery_read_raw(battery_t* bat) {
    uint32_t sum = 0;
    
    // Lấy trung bình nhiều mẫu để giảm nhiễu
    for (uint8_t i = 0; i < BATTERY_ADC_SAMPLES; i++) {
        sum += analogRead(bat->pin);
        delay(2); // Delay nhỏ giữa các lần đọc
    }
    
    bat->raw_value = (uint16_t)(sum / BATTERY_ADC_SAMPLES);

    return bat->raw_value;
}

float battery_read_voltage(battery_t* bat) {
    uint16_t raw_value = bat->raw_value;
    
    // Chuyển đổi ADC sang điện áp
    // ESP8266 có ADC 10-bit, Vref = 3.3V
    bat->voltage = (raw_value * 3.3f) / 1023.0f;
    
    // Áp dụng voltage divider nếu có
    bat->voltage *= BATTERY_VOLTAGE_DIVIDER;

    return bat->voltage;
}

uint8_t battery_read_percentage(battery_t* bat) {
    float voltage = bat->voltage;
    
    // Giới hạn điện áp trong khoảng min-max
    if (voltage < BATTERY_MIN_VOLTAGE) {
        return 0;
    }
    if (voltage > BATTERY_MAX_VOLTAGE) {
        return 100;
    }
    
    // Tính phần trăm tuyến tính
    float percentage = ((voltage - BATTERY_MIN_VOLTAGE) / 
                       (BATTERY_MAX_VOLTAGE - BATTERY_MIN_VOLTAGE)) * 100.0f;
    
    bat->percentage = (uint8_t)percentage;

    return bat->percentage;
}

battery_level_t battery_read_level(battery_t* bat) {
    uint8_t percentage = bat->percentage;
    
    if (percentage < 20) {
        return BATTERY_CRITICAL;
    } else if (percentage < 40) {
        return BATTERY_LOW;
    } else if (percentage < 70) {
        return BATTERY_MEDIUM;
    } else if (percentage < 90) {
        return BATTERY_HIGH;
    } else {
        return BATTERY_FULL;
    }

    return bat->level;
}

bool battery_is_low(battery_t* bat) {
    battery_level_t level = bat->level;
    return (level == BATTERY_CRITICAL || level == BATTERY_LOW);
} 