#ifndef TIPOS2_H
#define TIPOS2_H
#include "punto.h"
#include "pila.h"
#include "matriz.h"

typedef struct {
    Punto pos; /**< Posición actual del robot */
    Punto dest; /**< Destino del robot */
    int sensor; 
    Pila movimientos; /**< Pila de movimientos realizados por el robot */
    Matriz* mapa;
    GList usoSensor;
} _Robot;

typedef _Robot* Robot;

#endif /* TIPOS2_H */
