/*
 * dyn_sensor.c
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 *
 * TODO: High-level functions like "distance_wall_front", etc
 *
 */

#include "dyn_app_sensor.h"
#include "dyn/dyn_instr.h"

void distance_wall_front(uint8_t *distance) {
    // Funcio que retorna distancia a paret frontal mes propera
    dyn_read_byte(0x03,DYN_REG__IR_CENTER, distance);
}

void distance_wall_left(uint8_t *distance) {
    // Funcio que retorna distancia a paret esquerra mes propera
    dyn_read_byte(0x03,DYN_REG__IR_LEFT, distance);
}

void distance_wall_right(uint8_t *distance) {
    // Funcio que retorna distancia a paret dreta mes propera
    dyn_read_byte(0x03,DYN_REG__IR_RIGHT, distance);
}








