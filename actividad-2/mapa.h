#ifndef __MAPA_H__
#define __MAPA_H__
#include <stdlib.h>

/**
 * @file mapa.h
 * @brief Definición y funciones relacionadas con la estructura Mapa.
 */
typedef struct Mapa_ Mapa;

/**
 * @brief Crea un nuevo mapa.
 * 
 * @param numFilas Número de filas del mapa.
 * @param numColumnas Número de columnas del mapa.
 * @return Mapa* creado.
 */
Mapa* mapa_crear(size_t numFilas, size_t numColumnas);

/**
 * @brief Destruye un mapa.
 * 
 * @param mapa Mapa a destruir.
 */
void mapa_destruir(Mapa* mapa);

/**
 * @brief Obtiene el dato guardado en la posición dada del mapa.
 * 
 * @param mapa Mapa a leer.
 * @param fil Fila del dato.
 * @param col Columna del dato.
 * @return char Dato guardado en la posición dada.
 */
char mapa_leer(Mapa* mapa, size_t fil, size_t col);

/**
 * @brief Modifica el dato guardado en la posición dada del mapa.
 * 
 * @param mapa Mapa a modificar.
 * @param fil Fila del dato.
 * @param col Columna del dato.
 * @param val Nuevo valor a guardar.
 */
void mapa_escribir(Mapa* mapa, size_t fil, size_t col, char val);

/**
 * @brief Obtiene número de filas del mapa.
 * 
 * @param mapa Mapa a leer.
 * @return size_t Número de filas del mapa.
 */
size_t mapa_num_filas(Mapa* mapa);

/**
 * @brief Obtiene número de columnas del mapa.
 * 
 * @param mapa Mapa a leer.
 * @return size_t Número de columnas del mapa.
 */
size_t mapa_num_columnas(Mapa* mapa);

#endif /* __MAPA_H__ */
