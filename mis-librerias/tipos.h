#ifndef TIPOS_H
#define TIPOS_H
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionVisitante)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);
typedef int (*Predicado) (void *dato);

typedef enum {
  AVL_RECORRIDO_IN,  /** Inorden */
  AVL_RECORRIDO_PRE, /** Preorden */
  AVL_RECORRIDO_POST /** Postorden */
} AVLRecorrido;

#endif /* TIPOS_H */