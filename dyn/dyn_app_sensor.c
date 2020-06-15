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
    // Funcio que retorna distancia a paret frontal mes propera. El funcionament es simple, llegim el byte del registre global DYN_REG__IR_CEMTER.
    // Com a parametre només hem de passar el id del Mòdul Dynamixel del que volem llegir, que en aquest cas es 3. (Sensor)
    dyn_read_byte(0x03,DYN_REG__IR_CENTER, distance);
}

void distance_wall_left(uint8_t *distance) {
    // Funcio que retorna distancia a paret esquerra mes propera. El funcionament es simple, llegim el byte del registre global DYN_REG__IR_LEFT.
    // Com a parametre només hem de passar el id del Mòdul Dynamixel del que volem llegir, que en aquest cas es 3. (Sensor)
    dyn_read_byte(0x03,DYN_REG__IR_LEFT, distance);
}

void distance_wall_right(uint8_t *distance) {
    // Funcio que retorna distancia a paret dreta mes propera. El funcionament es simple, llegim el byte del registre global DYN_REG__IR_RIGHT.
    // Com a parametre només hem de passar el id del Mòdul Dynamixel del que volem llegir, que en aquest cas es 3. (Sensor)
    dyn_read_byte(0x03,DYN_REG__IR_RIGHT, distance);
}








