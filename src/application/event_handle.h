#ifndef EVENT_HANDLE_H
#define EVENT_HANDLE_H

#include "peripheral/ext/button/button.h"

bool button_check_ota_mode_entry(button_t* btn, unsigned long hold_time_ms);

#endif