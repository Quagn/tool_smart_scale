#ifndef SYS_CONFIG_H
#define SYS_CONFIG_H

//--------------------------------------------------// System Core Configuration
#define CPU_FREQ                160      // 160MHz

#define TIMER_MAX_COUNT         0xFFFFFF    // 24-bit timer

#define WDT_ENABLE              1
#define WDT_TIMEOUT_MS          8000     // 8 seconds

#define DEEP_SLEEP_ENABLE       1

#define LIGHT_SLEEP_ENABLE      1   

#define SYSTEM_RESET_ENABLE     1   


#endif // SYS_CONFIG_H 