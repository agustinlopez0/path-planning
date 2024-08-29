#include <stdio.h>
#include <stdlib.h>
#include "direccion.h"

void direccion_destruir(Direccion * a) {
  free(a);
}

Direccion *direccion_copiar(Direccion * a) {
  Direccion *copia = malloc(sizeof(Direccion));
  *copia = *a;
  return copia;
}

void direccion_imprimir(Direccion * direccion) {
  if (*direccion == UP)
    fprintf(stderr, "U");
  else if (*direccion == DOWN)
    fprintf(stderr, "D");
  else if (*direccion == LEFT)
    fprintf(stderr, "L");
  else if (*direccion == RIGHT)
    fprintf(stderr, "R");
}

Direccion direccion_opuesta(Direccion direccion) {
  if (direccion == UP)
    return DOWN;
  if (direccion == DOWN)
    return UP;
  if (direccion == RIGHT)
    return LEFT;
  return RIGHT;
}
