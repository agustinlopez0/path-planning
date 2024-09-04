#include "robotAux.h"
#include <stdio.h>

// Setea los valores iniciales del mapa de un robot
void robot_set_mapa(Robot robot) {
  size_t n = mapa_num_filas(robot->mapa);
  size_t m = mapa_num_columnas(robot->mapa);
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++)
      mapa_escribir(robot->mapa, i, j, '?');
  mapa_escribir(robot->mapa, robot->pos->x, robot->pos->y, '.');
  mapa_escribir(robot->mapa, robot->dest->x, robot->dest->y, '.');
}
Robot robot_crear(Punto pos, Punto dest, int N, int M) {
  Robot robot = malloc(sizeof(_Robot));
  robot->pos = malloc(sizeof(Punto));
  robot->pos->x = pos.x;
  robot->pos->y = pos.y;

  robot->dest = malloc(sizeof(Punto));
  robot->dest->x = dest.x;
  robot->dest->y = dest.y;

  robot->camino = dglist_crear();

  robot->mapa = mapa_crear(N, M);
  robot_set_mapa(robot);

  return robot;
}

// Retorna el máximo de un arreglo de 4 enteros
int sensor_max(int *arr) {
  int max = arr[0];
  for (int i = 1; i < 4; i++)
    if (arr[i] > max)
      max = arr[i];
  return max;
}
int usar_sensor(Robot robot) {
  // Enviar la posición actual del robot para usar el sensor
  printf("? %d %d\n", robot->pos->x, robot->pos->y);
  fflush(stdout);

  int cambios = 0;
  int distancias[4];

  scanf("%d %d %d %d", &distancias[0], &distancias[1], &distancias[2], &distancias[3]);

  size_t num_filas = mapa_num_filas(robot->mapa);
  size_t num_columnas = mapa_num_columnas(robot->mapa);

  int dx[4] = { -1, 1, 0, 0 };
  int dy[4] = { 0, 0, -1, 1 };
  char marca = '.';
  char obstaculo = '#';

  for (int i = 0; i < 4; i++) {
    int d = distancias[i];

    // Actualizar posiciones en la dirección correspondiente
    for (int j = 1; j < d; j++) {
      int nuevo_x = robot->pos->x + j * dx[i];
      int nuevo_y = robot->pos->y + j * dy[i];

      if (nuevo_x >= 0 && (size_t) nuevo_x < num_filas && nuevo_y >= 0 && (size_t) nuevo_y < num_columnas) {
        if (mapa_leer(robot->mapa, nuevo_x, nuevo_y) == '?') {
          cambios++;
          mapa_escribir(robot->mapa, nuevo_x, nuevo_y, marca);
        }
      }
    }

    // Marcar el obstáculo si está dentro del rango del sensor
    if (d < sensor_max(distancias)) {
      int obstaculo_x = robot->pos->x + d * dx[i];
      int obstaculo_y = robot->pos->y + d * dy[i];

      if (obstaculo_x >= 0 && (size_t) obstaculo_x < num_filas
          && obstaculo_y >= 0 && (size_t) obstaculo_y < num_columnas) {
        mapa_escribir(robot->mapa, obstaculo_x, obstaculo_y, obstaculo);
      }
    }
  }

  return cambios;
}

void robot_destruir(Robot robot) {
  free(robot->pos);
  free(robot->dest);
  dglist_destruir(robot->camino, free);
  mapa_destruir(robot->mapa);
  free(robot);
}
