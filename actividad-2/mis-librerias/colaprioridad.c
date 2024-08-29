#include "colaprioridad.h"

int cola_prioridad_es_vacia(ColaPrioridad cola){
  return bheap_es_vacio(cola);
}

void* cola_prioridad_maximo(ColaPrioridad cola){
  return cola->arr[1];
}

void cola_prioridad_eliminar_maximo(ColaPrioridad cola){
  bheap_eliminar(cola, 1);
}

void cola_prioridad_insertar(ColaPrioridad cola, void *elemento){
  bheap_insertar(cola, elemento);
}

void cola_prioridad_destruir(ColaPrioridad cola){
  bheap_destruir(cola);
}

ColaPrioridad cola_prioridad_crear(size_t capacidad, 
  FuncionComparadora comp, FuncionDestructora destr){
  return bheap_crear(capacidad, comp, destr);
}

void cola_prioridad_recorrer(ColaPrioridad cola, FuncionVisitante visit){
  bheap_recorrer(cola, visit);
}

ColaPrioridad cola_prioridad_crear_desde_arr(void** arr, int len, 
  FuncionCopiadora copy, FuncionDestructora destr, FuncionComparadora comp){
  return bheap_crear_desde_arr(arr, len, copy, destr, comp);
}
