#include "mapa.h"
#include <stdio.h>

struct Mapa_ {
  char **elem;
  size_t fil, col;
};


Mapa *mapa_crear(size_t numFilas, size_t numColumnas) {
  Mapa *mapa = malloc(sizeof(Mapa));
  mapa->fil = numFilas;
  mapa->col = numColumnas;
  mapa->elem = malloc(sizeof(char *) * numFilas);

  for (unsigned int i = 0; i < numFilas; i++)
    mapa->elem[i] = malloc(sizeof(char) * numColumnas);


  return mapa;
}

size_t mapa_num_filas(Mapa * mapa) {
  return mapa->fil;
}

size_t mapa_num_columnas(Mapa * mapa) {
  return mapa->col;
}

void mapa_destruir(Mapa * mapa) {
  if (mapa) {
    if (mapa->elem) {
      for (size_t i = 0; i < mapa_num_filas(mapa); i++)
        free(mapa->elem[i]);

      free(mapa->elem);
    }
    free(mapa);
  }
}


char mapa_leer(Mapa * mapa, size_t fil, size_t col) {
  if (fil >= mapa_num_filas(mapa) || col >= mapa_num_columnas(mapa))
    return 0;

  return mapa->elem[fil][col];
}

void mapa_escribir(Mapa * mapa, size_t fil, size_t col, char val) {
  if (fil < mapa_num_filas(mapa) || col < mapa_num_columnas(mapa))
    mapa->elem[fil][col] = val;
}
