#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "punto.h"
#include "glist.h"
#include "pila.h"
#include "tablahash.h"

/**
 * @file robot.h
 * @brief Definición y funciones relacionadas con la estructura Robot.
 */

/**
 * @struct _Robot
 * @brief Estructura que representa un robot en un mapa y la información que tiene/recolecta de su entorno.
 */
typedef struct {
  Punto pos; 
  Punto dest; 
  Pila movimientos;
  TablaHash visitados; 
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
 */
void robot_retroceder(Robot robot);

/**
 * @brief Destruye un robot y libera la memoria ocupada por sus campos.
 *
 * @param robot Robot a destruir.
 */
void robot_destruir(Robot robot);

#endif // __ROBOT_H__
