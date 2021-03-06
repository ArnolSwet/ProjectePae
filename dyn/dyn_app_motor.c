//
// Created by Arnau Cirera on 01/05/2020.
//

#include "dyn_app_motor.h"
#include "dyn/dyn_frames.h"
#include "dyn/dyn_instr.h"

bool direction_backward; //Declarem un boleà que indiqui la direcció que volem (true: endavant, false: endarrere)
uint8_t motor_L; //Definim la variable d'un byte que contindrà el valor del registre MOV_SPEED_L
uint8_t motor_H; //Definim la variable d'un byte que contindrà el valor del registre MOV_SPEED_H

void move_forward(void) {
    uint16_t speed = 0x3FE;
    direction_backward = false; // Declarem la direcció com a false(moviment endavant)
    uint8_t direction = (uint8_t) direction_backward; //Fem un cast al boleà direcció per utilitzar-lo com a un enter de 8 bits (true = 0x01, false = 0x00)
    motor_L = speed & 0xFF; //Definim els primers 8 bits del registre MOV_SPEED que contindran els primers 8 bits del valor speed (Per això a la variable speed la trunquem pels primers 8 bits)
    motor_H = ((direction<<2)&0x04)|((speed>>8)&0x03); //Definim els 8 bits restants de MOV_SPEED (Per això el bit de la direcció el desplacem 2 bits a l'esquerra per deixar espai als 2 bits restants de speed que queden després de treure els 8 primers que ja hem passat, fent el desplaçament de 8 bits a la dreta)
    dyn_write_byte(0x01, DYN_REG__MOV_SPEED_L, motor_L); //Escribim al mòdul 0x01 (Motor dret) al registre MOV_SPEED_L el valor que li hem assignat
    dyn_write_byte(0x01, DYN_REG__MOV_SPEED_H, motor_H); //Escribim al mòdul 0x01 (Motor dret) al registre MOV_SPEED_H el valor que li hem assignat
    dyn_write_byte(0x02, DYN_REG__MOV_SPEED_L, motor_L); //Escribim al mòdul 0x02 (Motor esquerra) al registre MOV_SPEED_L el valor que li hem assignat
    dyn_write_byte(0x02, DYN_REG__MOV_SPEED_H, motor_H); //Escribim al mòdul 0x02 (Motor esquerra) al registre MOV_SPEED_H el valor que li hem assignat
}

void move_backward(void) {
    uint16_t speed = 0x3FE;
    // El moviment enrere és exactament igual que el moviment endavant però al inici declarem la variable direcció com a true (sentit endarrere)
    direction_backward = true;
    uint8_t direction = (uint8_t) direction_backward;
    motor_L = speed & 0xFF;
    motor_H = ((direction<<2)&0x04)|((speed>>8)&0x03);
    dyn_write_byte(0x01, DYN_REG__MOV_SPEED_L, motor_L);
    dyn_write_byte(0x01, DYN_REG__MOV_SPEED_H, motor_H);
    dyn_write_byte(0x02, DYN_REG__MOV_SPEED_L, motor_L);
    dyn_write_byte(0x02, DYN_REG__MOV_SPEED_H, motor_H);
}
/*
void go_faster(void) {
    if (speed < 0x39B) {
        speed += 0x64;
    }else if (speed > 0x39B) {
        speed = 0x3FF;
    }
}

void go_slower(void) {
    if (speed > 0xC8) {
        speed -= 0x64;
    }else if (speed < 0xC8) {
        speed = 0x64;
    }
}
 */

void move_left(void) {
    // El moviment cap a l'esquerra el fem definint un motor endavant i l'altre parat
    // el motor dret (0x01) en direcció endavant
    direction_backward = false; // Declarem el sentit del motor (endavant)
    uint8_t direction = (uint8_t) direction_backward;
    uint16_t speed = 0x1F4;
    motor_L = speed & 0xFF;
    motor_H = ((direction<<2)&0x04)|((speed>>8)&0x03);

    dyn_write_byte(0x01, DYN_REG__MOV_SPEED_L, motor_L);
    dyn_write_byte(0x01, DYN_REG__MOV_SPEED_H, motor_H); //Al motor 0x01 (dreta) li passem amb el bit de direcció a 0 (endavant)

}

