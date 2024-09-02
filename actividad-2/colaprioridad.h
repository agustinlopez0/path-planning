#ifndef __COLAPRIORIDAD_H__
#define __COLAPRIORIDAD_H__

#include "bheap.h"
#include "tipos.h"

/**
 * @file colaprioridad.h
 * @brief Definición y funciones relacionadas con la estructura ColaPrioridad.
 */

/**
 * @typedef BHeap ColaPrioridad
 * @brief Definición de una cola de prioridad a partir de un heap binario.
 */
typedef BHeap ColaPrioridad;

/**
 * @brief Crea una cola de prioridad vacía.
 * 
 * @param capacidad Capacidad inicial de la cola.
 * @param comp Funcion comparadora de los elementos de la cola.
 */
ColaPrioridad cola_prioridad_crear(size_t capacidad, 
  FuncionComparadora comp, FuncionDestructora destr);

/**
 * @brief Retorna 1 si la cola de prioridad esta vacia, 0 en caso contrario.
 * 
 * @param cola Cola de prioridad a verificar.
 * @return 1 si la cola de prioridad esta vacia, 0 en caso contrario.
 */
int cola_prioridad_es_vacia(ColaPrioridad cola);

/**
 * @brief Retorna el elemento prioritario de la cola.
 * 
 * @param cola Cola de prioridad de la que se quiere obtener el elemento prioritario.
 * @return Elemento prioritario de la cola.
 */
void* cola_prioridad_maximo(ColaPrioridad cola);

/**
 * @brief Elimina el elemento prioritario de la cola.
 * 
 * @param cola Cola de prioridad de la que se quiere eliminar el elemento prioritario.
 */
void cola_prioridad_eliminar_maximo(ColaPrioridad cola);

/**
 * @brief Inserta un elemento en la cola de prioridad.
 * 
 * @param cola Cola de prioridad donde se insertara el elemento.
 * @param elemento Elemento a insertar.
 */
void cola_prioridad_insertar(ColaPrioridad cola, void* elemento);

/**
 * @brief Destruye la cola de prioridad.
 * 
 * @param cola Cola de prioridad a destruir.
 */
void cola_prioridad_destruir(ColaPrioridad cola);

#endif /* __COLAPRIORIDAD_H__ */
