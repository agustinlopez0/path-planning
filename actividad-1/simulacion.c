#include <stdio.h>
#include "simulacion.h"
#include "tablahash.h"

static int es_movimiento_valido(Mapa mapa, unsigned int i, unsigned int j) {
  return i < mapa->alto && j < mapa->ancho && mapa->coord[i][j] != '#';
}

static void actualizar_posicion(Robot robot, unsigned int nuevoI,
                                unsigned int nuevoJ) {
  robot->pos->i = nuevoI;
  robot->pos->j = nuevoJ;
}

int robot_mover(Robot robot, Mapa mapa, Direccion direccion) {
  unsigned int nuevoI = robot->pos->i;
  unsigned int nuevoJ = robot->pos->j;

  switch (direccion) {
  case UP:
    nuevoI--;
    break;
  case DOWN:
    nuevoI++;
    break;
  case LEFT:
    nuevoJ--;
    break;
  case RIGHT:
    nuevoJ++;
    break;
  }

  if (es_movimiento_valido(mapa, nuevoI, nuevoJ)) {
    actualizar_posicion(robot, nuevoI, nuevoJ);
    tablahash_insertar(robot->visitados, robot->pos);

    robot->movimientos =
        pila_apilar(robot->movimientos, &direccion,
                    (FuncionCopiadora) direccion_copiar);

    direccion_imprimir(&direccion);

    return 1;
  }

  return 0;
}

static int posicion_visitada(Robot robot, Direccion direccion) {
  int visitado = 0;
  Punto puntoAux;
  if (direccion == UP)
    puntoAux = punto_crear(robot->pos->i - 1, robot->pos->j);
  else if (direccion == DOWN)
    puntoAux = punto_crear(robot->pos->i + 1, robot->pos->j);
  else if (direccion == LEFT)
    puntoAux = punto_crear(robot->pos->i, robot->pos->j - 1);
  else if (direccion == RIGHT)
    puntoAux = punto_crear(robot->pos->i, robot->pos->j + 1);

  visitado = (tablahash_buscar(robot->visitados, puntoAux) != NULL);
  punto_destruir(puntoAux);

  return visitado;
}

void robot_ir_a_destino(Robot robot, Mapa mapa) {
  if (robot_en_destino(robot))
    return;

  // Sigo la ruta optimista por nodos no visitados hasta que no logro moverme mas
  Punto ultimaPosicion = NULL;
  do {
    punto_destruir(ultimaPosicion);
    ultimaPosicion = punto_copiar(robot->pos);

    // Si el robot esta arriba del destino
    while (punto_distancia_y(robot->pos, robot->dest) < 0
           && !posicion_visitada(robot, DOWN)
           && robot_mover(robot, mapa, DOWN));

    // Si el robot esta abajo del destino
    while (punto_distancia_y(robot->pos, robot->dest) > 0
           && !posicion_visitada(robot, UP)
           && robot_mover(robot, mapa, UP));

    // Si el robot esta a la derecha del destino
    while (punto_distancia_x(robot->pos, robot->dest) > 0
           && !posicion_visitada(robot, LEFT)
           && robot_mover(robot, mapa, LEFT));

    // Si el robot esta a la izquierda del destino
    while (punto_distancia_x(robot->pos, robot->dest) < 0
           && !posicion_visitada(robot, RIGHT)
           && robot_mover(robot, mapa, RIGHT));
           
  } while (punto_comparar(ultimaPosicion, robot->pos) != 0);
  punto_destruir(ultimaPosicion);

  // Una vez que no puedo avanzar por la ruta optimista
  if (!robot_en_destino(robot)) {
    //Voy para donde pueda y no haya ido antes
    if (!posicion_visitada(robot, DOWN) && robot_mover(robot, mapa, DOWN));
    else if (!posicion_visitada(robot, UP)
             && robot_mover(robot, mapa, UP));
    else if (!posicion_visitada(robot, LEFT)
             && robot_mover(robot, mapa, LEFT));
    else if (!posicion_visitada(robot, RIGHT)
             && robot_mover(robot, mapa, RIGHT));
    else // Si no puedo moverme a ningun lugar donde no haya estado retrocedo
      robot_retroceder(robot);
    
  }
  
  // Intenta nuevamente llegar a destino desde la posicion actual
  robot_ir_a_destino(robot, mapa);
}
