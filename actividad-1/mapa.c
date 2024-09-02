#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

Mapa mapa_crear(size_t alto, size_t ancho, char **coord) {
  if (coord == NULL || alto <= 0 || ancho <= 0) {
    fprintf(stderr, "Error: parámetros inválidos para crear el mapa.\n");
    return NULL;
  }

  Mapa nuevoMapa = malloc(sizeof(_Mapa));
  nuevoMapa->coord = coord;
  nuevoMapa->alto = alto;
  nuevoMapa->ancho = ancho;
  return nuevoMapa;
}

void mapa_destruir(Mapa mapa) {
  for (unsigned int i = 0; i < mapa->alto; i++)
    free(mapa->coord[i]);
  free(mapa->coord);
  free(mapa);
}
