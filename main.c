#include <pthread.h>
#include <signal.h>
#include <assert.h>
#include "posicion.h"
#include <stdio.h>
#include <dyn/dyn_app_motor.h>
#include <dyn/dyn_app_sensor.h>
#include "dyn/dyn_app_common.h"
#include "dyn_test/dyn_emu.h"
#include "dyn_test/b_queue.h"
#include "joystick_emu/joystick.h"
#include "habitacion_001.h"

uint8_t estado = Ninguno, estado_anterior = Ninguno, finalizar = 0;

/**
 * main.c
 */

/*
 * recorreHabitacio()
 */
void recorrerHabitacio() {
    // Definim les variables que usarem.
    uint8_t distanceWallLeft;
    uint8_t distanceWallCenter;
    // Comencem Bucle-While
    while (!simulator_finished) {
        // Comencem anant cap endavant.
        move_forward();
        // Actualitzem el moviment dels simuladors i comprovem
        // la distancia a una paret amb el sensor central.
        update_movement_simulator_values();
        distance_wall_front(&distanceWallCenter);
        // Evaluem si el robot esta 0x20 (32 en decimal) casellas, llavors girem a la dreta.
        if (distanceWallCenter < 0x20) {
            // Si tenim una paret davant, girem la orientació del robot cap a la dreta.
            move_right();
        } else {
            // En cas contrari, evaluem la distancia a un obstacle del sensor esquerre.
            distance_wall_left(&distanceWallLeft);
            // Si aquesta distancia es inferior  a 0x14 (29 en decimal), llavors girem
            // lleugermanet a la esquerra. Daquesta manera aconseguim quedarnos al costat
            // de una paret.
            if (distanceWallLeft > 0x14) {
                move_left();
            }

        }
        // Per últim, tornem a actualitzar el valor dels sensors.
        update_movement_simulator_values();
    }
}

int main(void) {
    pthread_t tid, jid;
    uint8_t tmp;

    //Init queue for TX/RX data
    init_queue(&q_tx);
    init_queue(&q_rx);

    //Start thread for dynamixel module emulation
    // Passing the room information to the dyn_emu thread
    pthread_create(&tid, NULL, dyn_emu, (void *) datos_habitacion);
    pthread_create(&jid, NULL, joystick_emu, (void *) &jid);


    //Testing some high level function
    printf("\nSetting LED to 0 \n");
    dyn_led_control(1, 0);
    printf("\nGetting LED value \n");
    dyn_led_read(1, &tmp);
    assert(tmp == 0);
    printf("\nSetting LED to 1 \n");
    dyn_led_control(1, 1);
    printf("\nGetting LED value \n");
    dyn_led_read(1, &tmp);
    assert(tmp == 1);
    printf("\n************************\n");
    printf("Test passed successfully\n");

    printf("\nDimensiones habitacion %d ancho x %d largo mm2\n", ANCHO, LARGO);
    printf("En memoria: %I64u B = %I64u MiB\n", sizeof(datos_habitacion), sizeof(datos_habitacion) >> 20);

    printf("Pulsar 'q' para terminar, qualquier tecla para seguir\n");
    fflush(stdout);//	return 0;

    while (estado != Quit) {
        if (simulator_finished) {
            break;
        }
        Get_estado(&estado, &estado_anterior);
        if (estado != estado_anterior) {
            Set_estado_anterior(estado);
            printf("estado = %d\n", estado);
            switch (estado) {
                case Sw1:
                    printf("Boton Sw1 ('a') apretado\n");
                    dyn_led_control(1, 1); //Probaremos de encender el led del motor 2
                    printf("\n");
                    break;
                case Sw2:
                    printf("Boton Sw2 ('s') apretado\n");
                    dyn_led_control(1, 0); //Probaremos de apagar el led del motor 2
                    printf("\n");
                    break;
                case Up:
                    printf("Boton Up ('i') apretado\n");
                    // Boton a clicar para empezar el movimiento del robot.
                    // Iniciamos el simulador de movimiento pasandole la habitación
                    init_movement_simulator(datos_habitacion);
                    //Ejecutamos el método para que el robot recorra una habitación
                    recorrerHabitacio();
                    break;
                case Down:
                    printf("Boton Down ('m') apretado\n");

                    break;
                case Left:
                    printf("Boton Left ('j') apretado\n");
                    //Comprobaremos si detectamos las esquinas de la pared izquierda:
                    printf("Esquina inferior izquierda:\n");
                    printf("(1, 1): %d (fuera pared)\n", obstaculo(1, 1, datos_habitacion));
                    printf("(0, 1): %d (pared izq.)\n", obstaculo(0, 1, datos_habitacion));
                    printf("(1, 0): %d (pared del.)\n", obstaculo(1, 0, datos_habitacion));
                    printf("(0, 0): %d (esquina)\n", obstaculo(0, 0, datos_habitacion));
                    printf("Esquina superior izquierda:\n");
                    printf("(1, 4094): %d (fuera pared)\n", obstaculo(1, 4094, datos_habitacion));
                    printf("(0, 4094): %d (pared izq.)\n", obstaculo(0, 4094, datos_habitacion));
                    printf("(1, 4095): %d (pared fondo.)\n", obstaculo(1, 4095, datos_habitacion));
                    printf("(0, 4095): %d (esquina)\n", obstaculo(0, 4095, datos_habitacion));
                    break;
                case Right:
                    printf("Boton Right ('l') apretado\n");
                    //Comprobaremos si detectamos las esquinas de la pared derecha:
                    printf("Esquina inferior derecha:\n");
                    printf("(4094, 1): %d (fuera pared)\n", obstaculo(4094, 1, datos_habitacion));
                    printf("(4094, 0): %d (pared del.)\n", obstaculo(4094, 0, datos_habitacion));
                    printf("(4095, 1): %d (pared der.)\n", obstaculo(4095, 1, datos_habitacion));
                    printf("(4095, 0): %d (esquina)\n", obstaculo(4095, 0, datos_habitacion));
                    printf("Esquina superior derecha:\n");
                    printf("(4094, 4094): %d (fuera pared)\n", obstaculo(4094, 4094, datos_habitacion));
                    printf("(4094, 4095): %d (pared fondo)\n", obstaculo(4094, 4095, datos_habitacion));
                    printf("(4095, 4094): %d (pared der.)\n", obstaculo(4095, 4094, datos_habitacion));
                    printf("(4095, 4095): %d (esquina)\n", obstaculo(4095, 4095, datos_habitacion));
                    break;
                case Center:
                    printf("Boton Center ('k') apretado\n");
                    break;
                case Quit:
                    printf("Adios!\n");
                    break;
                    //etc, etc...
            }
            fflush(stdout);
        }
    }
    //Signal the emulation thread to stop
    pthread_kill(tid, SIGTERM);
    pthread_kill(jid, SIGTERM);
    printf("Programa terminado\n");
    fflush(stdout);
}
