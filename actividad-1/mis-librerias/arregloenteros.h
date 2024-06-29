#ifndef ARREGLOENTEROS_H
#define ARREGLOENTEROS_H
#include "tipos.h"

typedef struct {
    int* direccion;
    int capacidad;
} ArregloEnteros;

/**
 * Retorna un arreglo de enteros vacio
 */
ArregloEnteros* arreglo_enteros_crear(size_t capacidad);

/**
 * Destruye el arreglo de enteros y sus datos
 */
void arreglo_enteros_destruir(ArregloEnteros* arreglo);

/**
 * Retorna el entero en la posicion pasada como argumento
 */
int arreglo_enteros_leer(ArregloEnteros* arreglo, size_t pos);

/**
 * Inserta un entero en una posicion dada
 */
void arreglo_enteros_escribir(ArregloEnteros* arreglo, size_t pos, int dato);

/**
 * Retorna la capacidad del arreglo de enteros
 */
int arreglo_enteros_capacidad(ArregloEnteros* arreglo);

/**
 * Imprime el arreglo de enteros
 */
void arreglo_enteros_imprimir(ArregloEnteros* arreglo);

/**
 * Ajusta la capacidad del arreglo de enteros
 */
void arreglo_enteros_ajustar(ArregloEnteros* arreglo, size_t capacidad);

/**
 * Inserta un dato en una posicion dada moviendo todos los elementos
 * desde esa posicion un lugar a la derecha
 */
void arreglo_enteros_insertar(ArregloEnteros* arreglo, size_t pos, int dato);

/**
 * Elimina un dato en una posicion dada moviendo todos los elementos
 * desde esa posicion un lugar a la izquierda
 */
void arreglo_enteros_eliminar(ArregloEnteros* arreglo, size_t pos);

#endif /* ARREGLOENTEROS_H */