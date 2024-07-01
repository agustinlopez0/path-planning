#ifndef __MAPA_H__
#define __MAPA_H__

#include "tipos.h"

typedef struct {
  char **coord;
  size_t ancho, alto;
} _Mapa;

typedef _Mapa *Mapa;

/**
 * Imprime los datos de la estructura mapa y dibuja el tablero.
 */
void mapa_imprimir(Mapa mapa);

/**
 * Destruye un mapa y libera la memoria que ocupaba.
 */
void mapa_destruir(Mapa mapa);

/**
 * Crea un mapa
 */
Mapa mapa_crear(size_t alto, size_t ancho, char** coord);

#endif // __MAPA_H__
