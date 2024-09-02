#include "colaprioridad.h"

ColaPrioridad cola_prioridad_crear(size_t capacidad,
                                   FuncionComparadora comp,
                                   FuncionDestructora destr) {
  return bheap_crear(capacidad, comp, destr);
}

int cola_prioridad_es_vacia(ColaPrioridad cola) {
  return bheap_es_vacio(cola);
}

void *cola_prioridad_maximo(ColaPrioridad cola) {
  return cola->arr[1];
}

void cola_prioridad_eliminar_maximo(ColaPrioridad cola) {
  bheap_eliminar(cola, 1);
}

void cola_prioridad_insertar(ColaPrioridad cola, void *elemento) {
  bheap_insertar(cola, elemento);
}

void cola_prioridad_destruir(ColaPrioridad cola) {
  bheap_destruir(cola);
}
