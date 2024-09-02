#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include "tipos.h"

/**
 * @file tablahash.h
 * @brief Definición y funciones relacionadas con la estructura TablaHash.
 */

/**
 * @struct _TablaHash
 * @brief Estructura que representa una tabla hash.
 */
typedef struct _TablaHash *TablaHash;

/**
 * @brief Crea una nueva tabla hash con la capacidad y funciones especificadas.
 * 
 * @param capacidad Capacidad inicial de la tabla hash.
 * @param copia Función para copiar los elementos de la tabla.
 * @param comp Función para comparar los elementos de la tabla.
 * @param destr Función para destruir los elementos de la tabla.
 * @param hash Función para calcular el hash de los elementos de la tabla.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash);

/**
 * @brief Retorna la cantidad de elementos en la tabla hash.
 * 
 * @param tabla Tabla hash de la cual se desea obtener la cantidad de elementos.
 * @return Cantidad de elementos en la tabla hash.
 */
int tablahash_nelems(TablaHash tabla);

/**
 * @brief Retorna la capacidad de la tabla hash.
 * 
 * @param tabla Tabla hash de la cual se desea obtener la capacidad.
 * @return Capacidad de la tabla hash.
 */
int tablahash_capacidad(TablaHash tabla);

/**
 * @brief Destruye una tabla hash y libera la memoria ocupada por ella.
 * 
 * @param tabla Tabla hash que se va a destruir.
 */
void tablahash_destruir(TablaHash tabla);

/**
 * @brief Inserta un elemento en la tabla hash.
 * 
 * @param tabla Tabla hash en la que se va a insertar el elemento.
 * @param dato Elemento que se va a insertar.
 */
void tablahash_insertar(TablaHash tabla, void *dato);

/**
 * @brief Busca un elemento en la tabla hash.
 * 
 * @param tabla Tabla hash en la que se va a buscar el elemento.
 * @param dato Elemento que se va a buscar.
 * @return Puntero al elemento si se encuentra, NULL en caso contrario.
 */
void *tablahash_buscar(TablaHash tabla, void *dato);

/**
 * @brief Reorganiza la tabla hash para mantener un factor de carga bajo.
 * 
 * @param tabla Tabla hash que se va a rehashear.
 */
void tablahash_rehash(TablaHash tabla);

#endif /* __TABLAHASH_H__ */
