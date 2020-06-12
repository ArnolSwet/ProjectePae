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
#include "dyn/dyn_frames.h"
#include "dyn/dyn_instr.h"


uint8_t distanceRi;
uint8_t distanceLe;

void distance_wall_front(uint8_t *distance) {
    dyn_read_byte(0x03,DYN_REG__IR_CENTER, distance);
    /* No usem ara matiex
    dyn_read_byte(0x03,DYN_REG__IR_LEFT, distanceRi);
    dyn_read_byte(0x03,DYN_REG__IR_RIGHT, distanceLe);*/
}




