#ifndef MAPA_H
#define MAPA_H

#include "tipos.h"

typedef enum {
  LEFT,
  RIGHT,
  UP,
  DOWN
} Direccion;

typedef struct {
  int i, j;
} Punto;


typedef struct {
  char **coord;
  int ancho, alto;
} _Mapa;

typedef _Mapa *Mapa;

/**
 * Imprime los datos de la estructura mapa y dibuja el tablero.
 */
void mapa_imprimir(Mapa mapa);

/**
 * Devuelve 0 si los puntos son iguales, cualquier otro valor si son distintos
 */
int punto_comparar(Punto a, Punto b);
int punto_compararp(Punto * a, Punto * b);

/**
 * Realiza una copia fisica de un punto.
 */
Punto *punto_copiar(Punto * a);

/**
 * Retorna 0 si estan alineados respecto al eje x.
 * Un valor positivo si b esta a la izquierda de a
 * Un valor negativo si b esta a la derecha de a
 */
int punto_distancia_x(Punto a, Punto b);

/**
 * Retorna 0 si estan alineados respecto al eje y.
 * Un valor positivo si b esta arriba de a
 * Un valor negativo si a esta arriba de b
 */
int punto_distancia_y(Punto a, Punto b);

/**
 * Destruye una direccion y libera la memoria.
 */
void direccion_destruir(Direccion * a);

/**
 * Realiza una copia fisica de una dirección.
 */
Direccion *direccion_copiar(Direccion * a);

/**
 * Imprime un punto
 */
void punto_imprimir(Punto * punto);

/**
 * Imprime una dirección.
 */
void direccion_imprimir(Direccion * direccion);

/**
 * Dada una dirección retorna su opuesta.
 */
Direccion direccion_opuesta(Direccion direccion);

/**
 * Destruye un mapa y libera la memoria que ocupaba.
 */
void mapa_destruir(Mapa mapa);

// Mapa mapa_crear(int alto, int ancho);

#endif // MAPA_H
