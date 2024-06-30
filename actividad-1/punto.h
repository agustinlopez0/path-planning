#ifndef __PUNTO_H__
#define __PUNTO_H__

typedef struct {
  int i, j;
} _Punto;

typedef _Punto* Punto;

/**
 * Crea un nuevo punto con las coordenadas pasadas como argumento
 */
Punto punto_crear(int i, int j);

/**
 * Destruye un punto y libera la memoria
 */
void punto_destruir(Punto a);

/**
 * Devuelve 0 si los puntos son iguales, cualquier otro valor si son distintos
 */
int punto_comparar(Punto a, Punto b);

/**
 * Realiza una copia fisica de un punto.
 */
Punto punto_copiar(Punto a);

/**
 * Retorna 0 si estan alineados respecto al eje x.
 * Un valor positivo si b esta a la izquierda de a
 * Un valor negativo si b esta a la derecha de a
 */
int punto_distancia_x(Punto a, Punto b);

/**
 * Retorna 0 si estan alineados respecto al eje y.
 * Un valor positivo si b esta arriba de a
 * Un valor negativo si a esta arriba de b
 */
int punto_distancia_y(Punto a, Punto b);

/**
 * Imprime un punto
 */
void punto_imprimir(Punto punto);

#endif /* __PUNTO_H__ */