void move_right(void) {
    // El moviment cap a la dreta és exactament igual que el moviment a l'esquerra,
    // però en aquest cas el motor esquerra (0x02) és el que gira
    direction_backward = false;
    uint8_t direction = (uint8_t) direction_backward;
    uint16_t speed = 0x1F4;
    motor_L = speed & 0xFF;
    motor_H = ((direction<<2)&0x04)|((speed>>8)&0x03);
    dyn_write_byte(0x02, DYN_REG__MOV_SPEED_L, motor_L);
    dyn_write_byte(0x02, DYN_REG__MOV_SPEED_H, motor_H); //Al motor 0x01(esquerra) li passem amb el bit de direcció a 0 (endavant)

}

void move_continuous(void) {
    // Per realitzar un moviment dels motors continu, tal com diu el manual dels motors,
    // hem de definir els dos registres de CW ANGLE LIMIT (0x06 i 0x07) i els dos registres de CCW ANGLE LIMIT (0x08 i 0x09) a 0.
    // Això ho hem de fer pels dos motors.
    dyn_write_byte(0x01, DYN_REG__CW_ANGLE_LIMIT_L, 0x00); //Definim a 0 el registre de nivell baix de CW ANGLE LIMIT pel motor 0x01(esquerra)
    dyn_write_byte(0x01, DYN_REG__CW_ANGLE_LIMIT_H, 0x00); //Definim a 0 el registre de nivell alt de CW ANGLE LIMIT pel motor 0x01(esquerra)
    dyn_write_byte(0x01, DYN_REG__CCW_ANGLE_LIMIT_L, 0x00); //Definim a 0 el registre de nivell baix de CCW ANGLE LIMIT pel motor 0x01(esquerra)
    dyn_write_byte(0x01, DYN_REG__CCW_ANGLE_LIMIT_H, 0x00); //Definim a 0 el registre de nivell alt de CCW ANGLE LIMIT pel motor 0x01(esquerra)
    dyn_write_byte(0x02, DYN_REG__CW_ANGLE_LIMIT_L, 0x00); //Definim a 0 el registre de nivell baix de CW ANGLE LIMIT pel motor 0x01(dreta)
    dyn_write_byte(0x02, DYN_REG__CW_ANGLE_LIMIT_H, 0x00); //Definim a 0 el registre de nivell alt de CW ANGLE LIMIT pel motor 0x01(dreta)
    dyn_write_byte(0x02, DYN_REG__CCW_ANGLE_LIMIT_L, 0x00); //Definim a 0 el registre de nivell baix de CCW ANGLE LIMIT pel motor 0x01(dreta)
    dyn_write_byte(0x02, DYN_REG__CCW_ANGLE_LIMIT_H, 0x00); //Definim a 0 el registre de nivell alt de CCW ANGLE LIMIT pel motor 0x01(dreta)
}

void dyn_speed_read(uint8_t id, uint16_t *val) {
    //Aquest és el mètode per llegir  els valors del registre MOVE_SPEED pels tests.
    //Retornarem una variable de 16bits per poder representar de manera més fàcil i clara el paquet sencer que ha de donar als assert.
    //Com que ho tenim amb dos registres diferents de 8 bits cada un (ja que UART no permet transmetre 16 bits) Haurem de agafar per separat en dos variables de 8 bits
    //I després ajuntar-ho en una de 16 bits.
    uint8_t mov_speed_L; // Declarem variable de 8 bits per la part baixa del registre.
    uint8_t mov_speed_H; // Declarem variable de 8 bits per la part alta del registre.
    dyn_read_byte(id,DYN_REG__MOV_SPEED_L,&mov_speed_L); //Cridem al mètode per llegir un byte del registre passat per paràmetre del mòdul indicat.
    dyn_read_byte(id,DYN_REG__MOV_SPEED_H,&mov_speed_H); //Tornem a cridar al mètode per l'altre byte del registre
    //Per ajuntar els 2 bytes primer desplacem 8 bits a l'esquerra la part alta del registre i la convertim a 16 bits. Quedarà així: XXXXXXXX00000000b
    //Tot seguit fem un OR amb el nivell baix del registre (MOV_SPEED_L) per ajuntar-ho tot, de manera que quedarà així: XXXXXXXXYYYYYYYYb (X = MOV SPEED H, Y = MOV SPEED L)
    *val = ((uint16_t)mov_speed_H << 8) | (uint8_t)mov_speed_L;
}