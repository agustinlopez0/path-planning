#ifndef __BHEAP_H__
#define __BHEAP_H__

#include <stdlib.h>
#include "tipos.h"

/**
 * @file bheap.h
 * @brief Definición y funciones relacionadas con la estructura BHeap.
 */

/**
 * @struct _BHeap
 * @brief Estructura de un heap binario.
 */
typedef struct _BHeap {
  void **arr;
  int capacidad;
  int ultimo;
  FuncionComparadora comp;
  FuncionDestructora destr;
} *BHeap;

/**
 * @brief Crea un heap binario vacio.
 * 
 * @param capacidad Capacidad inicial del heap.
 * @param comp Funcion comparadora de los elementos del heap.
 * @param destroy Funcion destructora de los elementos del heap.
 * @return Heap binario creado.
 */
BHeap bheap_crear(size_t capacidad, FuncionComparadora comp, FuncionDestructora destroy);

/**
 * @brief Destruye un heap binario.
 * 
 * @param heap Heap binario a destruir.
 */
void bheap_destruir(BHeap);

/**
 * @brief Retorna 1 si el heap esta vacio, 0 en caso contrario.
 * 
 * @param heap Heap binario a verificar.
 * @return 1 si el heap esta vacio, 0 en caso contrario.
 */
int bheap_es_vacio(BHeap);

/**
 * @brief Inserta un elemento en el heap binario.
 * 
 * @param heap Heap binario donde se insertara el elemento.
 * @param dato Elemento a insertar.
 */
void bheap_insertar(BHeap, void*);

/**
 * @brief Elimina un elemento del heap binario.
 * 
 * @param heap Heap binario donde se eliminara el elemento.
 * @param pos Posicion del elemento a eliminar.
 */
void bheap_eliminar(BHeap heap, size_t pos);


#endif /* __BHEAP_H__ */