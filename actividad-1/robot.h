#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "punto.h"
#include "pila.h"
#include "glist.h"
#include "tablahash.h"

/**
 * @file robot.h
 * @brief Definición y funciones relacionadas con la estructura Robot.
 */

typedef struct {
  Punto pos; /**< Posición actual del robot */
  Punto dest; /**< Destino del robot */
  Pila movimientos; /**< Pila de movimientos realizados por el robot */
  TablaHash visitados; /**< Lista de celdas visitadas por el robot */
} _Robot;

typedef _Robot *Robot;

/**
 * @brief Crea un nuevo robot con la posición y destino especificados.
 *
 * @param pos Punto inicial del robot.
 * @param dest Punto destino del robot.
 * @return Robot inicializado.
 */
Robot robot_crear(Punto pos, Punto dest);

/**
 * @brief Destruye un robot y libera la memoria ocupada por él.
 *
 * @param robot Robot a destruir.
 */
void robot_destruir(Robot robot);

/**
 * @brief Imprime los detalles del robot: posición y destino.
 *
 * @param robot Robot a imprimir.
 */
void robot_imprimir(Robot robot);

/**
 * @brief Verifica si el robot ha alcanzado su destino.
 *
 * @param robot Robot a verificar.
 * @return 1 si el robot está en su destino, 0 en caso contrario.
 */
int robot_en_destino(Robot robot);

/**
 * @brief Retrocede el robot a su posición anterior utilizando la pila de movimientos.
 *
 * @param robot Robot a retroceder.
 * @return 1 si se pudo retroceder, 0 si la pila de movimientos está vacía.
 */
int robot_retroceder(Robot robot);

#endif // __ROBOT_H__
