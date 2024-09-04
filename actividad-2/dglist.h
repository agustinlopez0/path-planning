#ifndef __GLIST_H__
#define __GLIST_H__

#include "tipos.h"

/**
 * @file ddglist.h
 * @brief Definición y funciones relacionadas con la estructura DGList.
 */

/**
 * @struct GNode
 * @brief Estructura de un nodo de una lista general simplemente enlazada con un puntero al inicio y otro al final.
 */
typedef struct _GNode {
    void *data;
    struct _GNode *next;
} GNode;

typedef struct {
    GNode *first;
    GNode *last;
} _DGList;

typedef _DGList *DGList;

/**
 * @brief Retorna una lista general vacía.
 *
 * @return DGList Lista general vacía.
 */
DGList dglist_crear(void);

/**
 * @brief Retorna 1 si la lista está vacía, 0 en caso contrario.
 *
 * @param list Lista general que se va a verificar.
 * @return int 1 si la lista está vacía, 0 si no lo está.
 */
int dglist_vacia(DGList list);

/**
 * @brief Agrega un elemento al inicio de la lista.
 *
 * @param list Lista general a la que se va a agregar el elemento.
 * @param data Dato que se va a agregar.
 * @param copy Función que se utilizará para copiar el dato.
 */
void dglist_agregar_inicio(DGList list, void *data, FuncionCopiadora copy);

/**
 * @brief Agrega un elemento al final de la lista.
 *
 * @param list Lista general a la que se va a agregar el elemento.
 * @param data Dato que se va a agregar.
 * @param copy Función que se utilizará para copiar el dato.
 */
void dglist_agregar_final(DGList list, void *data, FuncionCopiadora copy);

/**
 * @brief Recorre todos los elementos de la lista aplicando una función de visita.
 *
 * @param list Lista general que se va a recorrer.
 * @param visit Función que se aplicará a cada elemento de la lista.
 */
void dglist_recorrer(DGList list, FuncionVisitante visit);

/**
 * @brief Destruye una lista general y sus datos utilizando la función pasada como argumento.
 *
 * @param list Lista general que se va a destruir.
 * @param destruir Función que se utilizará para destruir los datos de cada nodo.
 */
void dglist_destruir(DGList list, FuncionDestructora destruir);

#endif /* __GLIST_H__ */
