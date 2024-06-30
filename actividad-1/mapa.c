#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

void mapa_imprimir(Mapa mapa) {
  printf("Mapa:\n");
  printf("\tDimensiones: %dx%d\n", mapa->alto, mapa->ancho);
  for (int i = 0; i < mapa->alto; i++) {
    printf("\t");
    for (int j = 0; j < mapa->ancho; j++)
      printf("%c ", mapa->coord[i][j]);
    printf("\n");
  }
}

void mapa_destruir(Mapa mapa) {
  for (int i = 0; i < mapa->alto; i++)
    free(mapa->coord[i]);
  free(mapa->coord);
}
