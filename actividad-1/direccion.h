#ifndef __DIRECCION_H__
#define __DIRECCION_H__

/**
 * @file direccion.h
 * @brief Definición y funciones relacionadas con la enumeración Direccion.
 */

/**
 * @enum Direccion
 * @brief Enumeración que representa las direcciones posibles: izquierda, derecha, arriba y abajo.
 */
typedef enum {
  LEFT, 
  RIGHT,  
  UP,     
  DOWN    
} Direccion;

/**
 * @brief Realiza una copia física de una dirección.
 *
 * @param a Dirección que se va a copiar.
 * @return Direccion* Puntero a la dirección copiada.
 */
Direccion *direccion_copiar(Direccion *a);

/**
 * @brief Imprime una dirección.
 *
 * @param direccion puntero a la Dirección que se va a imprimir.
 */
void direccion_imprimir(Direccion *direccion);

/**
 * @brief Retorna la dirección opuesta a la dirección dada.
 *
 * @param direccion Dirección de la cual se desea obtener la dirección opuesta.
 * @return Direccion opuesta.
 */
Direccion direccion_opuesta(Direccion direccion);


/**
 * @brief Destruye una dirección.
 *
 * @param a Puntero a la dirección que se va a destruir.
 */
void direccion_destruir(Direccion *a);

#endif /* __DIRECCION_H__ */
