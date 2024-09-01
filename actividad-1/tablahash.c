#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>

#define FACTOR_CARGA_UMBRAL 0.7

typedef struct {
  void *dato;
} CasillaHash;

struct _TablaHash {
  CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp,
                          FuncionDestructora destr, FuncionHash hash) {

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

  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].dato = NULL;
  }

  return tabla;
}

int tablahash_nelems(TablaHash tabla) {
  return tabla->numElems;
}

int tablahash_capacidad(TablaHash tabla) {
  return tabla->capacidad;
}

void tablahash_destruir(TablaHash tabla) {

  for (unsigned idx = 0; idx < tabla->capacidad; ++idx)
    if (tabla->elems[idx].dato != NULL)
      tabla->destr(tabla->elems[idx].dato);

  free(tabla->elems);
  free(tabla);
}

void tablahash_rehash(TablaHash tabla) {
  unsigned nueva_capacidad = tabla->capacidad * 2;
  CasillaHash *nuevas_casillas =
      malloc(sizeof(CasillaHash) * nueva_capacidad);
  assert(nuevas_casillas != NULL);

  for (unsigned idx = 0; idx < nueva_capacidad; ++idx) {
    nuevas_casillas[idx].dato = NULL;
  }

  CasillaHash *antiguas_casillas = tabla->elems;
  unsigned antigua_capacidad = tabla->capacidad;

  tabla->elems = nuevas_casillas;
  tabla->capacidad = nueva_capacidad;
  tabla->numElems = 0;

  for (unsigned idx = 0; idx < antigua_capacidad; ++idx) {
    if (antiguas_casillas[idx].dato != NULL) {
      tablahash_insertar(tabla, antiguas_casillas[idx].dato);
    }
  }

  free(antiguas_casillas);
}

void tablahash_insertar(TablaHash tabla, void *dato) {
  if ((double) tabla->numElems / tabla->capacidad > FACTOR_CARGA_UMBRAL) {
    tablahash_rehash(tabla);
  }

  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  unsigned original_idx = idx;

  while (tabla->elems[idx].dato != NULL) {
    if (tabla->comp(tabla->elems[idx].dato, dato) == 0) {
      tabla->destr(tabla->elems[idx].dato);
      tabla->elems[idx].dato = tabla->copia(dato);
      return;
    }

    idx = (idx + 1) % tabla->capacidad;

    if (idx == original_idx) {
      return;
    }
  }

  tabla->numElems++;
  tabla->elems[idx].dato = tabla->copia(dato);
}

void *tablahash_buscar(TablaHash tabla, void *dato) {
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  unsigned original_idx = idx;

  while (tabla->elems[idx].dato != NULL) {
    if (tabla->comp(tabla->elems[idx].dato, dato) == 0)
      return tabla->elems[idx].dato;

    idx = (idx + 1) % tabla->capacidad;

    if (idx == original_idx)
      break;
  }

  return NULL;
}