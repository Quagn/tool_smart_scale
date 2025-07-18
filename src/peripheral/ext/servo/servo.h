#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>
#include "config/peripheral_config.h"

typedef struct {
    uint8_t pin;
    uint16_t current_angle;
    uint16_t target_angle;
    unsigned long last_update_time;
    bool attached;
} servo_t;

void servo_init(servo_t* srv, uint8_t pin);

void servo_attach(servo_t* srv);

void servo_detach(servo_t* srv);

void servo_write_angle(servo_t* srv, uint16_t angle);

void servo_write_microseconds(servo_t* srv, uint16_t microseconds);

uint16_t servo_read_angle(servo_t* srv);

bool servo_is_attached(servo_t* srv);

void servo_update(servo_t* srv);

void servo_move_to(servo_t* srv, uint16_t target_angle, uint16_t speed);

#endif // SERVO_H 