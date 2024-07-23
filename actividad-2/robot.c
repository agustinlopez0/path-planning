#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include "punto.h"
#include "matriz.h"
#include "direccion.h"
#include "funcioneslistas.h"
#include "tipos.h"

void robot_ir_a_destino(Robot robot);

int main() {
    Robot robot = malloc(sizeof(_Robot));
    robot->pos = malloc(sizeof(_Punto));
    robot->dest = malloc(sizeof(_Punto));

    int N, M;
    scanf("%d%d%d", &N, &M, &robot->sensor);
    robot->mapa = matriz_crear(N, M);

    scanf("%d%d", &robot->pos->i, &robot->pos->j);
    scanf("%d%d", &robot->dest->i, &robot->dest->j);

    robot_set_mapa(robot);
    Pila movimientos = pila_crear();
    robot->movimientos = movimientos;

    fprintf(stderr, "%ld%ld%d %d%d %d%d", 
        matriz_num_filas(robot->mapa), matriz_num_columnas(robot->mapa), robot->sensor, 
        robot->pos->i, robot->pos->j,
        robot->dest->i, robot->dest->j);

    imprimir_mapa(robot);
    fflush(stdout);



    usar_sensor(robot);
    robot_ir_a_destino(robot);


    printf ("! RRRDDRRDD\n") ;
    fflush ( stdout ) ;
    return 0;
    return 0;
}

char* copy(char* a) {
    char* copia = malloc(sizeof(char));
    *copia = *a;
    return copia;
}

void destroy(char* a) {
    free(a);
}

void robot_mover(Robot robot, Direccion direccion) {

  switch (direccion) {
  case UP:
    robot->pos->i--;
    break;
  case DOWN:
    robot->pos->i++;
    break;
  case LEFT:
    robot->pos->j--;
    break;
  case RIGHT:
    robot->pos->j++;
    break;
  }

}

void robot_ir_a_destino(Robot robot) {
  if(robot_en_destino(robot))
    return;
  
  Punto ultimaPosicion = NULL;

  do {
    punto_destruir(ultimaPosicion);
    ultimaPosicion = punto_copiar(robot->pos);
    // Si el robot esta arriba del destino
    if (robot->pos->i < robot->dest->i && 
        matriz_leer(robot->mapa, robot->pos->i + 1, robot->pos->j) == '.') {
      robot_mover(robot, DOWN);
    } else
      // Si el robot esta abajo del destino
    if (robot->pos->i > robot->dest->i && 
        matriz_leer(robot->mapa, robot->pos->i - 1, robot->pos->j) == '.') {
      robot_mover(robot, UP);
    }
    // Si el robot esta a la derecha del destino
    if (robot->pos->j > robot->dest->j && 
        matriz_leer(robot->mapa, robot->pos->i, robot->pos->j - 1) == '.') {
      robot_mover(robot, LEFT);
    } else
      // Si el robot esta a la izquierda del destino
    if (robot->pos->j < robot->dest->j && 
        matriz_leer(robot->mapa, robot->pos->i, robot->pos->j + 1) == '.') {
      robot_mover(robot, RIGHT);
    }
  } while (punto_comparar(ultimaPosicion, robot->pos) != 0);
  punto_destruir(ultimaPosicion);

  usar_sensor(robot);
  robot_ir_a_destino(robot);

}
