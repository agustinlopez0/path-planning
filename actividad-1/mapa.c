#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

void mapa_imprimir(Mapa mapa) {
  printf("Mapa:\n");
  printf("\tDimensiones: %ldx%ld\n", mapa->alto, mapa->ancho);
  for (unsigned int i = 0; i < mapa->alto; i++) {
    printf("\t");
    for (unsigned int j = 0; j < mapa->ancho; j++)
      printf("%c ", mapa->coord[i][j]);
    printf("\n");
  }
}

void mapa_destruir(Mapa mapa) {
  for (unsigned int i = 0; i < mapa->alto; i++)
    free(mapa->coord[i]);
  free(mapa->coord);
  free(mapa);
}
