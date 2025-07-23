#include "event_handle.h"

bool button_check_ota_mode_entry(button_t* btn, unsigned long hold_time_ms) 
{
    button_update(btn);
    while (button_read_state(btn) == BUTTON_LONG_PRESSED || button_read_state(btn) == BUTTON_PRESSED)
    {
        if (millis() - btn->press_start_time >= hold_time_ms)
        {
            return true;
        }
        button_update(btn);
        delay(10);
    }
    return false;
} 