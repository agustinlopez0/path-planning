#include "tipos2.h"
#include "direccion.h"
#include "funcioneslistas.h"
#include <stdio.h>
#include <unistd.h>

int usar_sensor(Robot robot) {
  // Si ya se ha marcado la posición actual con 's', no hacer nada
  if (matriz_leer(robot->mapa, robot->pos->i, robot->pos->j) == 's')
    return 0;
  // Si conozco lo que hay en las 4 direcciones no uso el sensor
  // PROVISORIO
  if (!((robot->pos->i + 1 < (int) matriz_num_filas(robot->mapa) &&
         matriz_leer(robot->mapa, robot->pos->i + 1, robot->pos->j) == '?')
        || (robot->pos->i > 0
            && matriz_leer(robot->mapa, robot->pos->i - 1,
                           robot->pos->j) == '?')
        || (robot->pos->j + 1 < (int) matriz_num_columnas(robot->mapa)
            && matriz_leer(robot->mapa, robot->pos->i,
                           robot->pos->j + 1) == '?') || (robot->pos->j > 0
                                                          &&
                                                          matriz_leer
                                                          (robot->mapa,
                                                           robot->pos->i,
                                                           robot->pos->j -
                                                           1) == '?')
      )) {
    return 0;
  }

  // Enviar la posición actual del robot para usar el sensor
  fprintf(stderr, "? %d %d\n", robot->pos->i, robot->pos->j);
  printf("? %d %d\n", robot->pos->i, robot->pos->j);
  fflush(stdout);

  int cambios = 0;


  // Marcar la posición actual como explorada
  matriz_escribir(robot->mapa, robot->pos->i, robot->pos->j, 's');
  fprintf(stderr, "BR1\n");

  int d1, d2, d3, d4;
  // Leer las distancias desde el sensor
  scanf("%d %d %d %d", &d1, &d2, &d3, &d4);
  fprintf(stderr, "usar_sensor (%d, %d) ", robot->pos->i, robot->pos->j);
  fprintf(stderr, "%d %d %d %d:", d1, d2, d3, d4);
  fprintf(stderr, "BR2\n");

  size_t num_filas = matriz_num_filas(robot->mapa);
  size_t num_columnas = matriz_num_columnas(robot->mapa);
  fprintf(stderr, "BR3\n");

  // Actualizar posiciones hacia arriba
  if (d1 > 1) {
    for (int i = 1; i < d1; i++) {
      if ((robot->pos->i - i) >= 0) {
        if (matriz_leer(robot->mapa, robot->pos->i - i, robot->pos->j) ==
            '?') {
          cambios++;
          matriz_escribir(robot->mapa, robot->pos->i - i, robot->pos->j,
                          '.');
        }
      }
    }
  }
  fprintf(stderr, "BR4\n");

  if (d1 <= robot->sensor && (robot->pos->i - d1) >= 0) {
    matriz_escribir(robot->mapa, robot->pos->i - d1, robot->pos->j, '#');
  }
  // Actualizar posiciones hacia abajo
  fprintf(stderr, "BR5\n");
  if (d2 > 1) {
    for (int i = 1; i < d2; i++) {
      if ((size_t) (robot->pos->i + i) < num_filas) {
        if (matriz_leer(robot->mapa, robot->pos->i + i, robot->pos->j) ==
            '?') {
          cambios++;
          matriz_escribir(robot->mapa, robot->pos->i + i, robot->pos->j,
                          '.');
        }
      }
    }
  }
  if (d2 <= robot->sensor && (size_t) (robot->pos->i + d2) < num_filas) {
    matriz_escribir(robot->mapa, robot->pos->i + d2, robot->pos->j, '#');
  }
  fprintf(stderr, "BR6\n");

  // Actualizar posiciones hacia la izquierda
  if (d3 > 1) {
    for (int i = 1; i < d3; i++) {
      if ((robot->pos->j - i) >= 0) {
        if (matriz_leer(robot->mapa, robot->pos->i, robot->pos->j - i) ==
            '?') {
          cambios++;
          matriz_escribir(robot->mapa, robot->pos->i, robot->pos->j - i,
                          '.');
        }
      }
    }
  }
  fprintf(stderr, "BR7\n");

  if (d3 <= robot->sensor && (robot->pos->j - d3) >= 0) {
    matriz_escribir(robot->mapa, robot->pos->i, robot->pos->j - d3, '#');
  }
  // Actualizar posiciones hacia la derecha
  if (d4 > 1) {
    for (int i = 1; i < d4; i++) {
      if ((size_t) (robot->pos->j + i) < num_columnas) {
        if (matriz_leer(robot->mapa, robot->pos->i, robot->pos->j + i) ==
            '?') {
          cambios++;
          matriz_escribir(robot->mapa, robot->pos->i, robot->pos->j + i,
                          '.');
        }
      }
    }
  }

  if (d4 <= robot->sensor && (size_t) (robot->pos->j + d4) < num_columnas) {
    matriz_escribir(robot->mapa, robot->pos->i, robot->pos->j + d4, '#');
  }
  // Imprimir el mapa actualizado
  imprimir_mapa(robot);
  return cambios;
}


int robot_en_destino(Robot robot) {
  return punto_comparar(robot->pos, robot->dest) == 0;
}

void robot_set_mapa(Robot robot) {
  int n = (int) matriz_num_filas(robot->mapa);
  int m = (int) matriz_num_columnas(robot->mapa);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      matriz_escribir(robot->mapa, i, j, '?');
}


void imprimir_mapa(Robot robot) {
  fprintf(stderr, "\n-------------------\n");
  for (size_t i = 0; i < matriz_num_filas(robot->mapa); i++) {
    for (size_t j = 0; j < matriz_num_columnas(robot->mapa); j++) {
      if (i == (size_t) robot->pos->i && j == (size_t) robot->pos->j) {
        fprintf(stderr, "R ");
      } else if (i == (size_t) robot->dest->i
                 && j == (size_t) robot->dest->j) {
        fprintf(stderr, "D ");
      } else {
        fprintf(stderr, "%c ", matriz_leer(robot->mapa, i, j));
      }
    }
    fprintf(stderr, " |\n");
  }
  fprintf(stderr, "-------------------\n");

  usleep(500000);

}

int robot_retroceder(Robot robot) {
  if (pila_es_vacia(robot->movimientos))
    return 0;

  // Obtener la última dirección desde la pila
  Direccion *ultima_direccion = pila_tope(robot->movimientos);

  if (matriz_leer(robot->mapa, robot->pos->i, robot->pos->j) == '.')
    matriz_escribir(robot->mapa, robot->pos->i, robot->pos->j, '-');

  // Mover el robot en la dirección opuesta
  switch (*ultima_direccion) {
  case UP:
    robot->pos->i++;
    break;
  case DOWN:
    robot->pos->i--;
    break;
  case LEFT:
    robot->pos->j++;
    break;
  case RIGHT:
    robot->pos->j--;
    break;
  }

  robot->movimientos =
      pila_desapilar(robot->movimientos,
                     (FuncionDestructora) direccion_destruir);

  fprintf(stderr, "\nrobot_retroceder:");
  imprimir_mapa(robot);
  return 1;
}
