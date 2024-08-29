#ifndef __PILA_H__
#define __PILA_H__
#include "tipos.h"
#include "glist.h"

typedef GList Pila;

/**
 * Retorna una pila vacia
 */
Pila pila_crear(void);

/**
 * Destruye una pila y sus elementos
 */
void pila_destruir(Pila pila, FuncionDestructora destroy);

/**
 * Retorna 1 si la pila esta vacia, 0 en caso contrario
 */
int pila_es_vacia(Pila pila);

/**
 * Devuelve el tope de la pila
 */
void* pila_tope(Pila pila);

/**
 * Agrega un elemento a la pila
 */
Pila pila_apilar(Pila pila, void* dato, FuncionCopiadora copy);

/**
 * Elimina un elemento de la pila
 */
Pila pila_desapilar(Pila pila, FuncionDestructora destroy);

/**
 * Recorre la pila con la funcion pasada como argumento
 */
void pila_recorrer(Pila pila, FuncionVisitante visit);

#endif