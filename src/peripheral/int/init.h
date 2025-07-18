#ifndef INIT_H
#define INIT_H

#include <Arduino.h>
//#include <SPI.h>
#include <Wire.h>
#include "config/peripheral_config.h"

void GPIO_Init(void);
//void SPI_Init(void);
void I2C_Init(void);
void UART_Init(void);
void ADC_Init(void);
void PWM_Init(void);

#endif // INIT_H
