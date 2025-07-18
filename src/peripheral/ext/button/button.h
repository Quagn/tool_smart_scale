#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "config/peripheral_config.h"

typedef enum {
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED = 1,
    BUTTON_LONG_PRESSED = 2
} button_state_t;

typedef enum {
    BUTTON_EVENT_NONE = 0,
    BUTTON_EVENT_PRESS = 1,
    BUTTON_EVENT_RELEASE = 2,
    BUTTON_EVENT_LONG_PRESS = 3
} button_event_t;

typedef struct {
    uint8_t pin;
    bool active_low;
    bool current_state;
    bool last_state;
    bool debounced_state;
    unsigned long last_debounce_time;
    unsigned long press_start_time;
    bool long_press_triggered;
} button_t;

void button_init(button_t* btn, uint8_t pin, bool active_low);

void button_update(button_t* btn);

button_state_t button_read_state(button_t* btn);

button_event_t button_read_event(button_t* btn);

bool button_is_pressed(button_t* btn);

bool button_is_released(button_t* btn);

bool button_is_long_pressed(button_t* btn);

#endif // BUTTON_H 