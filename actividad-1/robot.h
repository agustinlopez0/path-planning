#ifndef ROBOT_H
#define ROBOT_H

#include "tipos.h"
#include "mapa.h"

#include "pila.h"
#include "glist.h"

typedef struct {
  Punto pos;
  Punto dest;
  Pila movimientos;
  GList visitados;
} _Robot;

typedef _Robot *Robot;

/**
 * Retorna un robot inicializado con los valores de posicion
 *  y destino.
 */
Robot robot_crear(Punto pos, Punto dest);

/**
 * Destruye un robot y libera la memoria.
 */
void robot_destruir(Robot robot);

/**
 * Imprime los datos del robot.
 */
void robot_imprimir(Robot robot);

/**
 * Retorna 1 si el robot llego a su destino, 0 en
 *  caso contrario.
 */
int robot_en_destino(Robot robot);

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

#endif // ROBOT_H
