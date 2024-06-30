#include <stdio.h>
#include <stdlib.h>
#include "punto.h"

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

void punto_imprimir(Punto * punto) {
  printf("(%d, %d) ", punto->i, punto->j);
}
