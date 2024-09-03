#ifndef __SIMULACION_H__
#define __SIMULACION_H__

#include "robot.h"
#include "mapa.h"
#include "direccion.h"

/**
 * @file simulacion.h
 * @brief Funciones relacionadas con la simulación y movimiento del robot en el mapa.
 */

/**
 * @brief Retorna 1 si el robot se pudo mover en la dirección indicada
 * (si no se choca con ningún obstáculo o se sale del tablero),
 * en caso contrario retorna 0.
 *
 * @param robot El robot que se va a intentar mover.
 * @param mapa El mapa en el que se va a mover el robot.
 * @param direccion La dirección en la que se va a intentar mover el robot.
 * @return 1 si el movimiento fue exitoso, 0 si hubo un obstáculo o se salió del tablero.
 */
int robot_mover(Robot robot, Mapa mapa, Direccion direccion);

/**
 * @brief Mueve al robot hacia su destino utilizando el algoritmo descripto en el informe.
 *
 * @param robot El robot que se va a mover hacia su destino.
 * @param mapa El mapa en el que se encuentra el robot y su destino.
 */
void robot_ir_a_destino(Robot robot, Mapa mapa);

#endif // __SIMULACION_H__