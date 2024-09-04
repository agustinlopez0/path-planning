#ifndef __ROBOT_AUX_H__
#define __ROBOT_AUX_H__

#include "tipos.h"
#include "mapa.h"
#include "dglist.h"

/**
 * @file robotAux.h
 * @brief Definición y funciones relacionadas con la estructura Robot.
 */

/**
 * @brief Estructura que representa un robot y la información necesaria para su funcionamiento.
 * 
 * @param pos Posición actual del robot.
 * @param dest Posición destino del robot.
 * @param mapa Matriz de caracteres que representa al mapa en el que se encuentra el robot.
 * @param camino Lista de caracteres que representa el camino que siguio el robot desde su posicion inicial.
 */
typedef struct {
  Punto *pos;
  Punto *dest;
  Mapa *mapa;
  DGList camino;
} _Robot;

typedef _Robot *Robot;

/**
 * @brief Crea un nuevo robot con los campos inicializados.
 * 
 * @param pos Posición inicial del robot.
 * @param dest Posición destino del robot.
 * @param N Número de filas del mapa.
 * @param M Número de columnas del mapa.
 * @return Robot creado.
 */
Robot robot_crear(Punto pos, Punto dest, int N, int M);

/** 
 * @brief Usa el sensor del robot y actualiza el mapa cargado en memoria.
 * 
 * @param robot Robot a usar el sensor.
 * @return int Cambios realizados.
 */
int usar_sensor(Robot robot);

/** 
 * @brief Destruye un robot y libera la memoria.
 * 
 * @param robot Robot a destruir.
 */
void robot_destruir(Robot robot);



#endif // __ROBOT_AUX_H__