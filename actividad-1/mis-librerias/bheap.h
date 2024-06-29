#ifndef __BHEAP_H__
#define __BHEAP_H__
#include "tipos.h"


typedef struct _BHeap {
  void **arr;
  int capacidad;
  int ultimo;
  FuncionComparadora comp;
  FuncionDestructora destr;
} *BHeap;

/**
 * Crea un heap vacio con una capacidad y una funcion
 * de comparacion dadas
*/
BHeap bheap_crear(size_t, FuncionComparadora, FuncionDestructora);

/**
 * Destruye un heap
*/
void bheap_destruir(BHeap);

/**
 * Retorna 1 si el heap esta vacio y 0 en caso contrario
*/
int bheap_es_vacio(BHeap);

/**
 * Recorre los nodos utilizando busqueda por extension
 * aplicando la funcion en cada elemento
*/
void bheap_recorrer(BHeap, FuncionVisitante);

/**
 * Agrega un elemento al heap
*/
void bheap_insertar(BHeap, void*);

/**
 * Elimina un elemento del heap
*/
void bheap_eliminar(BHeap heap, size_t pos);

/**
 * A partir de un arreglo arbitrario crea un heap binario.
*/
BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionCopiadora copiar,
  FuncionDestructora destr, FuncionComparadora comp);


#endif /* __BHEAP_H__ */