#ifndef __COLAPRIORIDAD_H__
#define __COLAPRIORIDAD_H__
#include "tipos.h"
#include "bheap.h"

typedef BHeap ColaPrioridad;

/**
 * Retorna 1 si la cola esta vacia, 0 en caso contrario
 */
int cola_prioridad_es_vacia(ColaPrioridad cola);

/**
 * Retorna el elemento prioritario de la cola
 */
void* cola_prioridad_maximo(ColaPrioridad cola);

/**
 * Elimina el elemento prioritario de la cola
 */
void cola_prioridad_eliminar_maximo(ColaPrioridad cola);

/**
 * Inserta un elemento en la cola con una determinada prioridad
 */
void cola_prioridad_insertar(ColaPrioridad cola, void* elemento);

/**
 * Destruye la cola de prioridad y sus elementos
 */
void cola_prioridad_destruir(ColaPrioridad cola);

/**
 * Crea una cola de prioridad vacia
 */
ColaPrioridad cola_prioridad_crear(size_t capacidad, 
  FuncionComparadora comp, FuncionDestructora destr);

/**
 * Recorre la cola de prioridad con la funcion pasada como argumento
 */
void cola_prioridad_recorrer(ColaPrioridad cola, FuncionVisitante visit);

/**
 * A partir de un arreglo arbitrario crea un heap binario.
*/
ColaPrioridad cola_prioridad_crear_desde_arr(void** arr, int len, 
  FuncionCopiadora copy, FuncionDestructora destr, FuncionComparadora comp);
  
#endif /* __COLAPRIORIDAD_H__ */
