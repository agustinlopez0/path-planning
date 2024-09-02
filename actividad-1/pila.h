#ifndef __PILA_H__
#define __PILA_H__

#include "tipos.h"
#include "glist.h"

/**
 * @file pila.h
 * @brief Definición y funciones relacionadas con la estructura Pila.
 */

/**
 * @typedef Pila
 * @brief Definición de pila como utilizando una lista general.
 */
typedef GList Pila;

/**
 * @brief Retorna una pila vacía.
 *
 * @return Pila vacía.
 */
Pila pila_crear(void);

/**
 * @brief Verifica si la pila está vacía.
 *
 * @param pila Pila a verificar.
 * @return 1 si la pila está vacía, 0 en caso contrario.
 */
int pila_es_vacia(Pila pila);

/**
 * @brief Devuelve el elemento en el tope de la pila sin removerlo.
 *
 * @param pila Pila de la cual se obtendrá el tope.
 * @return Puntero al elemento en el tope de la pila, o NULL si la pila está vacía.
 */
void* pila_tope(Pila pila);

/**
 * @brief Agrega un elemento a la pila.
 *
 * @param pila Pila a la cual se va a agregar el elemento.
 * @param dato Elemento a agregar.
 * @param copy Función para copiar el elemento.
 * @return Pila actualizada después de agregar el elemento.
 */
Pila pila_apilar(Pila pila, void* dato, FuncionCopiadora copy);

/**
 * @brief Elimina el elemento en el tope de la pila.
 *
 * @param pila Pila de la cual se va a eliminar el elemento del tope.
 * @param destroy Función para destruir el elemento eliminado.
 * @return Pila actualizada después de eliminar el elemento del tope.
 */
Pila pila_desapilar(Pila pila, FuncionDestructora destroy);

/**
 * @brief Recorre todos los elementos de la pila aplicando una función de visita.
 *
 * @param pila Pila a recorrer.
 * @param visit Función que será aplicada a cada elemento de la pila.
 */
void pila_recorrer(Pila pila, FuncionVisitante visit);

/**
 * @brief Destruye una pila y libera la memoria ocupada por sus elementos.
 *
 * @param pila Pila a destruir.
 * @param destroy Función para destruir los elementos de la pila.
 */
void pila_destruir(Pila pila, FuncionDestructora destroy);

#endif // __PILA_H__
