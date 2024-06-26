#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

#define MAX 100
#define INF INT_MAX

typedef struct {
  int i, j;
} Point;

typedef enum {
  LEFT,
  RIGHT,
  UP,
  DOWN
} Direccion;

typedef struct {
  Point pos;
  Point dest;
} _Robot;

typedef _Robot *Robot;

typedef struct {
  char **coord;
  int ancho, alto;
} _Mapa;

typedef _Mapa *Mapa;

/**
 * Si el robot se puede mover en la direccion dada actualiza la posicion del robot
 * y devuelve 1, en caso contrario devuelve 0
 */
int robot_mover(Robot robot, Mapa mapa, Direccion direccion) {
  if (direccion == UP) {
    if (robot->pos.i - 1 >= 0
        && mapa->coord[robot->pos.i - 1][robot->pos.j] != '#') {
      robot->pos.i--;
      printf("U");
      return 1;
    }
  } else if (direccion == DOWN) {
    if (robot->pos.i + 1 < mapa->alto
        && mapa->coord[robot->pos.i + 1][robot->pos.j] != '#') {
      robot->pos.i++;
      printf("D");
      return 1;
    }
  } else if (direccion == LEFT) {
    if (robot->pos.j - 1 >= 0
        && mapa->coord[robot->pos.i][robot->pos.j - 1] != '#') {
      robot->pos.j--;
      printf("L");
      return 1;
    }
  } else if (direccion == RIGHT) {
    if (robot->pos.j + 1 < mapa->ancho - 1
        && mapa->coord[robot->pos.i][robot->pos.j + 1] != '#') {
      robot->pos.j++;
      printf("R");
      return 1;

    }
  }

  return 0;
}

void robot_destruir(Robot robot) {
  free(robot);
}

void mapa_destruir(Mapa mapa) {
  for (int i = 0; i < mapa->alto; i++) {
    free(mapa->coord[i]);
  }
  free(mapa->coord);
}

void robot_imprimir(Robot robot) {
  printf("robot->pos.i = %d, robot->pos.j = %d\n", robot->pos.i, robot->pos.j);
  printf("robot->dest.i = %d, robot->dest.j = %d\n", robot->dest.i,
         robot->dest.j);
}

void mapa_imprimir(Mapa mapa) {
  printf("N = %d, M = %d\n", mapa->alto, mapa->ancho);

  for (int i = 0; i < mapa->alto; i++) {
    for (int j = 0; j < mapa->ancho; j++) {
      printf("%c", mapa->coord[i][j]);
    }
    printf("\n");
  }
}

void robot_ir_a_destino(Robot robot, Mapa mapa) {

}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Uso: %s <nombre_archivo>\n", argv[0]);
    return 1;
  }

  /*Abre el archivo e inicializa mapa y robot con los datos */
  printf("Abriendo archivo: %s\n", argv[1]);
  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[1]);
    return 1;
  }

  Mapa mapa = malloc(sizeof(_Mapa));
  Robot robot = malloc(sizeof(_Robot));

  int dummy;
  fscanf(f, "%d %d %d", &mapa->alto, &mapa->ancho, &dummy);
  fscanf(f, "%d %d", &robot->pos.i, &robot->pos.j);
  fscanf(f, "%d %d", &robot->dest.i, &robot->dest.j);

  mapa->coord = malloc(sizeof(char *) * mapa->alto);
  for (int i = 0; i < mapa->alto; i++) {
    mapa->coord[i] = malloc(sizeof(char) * (mapa->ancho + 1));
    fscanf(f, "%s", mapa->coord[i]);
  }

  fclose(f);
  /*Una vez cargados los datos cierra el archivo */


  puts("");

  robot_imprimir(robot);
  mapa_imprimir(mapa);

  puts("");
  mapa_destruir(mapa);
  robot_destruir(robot);


  return 0;
}
