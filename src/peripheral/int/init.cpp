#include "init.h"

void GPIO_Init(void) 
{
    pinMode(BUTTON_1_PIN, INPUT_PULLUP);
    pinMode(BUTTON_2_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

// void SPI_Init(void) 
// {
//     SPI.begin();
//     SPI.setFrequency(SPI_FREQUENCY);
// }

void I2C_Init(void) 
{
    Wire.begin(LCD_I2C_SDA_PIN, LCD_I2C_SCL_PIN);
    Wire.setClock(I2C_FREQUENCY);
}

void UART_Init(void) 
{
    Serial.begin(UART0_BAUDRATE);
}

void ADC_Init(void) 
{
    // ESP8266 doesn't support analogReadResolution
    // ADC is fixed at 10-bit resolution (0-1023)
}

void PWM_Init(void) 
{
    // ESP8266 uses analogWrite for PWM
    analogWriteFreq(SERVO_PWM_FREQ);
    analogWriteRange(SERVO_PWM_RESOLUTION);
    analogWrite(SERVO_PIN, 0);
}
