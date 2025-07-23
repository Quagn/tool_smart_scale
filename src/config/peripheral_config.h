#ifndef PERIPHERAL_CONFIG_H
#define PERIPHERAL_CONFIG_H

//----------------------------------------------------------------------------------// Pin Mapping
// HX711 Load Cell Amplifiers
#define HX711_1_DOUT_PIN        12              // D6 - HX711 #1 Data
#define HX711_1_SCK_PIN         13              // D7 - HX711 #1 Clock

#define HX711_2_DOUT_PIN        14              // D5 - HX711 #2 Data  
#define HX711_2_SCK_PIN         4               // D2 - HX711 #2 Clock

#define HX711_3_DOUT_PIN        5               // D1 - HX711 #3 Data
#define HX711_3_SCK_PIN         16              // D0 - HX711 #3 Clock

// I2C for LCD Display
#define LCD_I2C_SDA_PIN         4               // D4 - I2C SDA
#define LCD_I2C_SCL_PIN         5               // D3 - I2C SCL

// Buttons
#define BUTTON_1_PIN            15              // D8 - Button 1 (with external pull-up)
#define BUTTON_2_PIN            3               // RX - Button 2 (use with caution)

// Servo
#define SERVO_PIN               1               // TX - Servo control (use with caution)

// Battery voltage monitoring
#define BATTERY_ADC_PIN         A0              // Analog input

// LED indicator (optional - using built-in LED)
#define LED_PIN                 LED_BUILTIN

//----------------------------------------------------------------------------------// Internal Peripherals
// ----- UART Configuration -----
#define UART0_BAUDRATE              115200
                                                                
// ----- SPI Configuration -----
// #define SPI_FREQUENCY               1000000  // 1MHz

// ----- I2C Configuration -----
#define I2C_FREQUENCY               100000      // 100kHz

// ----- PWM Configuration -----
#define SERVO_PWM_FREQ              50          // 50Hz
#define SERVO_PWM_RESOLUTION        1023        // 10-bit

// ----- ADC Configuration -----
#define ADC_RESOLUTION              10          // 10-bit

//----------------------------------------------------------------------------------// External Peripherals
// Battery
#define BATTERY_MIN_VOLTAGE     3.0f            // V - Minimum battery voltage
#define BATTERY_MAX_VOLTAGE     4.2f            // V - Maximum battery voltage
#define BATTERY_ADC_SAMPLES     5               // Number of samples for noise filtering
#define BATTERY_VOLTAGE_DIVIDER 2.0f            // Voltage divider ratio (if any)

// Button
#define BUTTON_DEBOUNCE_DELAY   50              // ms - Debounce delay
#define BUTTON_LONG_PRESS_TIME  1000            // ms - Long press time
#define BUTTON_OTA_HOLD_TIME    5000            // ms - Hold time to enter OTA mode
#define BUTTON_ACTIVE_LOW       true            // true if button active low

// Servo
#define SERVO_MIN_PULSE_WIDTH   544             // us - Minimum pulse width (0 degree)
#define SERVO_MAX_PULSE_WIDTH   2400            // us - Maximum pulse width (180 degree)
#define SERVO_REFRESH_INTERVAL  20000           // us - PWM refresh interval (50Hz)
#define SERVO_MIN_ANGLE         0               // degree - Minimum angle
#define SERVO_MAX_ANGLE         180             // degree - Maximum angle

#endif // PERIPHERAL_CONFIG_H
