#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "direccion.h"

Robot robot_crear(Punto pos, Punto dest) {
  Robot robot = malloc(sizeof(_Robot));
  robot->pos = pos;
  robot->dest = dest;
  robot->movimientos = pila_crear();
  robot->visitados = glist_crear();
  robot->visitados =
      glist_agregar_inicio(robot->visitados, pos,
                           (FuncionCopiadora) punto_copiar);
  return robot;
}

void robot_destruir(Robot robot) {
  glist_destruir(robot->visitados, (FuncionDestructora) punto_destruir);
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
