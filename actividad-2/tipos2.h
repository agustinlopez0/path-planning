#ifndef TIPOS2_H
#define TIPOS2_H
// #include "punto.h"
// #include "pila.h"
// #include "matriz.h"
typedef struct {
    int x, y;
} Punto;

typedef struct {
    Punto* pos; /**< Posición actual del robot */
    Punto* dest; /**< Destino del robot */
    int sensor; 
    Matriz* mapa;
} _Robot;

typedef _Robot* Robot;

#endif /* TIPOS2_H */
