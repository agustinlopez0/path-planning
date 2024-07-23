#include "tipos2.h"
#include "direccion.h"
#include "funcioneslistas.h"
#include <stdio.h>

void usar_sensor(Robot robot) {
    printf("? %d %d\n", robot->pos->i, robot->pos->j);
    fflush(stdout);

    int d1, d2, d3, d4;
    scanf("%d %d %d %d", &d1, &d2, &d3, &d4);

    size_t num_filas = matriz_num_filas(robot->mapa);
    size_t num_columnas = matriz_num_columnas(robot->mapa);

    fprintf(stderr, "\nBREAKPOINT\n");
    // Actualizar posiciones hacia arriba
    if (d1 > 1 ) {
        for (int i = 0; i < d1; i++) {
            if ((size_t)(robot->pos->i - i) < num_filas) {
                matriz_escribir(robot->mapa, robot->pos->i - i, robot->pos->j, '.');
            }
        }
    }

    // Actualizar posiciones hacia abajo
    if (d2 > 1 ) {
        for (int i = 0; i < d2; i++) {
            if ((size_t)(robot->pos->i + i) < num_filas) {
                matriz_escribir(robot->mapa, robot->pos->i + i, robot->pos->j, '.');
            }
        }
    }

    // Actualizar posiciones hacia la izquierda
    if (d3 > 1 ) {
        for (int i = 0; i < d3; i++) {
            if ((size_t)(robot->pos->j - i) >= 0) {
                matriz_escribir(robot->mapa, robot->pos->i, robot->pos->j - i, '.');
            }
        }
    }

    // Actualizar posiciones hacia la derecha
    if (d4 > 1 ) {
        for (int i = 0; i < d4; i++) {
            if ((size_t)(robot->pos->j + i) < num_columnas) {
                matriz_escribir(robot->mapa, robot->pos->i, robot->pos->j + i, '.');
            }
        }
    }

    imprimir_mapa(robot);
}

int robot_en_destino(Robot robot){
  return punto_comparar(robot->pos, robot->dest) == 0;
}

void robot_set_mapa(Robot robot) {
    int n = (int)matriz_num_filas(robot->mapa);
    int m = (int)matriz_num_columnas(robot->mapa);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matriz_escribir(robot->mapa, i, j, '#');
}


void imprimir_mapa(Robot robot) {
    fprintf(stderr, "\n");
    for (size_t i = 0; i < matriz_num_filas(robot->mapa); i++) {
        for (size_t j = 0; j < matriz_num_columnas(robot->mapa); j++){
            if(i == (size_t)robot->pos->i && j == (size_t)robot->pos->j){
              fprintf(stderr, "R ");
            } else if (i == (size_t)robot->dest->i && j == (size_t)robot->dest->j){
              fprintf(stderr, "D ");
            } else {
              fprintf(stderr, "%c ", matriz_leer(robot->mapa, i, j));
            }
        }
        fprintf(stderr, "\n");
    }
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
