#ifndef __DIRECCION_H__
#define __DIRECCION_H__

typedef enum {
  LEFT,
  RIGHT,
  UP,
  DOWN
} Direccion;

/**
 * Destruye una direccion y libera la memoria.
 */
void direccion_destruir(Direccion * a);

/**
 * Realiza una copia fisica de una dirección.
 */
Direccion *direccion_copiar(Direccion * a);

/**
 * Dada una dirección retorna su opuesta.
 */
Direccion direccion_opuesta(Direccion direccion);

/**
 * Imprime una dirección.
 */
void direccion_imprimir(Direccion * direccion);

#endif /* __DIRECCION_H__ */