#include "button.h"

void button_init(button_t* btn, uint8_t pin, bool active_low) {
    btn->pin = pin;
    btn->active_low = active_low;
    btn->current_state = false;
    btn->last_state = false;
    btn->debounced_state = false;
    btn->last_debounce_time = 0;
    btn->press_start_time = 0;
    btn->long_press_triggered = false;
    
    // Cấu hình pin với pull-up internal
    pinMode(pin, INPUT_PULLUP);
}

void button_update(button_t* btn) {
    // Đọc trạng thái thô của button
    bool raw_state = digitalRead(btn->pin);
    
    // Áp dụng logic active low/high
    bool pressed = btn->active_low ? !raw_state : raw_state;
    
    // Debounce logic
    if (pressed != btn->last_state) {
        btn->last_debounce_time = millis();
    }
    
    if ((millis() - btn->last_debounce_time) > BUTTON_DEBOUNCE_DELAY) {
        if (pressed != btn->debounced_state) {
            btn->debounced_state = pressed;
            
            if (pressed) {
                // Button được nhấn
                btn->press_start_time = millis();
                btn->long_press_triggered = false;
            }
        }
    }
    
    // Kiểm tra long press
    if (btn->debounced_state && !btn->long_press_triggered) {
        if ((millis() - btn->press_start_time) >= BUTTON_LONG_PRESS_TIME) {
            btn->long_press_triggered = true;
        }
    }
    
    btn->current_state = btn->debounced_state;
    btn->last_state = pressed;
}

button_state_t button_read_state(button_t* btn) {
    if (btn->long_press_triggered) {
        return BUTTON_LONG_PRESSED;
    } else if (btn->current_state) {
        return BUTTON_PRESSED;
    } else {
        return BUTTON_RELEASED;
    }
}

button_event_t button_read_event(button_t* btn) {
    static bool last_debounced_state = false;
    static bool last_long_press_state = false;
    
    button_event_t event = BUTTON_EVENT_NONE;
    
    // Kiểm tra long press event
    if (btn->long_press_triggered && !last_long_press_state) {
        event = BUTTON_EVENT_LONG_PRESS;
    }
    // Kiểm tra press event
    else if (btn->debounced_state && !last_debounced_state) {
        event = BUTTON_EVENT_PRESS;
    }
    // Kiểm tra release event
    else if (!btn->debounced_state && last_debounced_state) {
        event = BUTTON_EVENT_RELEASE;
    }
    
    last_debounced_state = btn->debounced_state;
    last_long_press_state = btn->long_press_triggered;
    
    return event;
}

bool button_is_pressed(button_t* btn) {
    return btn->current_state;
}

bool button_is_released(button_t* btn) {
    return !btn->current_state;
}

bool button_is_long_pressed(button_t* btn) {
    return btn->long_press_triggered;
} 