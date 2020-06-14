/*
 * dyn_sensor.h
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 */

#ifndef DYN_SENSOR_H_
#define DYN_SENSOR_H_

#include <stdint.h>

void distance_wall_front(uint8_t *distance);
void distance_wall_left(uint8_t *distance);
void distance_wall_right(uint8_t *distance);


#endif /* DYN_SENSOR_H_ */
