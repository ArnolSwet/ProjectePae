//
// Created by Arnau Cirera on 01/05/2020.
//

#ifndef JOYSTICK_DYN_APP_MOTOR_H
#define JOYSTICK_DYN_APP_MOTOR_H

#include <stdint.h>

void move_forward(void);

void move_backward(void);

void go_faster(void);

void go_slower(void);

void move_left(void);

void move_right(void);

void move_continuous(void);

void dyn_speed_read(uint8_t id, uint16_t *val);

#endif //JOYSTICK_DYN_APP_MOTOR_H
