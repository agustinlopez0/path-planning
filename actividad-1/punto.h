#ifndef __PUNTO_H__
#define __PUNTO_H__

/**
 * @file punto.h
 * @brief Definiciones y operaciones relacionadas con puntos en un plano cartesiano.
 */

typedef struct {
  int i;
  int j;
} _Punto;

typedef _Punto* Punto;

/**
 * @brief Crea un nuevo punto con las coordenadas especificadas.
 *
 * @param i Coordenada en el eje vertical.
 * @param j Coordenada en el eje horizontal.
 * @return Puntero al nuevo punto creado.
 */
Punto punto_crear(int i, int j);

/**
 * @brief Calcula el hash de un punto.
 * 
 * @param punto Punto del cual se desea calcular el hash.
 * @return Valor hash del punto.
 */
unsigned int punto_hash(Punto punto);

/**
 * @brief Compara dos puntos para determinar si son iguales.
 *
 * @param a Primer punto a comparar.
 * @param b Segundo punto a comparar.
 * @return 0 si los puntos son iguales, cualquier otro valor si son diferentes.
 */
int punto_comparar(Punto a, Punto b);

/**
 * @brief Realiza una copia física de un punto.
 *
 * @param a Punto que se desea copiar.
 * @return Puntero a una copia del punto original.
 */
Punto punto_copiar(Punto a);

/**
 * @brief Calcula la distancia relativa en el eje x entre dos puntos.
 *
 * @param a Primer punto.
 * @param b Segundo punto.
 * @return 0 si los puntos están alineados respecto al eje x,
 *         un valor positivo si b está a la izquierda de a,
 *         un valor negativo si b está a la derecha de a.
 */
int punto_distancia_x(Punto a, Punto b);

/**
 * @brief Calcula la distancia relativa en el eje y entre dos puntos.
 *
 * @param a Primer punto.
 * @param b Segundo punto.
 * @return 0 si los puntos están alineados respecto al eje y,
 *         un valor positivo si b está arriba de a,
 *         un valor negativo si b está abajo de a.
 */
int punto_distancia_y(Punto a, Punto b);

/**
 * @brief Destruye un punto y libera la memoria asociada.
 *
 * @param a Puntero al punto que se desea destruir.
 */
void punto_destruir(Punto a);

#endif /* __PUNTO_H__ */
