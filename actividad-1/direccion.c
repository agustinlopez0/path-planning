#include <stdio.h>
#include <stdlib.h>
#include "direccion.h"

Direccion *direccion_copiar(Direccion *a) {
  Direccion *copia = malloc(sizeof(Direccion));
  *copia = *a;
  return copia;
}

void direccion_imprimir(Direccion *direccion) {
  if (*direccion == UP)
    printf("U");
  else if (*direccion == DOWN)
    printf("D");
  else if (*direccion == LEFT)
    printf("L");
  else if (*direccion == RIGHT)
    printf("R");
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

void direccion_destruir(Direccion *a) {
  free(a);
}
