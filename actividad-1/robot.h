#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "punto.h"
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
Robot robot_crear(Punto pos, Punto dest, FuncionCopiadora copy_punto);

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



#endif // __ROBOT_H__
