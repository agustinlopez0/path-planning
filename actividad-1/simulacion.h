#ifndef __SIMULACION_H__
#define __SIMULACION_H__
#include "robot.h"
#include "mapa.h"
#include "direccion.h"

/**
 * Imprime el mapa marcando las celdas visitadas por el robot,
 *  ademas muestra la posicion actual del robot y su destino 
 */
void mostrar_robot_mapa(Robot robot, Mapa mapa);

/**
 * Retorna 1 si el robot se pudo mover en la direccion indicada
 *  (si no se choca ningun obstaculo o se sale del tablero),
 *  en caso contrario retorna 0.
 */
int robot_mover(Robot robot, Mapa mapa, Direccion direccion);

/**
 * Vuelve a la posicion anterior utilizando la pila de movimientos.
 */
int robot_retroceder(Robot robot, Mapa mapa);

/**
 * Mueve al robot hacia su destino.
 */
int robot_ir_a_destino(Robot robot, Mapa mapa);


#endif // __SIMULACION_H__
