#include <stdio.h>
#include "simulacion.h"

void mostrar_robot_mapa(Robot robot, Mapa mapa) {
  Punto puntoAux;
  for (unsigned i = 0; i < mapa->alto; i++) {
    printf("\t");
    for (unsigned j = 0; j < mapa->ancho; j++) {
      puntoAux = punto_crear(i, j);
      if (punto_comparar(puntoAux, robot->pos) == 0)
        printf("R ");
      else if (punto_comparar(puntoAux, robot->dest) == 0)
        printf("D ");
      else if (glist_include
               (robot->visitados, puntoAux,
                (FuncionComparadora) punto_comparar))
        printf("_ ");
      else
        printf("%c ", mapa->coord[i][j]);
      punto_destruir(puntoAux);
    }
    printf("\n");
  }
  getchar();
}

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

    robot->visitados =
        glist_agregar_inicio(robot->visitados, robot->pos,
                             (FuncionCopiadora) punto_copiar);

    robot->movimientos =
        pila_apilar(robot->movimientos, &direccion,
                    (FuncionCopiadora) direccion_copiar);

    direccion_imprimir(&direccion);
    mostrar_robot_mapa(robot, mapa);
    // glist_recorrer(robot->visitados, (FuncionVisitante) punto_imprimir);
    // puts("");

    return 1;
  }

  return 0;
}

// Analizar llevar a robot.c
// sacar mapa


static int posicion_visitada(Robot robot, Direccion direccion) {
  int visitado = 0;
  if (direccion == UP) {
    Punto puntoAux = punto_crear(robot->pos->i - 1, robot->pos->j);
    visitado =
        glist_include(robot->visitados, puntoAux,
                      (FuncionComparadora) punto_comparar);
    punto_destruir(puntoAux);
  } else if (direccion == DOWN) {
    Punto puntoAux = punto_crear(robot->pos->i + 1, robot->pos->j);
    visitado =
        glist_include(robot->visitados, puntoAux,
                      (FuncionComparadora) punto_comparar);
    punto_destruir(puntoAux);
  } else if (direccion == LEFT) {
    Punto puntoAux = punto_crear(robot->pos->i, robot->pos->j - 1);
    visitado =
        glist_include(robot->visitados, puntoAux,
                      (FuncionComparadora) punto_comparar);
    punto_destruir(puntoAux);
  } else if (direccion == RIGHT) {
    Punto puntoAux = punto_crear(robot->pos->i, robot->pos->j + 1);
    visitado =
        glist_include(robot->visitados, puntoAux,
                      (FuncionComparadora) punto_comparar);
    punto_destruir(puntoAux);
  }
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
    if (robot->pos->i < robot->dest->i && !posicion_visitada(robot, DOWN)) {
      robot_mover(robot, mapa, DOWN);
    } else
      // Si el robot esta abajo del destino
    if (robot->pos->i > robot->dest->i && !posicion_visitada(robot, UP)) {
      robot_mover(robot, mapa, UP);
    }
    // Si el robot esta a la derecha del destino
    if (robot->pos->j > robot->dest->j && !posicion_visitada(robot, LEFT)) {
      robot_mover(robot, mapa, LEFT);
    } else
      // Si el robot esta a la izquierda del destino
    if (robot->pos->j < robot->dest->j && !posicion_visitada(robot, RIGHT)) {
      robot_mover(robot, mapa, RIGHT);
    }
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
    else {
      // Si no puedo moverme a ningun lugar donde no haya estado retrocedo
      //sacar mapa
      robot_retroceder(robot);
      mostrar_robot_mapa(robot, mapa);
    }
  }
  // Intenta nuevamente llegar a destino desde la posicion actual
  robot_ir_a_destino(robot, mapa);
}
