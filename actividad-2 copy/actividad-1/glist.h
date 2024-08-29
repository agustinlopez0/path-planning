#ifndef __GLIST_H__
#define __GLIST_H__

#include "tipos.h"

/**
 * @file glist.h
 * @brief Definición y funciones relacionadas con la estructura GList.
 */

typedef struct _GNode {
    void *data;
    struct _GNode *next;
} GNode;

typedef GNode *GList; 

/**
 * @brief Retorna una lista general vacía.
 *
 * @return GList Lista general vacía.
 */
GList glist_crear();

/**
 * @brief Destruye una lista general y sus datos utilizando la función pasada como argumento.
 *
 * @param lista Lista general que se va a destruir.
 * @param destruir Función que se utilizará para destruir los datos de cada nodo.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * @brief Retorna 1 si la lista está vacía, 0 en caso contrario.
 *
 * @param lista Lista general que se va a verificar.
 * @return int 1 si la lista está vacía, 0 si no lo está.
 */
int glist_vacia(GList lista);

/**
 * @brief Agrega un elemento al inicio de la lista.
 *
 * @param lista Lista general a la que se va a agregar el elemento.
 * @param dato Dato que se va a agregar.
 * @param copiar Función que se utilizará para copiar el dato.
 * @return GList Lista general con el elemento agregado al inicio.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopiadora copiar);

/**
 * @brief Agrega un elemento al final de la lista.
 *
 * @param lista Lista general a la que se va a agregar el elemento.
 * @param dato Dato que se va a agregar.
 * @param copy Función que se utilizará para copiar el dato.
 * @return GList Lista general con el elemento agregado al final.
 */
GList glist_agregar_final(GList lista, void *dato, FuncionCopiadora copy);

/**
 * @brief Recorre la lista aplicando la función de visitante a cada elemento.
 *
 * @param lista Lista general que se va a recorrer.
 * @param visitar Función que se aplicará a cada elemento de la lista.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

/**
 * @brief Retorna el primer elemento de la lista.
 *
 * @param lista Lista general de la que se quiere obtener el primer elemento.
 * @return void* Primer elemento de la lista.
 */
void* glist_primer_elemento(GList lista);

/**
 * @brief Elimina el último elemento de la lista.
 *
 * @param lista Lista general de la que se va a eliminar el último elemento.
 * @param destroy Función que se utilizará para destruir el dato del último nodo.
 * @return GList Lista general con el último elemento eliminado.
 */
GList glist_eliminar_final(GList lista, FuncionDestructora destroy);

/**
 * @brief Elimina el primer elemento de la lista.
 *
 * @param lista Lista general de la que se va a eliminar el primer elemento.
 * @param destroy Función que se utilizará para destruir el dato del primer nodo.
 * @return GList Lista general con el primer elemento eliminado.
 */
GList glist_eliminar_inicio(GList lista, FuncionDestructora destroy);

/**
 * @brief Busca si un dato está en la lista utilizando una función comparadora.
 *
 * @param lista Lista general en la que se va a buscar el dato.
 * @param dato Dato que se va a buscar.
 * @param comp Función que se utilizará para comparar el dato.
 * @return int 1 si el dato está en la lista, 0 si no lo está.
 */
int glist_include(GList lista, void *dato, FuncionComparadora comp);

#endif /* __GLIST_H__ */
