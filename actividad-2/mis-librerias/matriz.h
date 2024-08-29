#ifndef __MATRIZ_H__
#define __MATRIZ_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct Matriz_ Matriz;

/*
** Crea una nueva matriz
*/
Matriz* matriz_crear(size_t numFilas, size_t numColumnas);

/*
** Destruye una matriz
*/
void matriz_destruir(Matriz* matriz);

/*
** Obtiene el dato guardado en la posición dada de la matriz
*/
double matriz_leer(Matriz* matriz, size_t fil, size_t col);

/*
** Modifica el dato guardado en la posición dada de la matriz
*/
void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val);

/*
** Obtiene número de filas de la matriz
*/
size_t matriz_num_filas(Matriz* matriz);

/*
** Obtiene número de columnas de la matriz
*/
size_t matriz_num_columnas(Matriz* matriz);

/**
 * Intercambia dos filas dadas
*/
void matriz_intercambiar_filas(Matriz* matriz, size_t fil1, size_t fil2);

/**
 * Agrega una nueva fila en una posición dada
*/
void matriz_insertar_fila(Matriz* matriz, Matriz* matriz_fila, size_t fil);

#endif /* __MATRIZ_H__ */
