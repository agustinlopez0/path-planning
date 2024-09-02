#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__
#include "tipos.h"

typedef struct _TablaHash *TablaHash;

TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash);

int tablahash_nelems(TablaHash tabla);

int tablahash_capacidad(TablaHash tabla);

void tablahash_destruir(TablaHash tabla);

void tablahash_insertar(TablaHash tabla, void *dato);

void *tablahash_buscar(TablaHash tabla, void *dato);


void tablahash_rehash(TablaHash tabla);

#endif /* __TABLAHASH_H__ */
