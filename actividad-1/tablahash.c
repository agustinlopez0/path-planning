#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void *dato;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].dato = NULL;
  }

  return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx)
    if (tabla->elems[idx].dato != NULL)
      tabla->destr(tabla->elems[idx].dato);

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 * Maneja colisiones utilizando linear probing.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {
  // Calculamos la posicion inicial del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  unsigned original_idx = idx;

  while (tabla->elems[idx].dato != NULL) {
    // Sobrescribir el dato si el mismo ya se encontraba en la tabla.
    if (tabla->comp(tabla->elems[idx].dato, dato) == 0) {
      tabla->destr(tabla->elems[idx].dato);
      tabla->elems[idx].dato = tabla->copia(dato);
      return;
    }

    // Avanzar a la siguiente posición en caso de colisión.
    idx = (idx + 1) % tabla->capacidad;

    // Si hemos recorrido toda la tabla, terminamos la búsqueda.
    if (idx == original_idx) {
      return;
    }
  }

  // Insertar el dato si encontramos una casilla libre.
  tabla->numElems++;
  tabla->elems[idx].dato = tabla->copia(dato);
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {
  // Calculamos la posicion inicial del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  unsigned original_idx = idx;

  // Realizamos una búsqueda hasta encontrar el dato o una casilla vacía.
  while (tabla->elems[idx].dato != NULL) {
    // Retornar el dato si se encuentra una coincidencia.
    if (tabla->comp(tabla->elems[idx].dato, dato) == 0)
      return tabla->elems[idx].dato;

    // Avanzar a la siguiente posición en caso de colisión.
    idx = (idx + 1) % tabla->capacidad;

    // Si hemos recorrido toda la tabla, terminamos la búsqueda.
    if (idx == original_idx)
      break;  // El dato no está en la tabla.
  }

  // Retornar NULL si no se encuentra el dato.
  return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return;
  // Vaciar la casilla si hay coincidencia.
  else if (tabla->comp(tabla->elems[idx].dato, dato) == 0) {
    tabla->numElems--;
    tabla->destr(tabla->elems[idx].dato);
    tabla->elems[idx].dato = NULL;
    return;
  }
}
