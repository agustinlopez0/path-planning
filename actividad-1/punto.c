#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "punto.h"

Punto punto_crear(int i, int j) {
  Punto nuevoPunto = malloc(sizeof(_Punto));
  assert(nuevoPunto != NULL);
  nuevoPunto->i = i;
  nuevoPunto->j = j;
  return nuevoPunto;
}

unsigned punto_hash(Punto punto) {
  return (punto->i * 73856093) + (punto->j * 19349663);
}

int punto_comparar(Punto a, Punto b) {
  return !(a->i == b->i && a->j == b->j);
}

Punto punto_copiar(Punto a) {
  Punto nuevoPunto = punto_crear(a->i, a->j);
  return nuevoPunto;
}

int punto_distancia_x(Punto a, Punto b) {
  return a->j - b->j;
}

int punto_distancia_y(Punto a, Punto b) {
  return a->i - b->i;
}

void punto_destruir(Punto punto) {
  free(punto);
}
