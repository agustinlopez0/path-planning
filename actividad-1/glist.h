#ifndef __GLIST_H__
#define __GLIST_H__
#include "tipos.h"

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

/**
 * Retorna una lista general vacia
 */
GList glist_crear();

/**
 * Destruye una lista general y sus datos con la funcion 
 * pasada como argumento
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * Retorna 1 si la lista esta vacia, 0 en caso contrario
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al inicio de la lista
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopiadora copiar);

/**
 * Agrega un elemento al final de la lista
 */
GList glist_agregar_final(GList list, void *data, FuncionCopiadora copy);

/**
 * Recorre la lista con la funcion pasada como argumento
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

/**
 * Devuelve una lista con los elementos que cumplen el predicado
 */
GList glist_filtrar(GList lista, FuncionCopiadora c, Predicado p);

/**
 * Retorna el primer elemento de la lista
 */
void* glist_primer_elemento(GList list);

/**
 * Elimina el ultimo elemento de la lista
 */
GList glist_eliminar_final(GList lista, FuncionDestructora destroy);

/**
 * Elimina el primer elemento de la lista
 */
GList glist_eliminar_inicio(GList lista, FuncionDestructora destroy);

/**
 * Retorna 1 si el dato esta en la lista, 0 en caso contrario.
 */
int glist_include(GList lista, void * dato, FuncionComparadora comp);

#endif /* __GLIST_H__ */
