
#include "mapa.h"

void mapa_imprimir(Mapa mapa) {
  printf("Mapa:\n");
  printf("\tDimensiones: %dx%d\n", mapa->alto, mapa->ancho);
  for (int i = 0; i < mapa->alto; i++) {
    printf("\t");
    for (int j = 0; j < mapa->ancho; j++)
      printf("%c", mapa->coord[i][j]);
    printf("\n");
  }
}

int punto_comparar(Punto a, Punto b) {
  return !(a.i == b.i && a.j == b.j);
}

int punto_compararp(Punto * a, Punto * b) {
  return !(a->i == b->i && a->j == b->j);
}

Punto *punto_copiar(Punto * a) {
  Punto *nuevoPunto = malloc(sizeof(Punto));
  *nuevoPunto = *a;
  return nuevoPunto;
}

int punto_distancia_x(Punto a, Punto b) {
  return a.j - b.j;
}

int punto_distancia_y(Punto a, Punto b) {
  return a.i - b.i;
}

void direccion_destruir(Direccion * a) {
  free(a);
}

Direccion *direccion_copiar(Direccion * a) {
  Direccion *copia = malloc(sizeof(Direccion));
  *copia = *a;
  return copia;
}

void punto_imprimir(Punto * punto) {
  printf("(%d, %d) ", punto->i, punto->j);
}

void direccion_imprimir(Direccion * direccion) {
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

void mapa_destruir(Mapa mapa) {
  for (int i = 0; i < mapa->alto; i++)
    free(mapa->coord[i]);
  free(mapa->coord);
}