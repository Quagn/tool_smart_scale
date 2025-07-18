#include "init.h"

void GPIO_Init(void) {
    pinMode(BUTTON_1_PIN, INPUT_PULLUP);
    pinMode(BUTTON_2_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void SPI_Init(void) {
    SPI.begin();
    SPI.setFrequency(SPI_FREQUENCY);
}

void I2C_Init(void) {
    Wire.begin(LCD_I2C_SDA_PIN, LCD_I2C_SCL_PIN);
    Wire.setClock(I2C_FREQUENCY);
}

void UART_Init(void) {
    Serial.begin(UART0_BAUDRATE);
}

void ADC_Init(void) {
    analogReadResolution(ADC_RESOLUTION);
}

void PWM_Init(void) {
    ledcSetup(0, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(SERVO_PIN, 0);
}

void PMU_Init(void) {
    // TODO: Implement PMU initialization
}

void System_Init(void) {
    GPIO_Init();
    SPI_Init();
    I2C_Init();
    UART_Init();
}
