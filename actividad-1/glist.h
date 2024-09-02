#ifndef __GLIST_H__
#define __GLIST_H__

#include "tipos.h"

/**
 * @file glist.h
 * @brief Definición y funciones relacionadas con la estructura GList.
 */

/**
 * @struct GList
 * @brief Estructura de un nodo de una lista general simplemente enlazada.
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
GList glist_crear(void);

/**
 * @brief Retorna 1 si la lista está vacía, 0 en caso contrario.
 *
 * @param list Lista general que se va a verificar.
 * @return int 1 si la lista está vacía, 0 si no lo está.
 */
int glist_vacia(GList list);

/**
 * @brief Agrega un elemento al inicio de la lista.
 *
 * @param list Lista general a la que se va a agregar el elemento.
 * @param data Dato que se va a agregar.
 * @param copy Función que se utilizará para copiar el dato.
 * @return GList Lista general con el elemento agregado al inicio.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopiadora copy);

/**
 * @brief Agrega un elemento al final de la lista.
 *
 * @param list Lista general a la que se va a agregar el elemento.
 * @param data Dato que se va a agregar.
 * @param copy Función que se utilizará para copiar el dato.
 * @return GList Lista general con el elemento agregado al final.
 */
GList glist_agregar_final(GList list, void *data, FuncionCopiadora copy);

/**
 * @brief Recorre todos los elementos de la lista aplicando una función de visita.
 *
 * @param list Lista general que se va a recorrer.
 * @param visit Función que se aplicará a cada elemento de la lista.
 */
void glist_recorrer(GList list, FuncionVisitante visit);

/**
 * @brief Retorna el primer elemento de la lista.
 *
 * @param list Lista general de la que se quiere obtener el primer elemento.
 * @return void* Primer elemento de la lista.
 */
void* glist_primer_elemento(GList list);

/**
 * @brief Elimina el primer elemento de la lista.
 *
 * @param list Lista general de la que se va a eliminar el primer elemento.
 * @param destroy Función que se utilizará para destruir el dato del primer nodo.
 * @return GList Lista general con el primer elemento eliminado.
 */
GList glist_eliminar_inicio(GList list, FuncionDestructora destroy);

/**
 * @brief Destruye una lista general y sus datos utilizando la función pasada como argumento.
 *
 * @param list Lista general que se va a destruir.
 * @param destruir Función que se utilizará para destruir los datos de cada nodo.
 */
void glist_destruir(GList list, FuncionDestructora destruir);

#endif /* __GLIST_H__ */
