#ifndef __LEER_ARCHIVO_H__
#define __LEER_ARCHIVO_H__

#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "punto.h"

/**
 * @file leerArchivo.h
 * @brief Funciones relacionadas con la lectura del archivo de entrada
 */

/**
 * @brief Estructura que almacena los datos leídos desde el archivo de configuración.
 */
typedef struct {
  size_t alto, ancho;
  Punto posRobot;
  Punto destRobot;
  char **coord;
} _FileData;

typedef _FileData *FileData;

/**
 * @brief Lee un archivo de configuración y carga los datos en una estructura FileData.
 *
 * @param nombre_archivo Nombre del archivo de configuración.
 * @return Puntero a la estructura FileData creada con los datos del archivo, o NULL si hay errores.
 */
FileData leer_archivo(const char *nombre_archivo);

/**
 * @brief Libera la memoria asignada a una estructura FileData y sus campos.
 *
 * @param fileData Puntero a la estructura FileData a destruir.
 */
void filedata_destruir(FileData fileData);

#endif /* __LEER_ARCHIVO_H__ */