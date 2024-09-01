#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "direccion.h"

unsigned punto_hash(Punto punto) {
  return punto->i * 31 + punto->j;
}

Robot robot_crear(Punto pos, Punto dest) {
  Robot robot = malloc(sizeof(_Robot));
  robot->pos = pos;
  robot->dest = dest;
  robot->movimientos = pila_crear();
  robot->visitados = tablahash_crear(100, (FuncionCopiadora) punto_copiar,
                                     (FuncionComparadora) punto_comparar,
                                     (FuncionDestructora) punto_destruir,
                                     (FuncionHash) punto_hash);
  tablahash_insertar(robot->visitados, pos);

  return robot;
}

void robot_destruir(Robot robot) {
  tablahash_destruir(robot->visitados);
  pila_destruir(robot->movimientos,
                (FuncionDestructora) direccion_destruir);
  punto_destruir(robot->pos);
  punto_destruir(robot->dest);
  free(robot);
}

void robot_imprimir(Robot robot) {
  printf("Robot:");
  printf("\tPosicion: (%d, %d)\n", robot->pos->i, robot->pos->j);
  printf("\tDestino: (%d, %d)\n", robot->dest->i, robot->dest->j);
}

int robot_en_destino(Robot robot) {
  return punto_comparar(robot->pos, robot->dest) == 0;
}

int robot_retroceder(Robot robot) {
  if (pila_es_vacia(robot->movimientos))
    return 0;

  // Obtener la última dirección desde la pila
  Direccion *ultima_direccion = pila_tope(robot->movimientos);
  Direccion direccion = direccion_opuesta(*ultima_direccion);

  // Mover el robot en la dirección opuesta
  if (direccion == DOWN)
    robot->pos->i++;
  else if (direccion == UP)
    robot->pos->i--;
  else if (direccion == LEFT)
    robot->pos->j--;
  else if (direccion == RIGHT)
    robot->pos->j++;

  robot->movimientos =
      pila_desapilar(robot->movimientos,
                     (FuncionDestructora) direccion_destruir);

  return 1;
}
