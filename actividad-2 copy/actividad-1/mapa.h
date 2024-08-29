#ifndef __MAPA_H__
#define __MAPA_H__

/**
 * @file mapa.h
 * @brief Definición y funciones relacionadas con la estructura Mapa.
 */

typedef struct {
  char **coord; 
  size_t ancho;  
  size_t alto;    
} _Mapa;

typedef _Mapa *Mapa;

/**
 * @brief Imprime los datos del mapa y dibuja el tablero.
 *
 * @param mapa El mapa que se va a imprimir.
 */
void mapa_imprimir(Mapa mapa);

/**
 * @brief Destruye un mapa y libera la memoria que ocupa.
 *
 * @param mapa El mapa que se va a destruir.
 */
void mapa_destruir(Mapa mapa);

/**
 * @brief Crea un nuevo mapa con las dimensiones y la configuración dadas.
 *
 * @param alto Altura del mapa.
 * @param ancho Ancho del mapa.
 * @param coord Matriz que representa el contenido del mapa.
 * @return Mapa creado.
 */
Mapa mapa_crear(size_t alto, size_t ancho, char **coord);

#endif // __MAPA_H__
