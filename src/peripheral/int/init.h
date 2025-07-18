#ifndef INIT_H
#define INIT_H

#include "sys_pin_mapping.h"
#include "peripheral_config.h"

void GPIO_Init(void);
void SPI_Init(void);
void I2C_Init(void);
void UART_Init(void);
void ADC_Init(void);
void PWM_Init(void);
void PMU_Init(void);
void System_Init(void);     

#endif // INIT_H
