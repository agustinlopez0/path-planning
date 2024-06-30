#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "simulacion.h"

int validar_formato(FILE * f, size_t *alto, size_t *ancho, int *dummy,
                    Punto * robotPos, Punto * robotDest) {
  // Validar la primera línea
  if (fscanf(f, "%ld %ld %d", alto, ancho, dummy) != 3) {
    fprintf(stderr, "Formato de archivo inválido en la primera línea\n");
    return 1;
  }
  // Validar la segunda línea
  if (fscanf(f, "%d %d", &robotPos->i, &robotPos->j) != 2) {
    fprintf(stderr, "Formato de archivo inválido en la segunda línea\n");
    return 1;
  }
  // Validar la tercera línea
  if (fscanf(f, "%d %d", &robotDest->i, &robotDest->j) != 2) {
    fprintf(stderr, "Formato de archivo inválido en la tercera línea\n");
    return 1;
  }

  return 0;
}

int leer_archivo(const char *nombre_archivo, Mapa mapa, Punto * robotPos,
                 Punto * robotDest) {
  FILE *f = fopen(nombre_archivo, "r");
  if (f == NULL) {
    fprintf(stderr, "No se pudo abrir el archivo %s\n", nombre_archivo);
    return 1;
  }

  int dummy;
  if (validar_formato
      (f, &mapa->alto, &mapa->ancho, &dummy, robotPos, robotDest) != 0) {
    fclose(f);
    return 1;
  }

  mapa->coord = malloc(sizeof(char *) * mapa->alto);
  for (unsigned int i = 0; i < mapa->alto; i++) {
    mapa->coord[i] = malloc(sizeof(char) * (mapa->ancho + 1));
    assert(mapa->coord[i] != NULL);

    if (fscanf(f, "%s", mapa->coord[i]) != 1) {
      fprintf(stderr, "Formato de archivo inválido en la línea %d\n",
              i + 4);
      mapa_destruir(mapa);
      fclose(f);
      return 1;
    }

    if (strlen(mapa->coord[i]) != mapa->ancho) {
      fprintf(stderr, "Longitud de fila incorrecta en la línea %d\n",
              i + 4);
      mapa_destruir(mapa);
      fclose(f);
      return 1;
    }
  }

  fclose(f);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Uso: %s <archivo de entrada>\n", argv[0]);
    return 1;
  }

  printf("Abriendo archivo: %s\n", argv[1]);

  Mapa mapa = malloc(sizeof(_Mapa));
  Punto robotPos, robotDest;

  if (leer_archivo(argv[1], mapa, &robotPos, &robotDest) != 0) {
    return 1;
  }

  Robot robot = robot_crear(robotPos, robotDest);
  if (!robot) {
    mapa_destruir(mapa);
    return 1;
  }

  mostrar_robot_mapa(robot, mapa);


  puts("Recorrido:");
  robot_ir_a_destino(robot, mapa);
  puts("");
  mapa_destruir(mapa);
  robot_destruir(robot);


  return 0;
}
