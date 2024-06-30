#include <stdio.h>
#include "simulacion.h"

void mostrar_robot_mapa(Robot robot, Mapa mapa) {
  for (int i = 0; i < mapa->alto; i++) {
    printf("\t");
    for (int j = 0; j < mapa->ancho; j++) {
      Punto aux = { i, j };
      if (punto_comparar(aux, robot->pos) == 0)
        printf("R ");
      else if (punto_comparar(aux, robot->dest) == 0)
        printf("D ");
      else if (glist_include(robot->visitados, &(Punto) {
                             i, j}
                             , (FuncionComparadora) punto_compararp))
        printf("_ ");
      else
        printf("%c ", mapa->coord[i][j]);
    }
    printf("\n");
  }
  getchar();
}

static int es_movimiento_valido(Mapa mapa, int i, int j) {
  return i >= 0 && i < mapa->alto && j >= 0 && j < mapa->ancho
      && mapa->coord[i][j] != '#';
}

static int actualizar_posicion(Robot robot, int nuevo_i, int nuevo_j) {
  robot->pos.i = nuevo_i;
  robot->pos.j = nuevo_j;
  return 1;
}

int robot_mover(Robot robot, Mapa mapa, Direccion direccion) {
  int nuevo_i = robot->pos.i;
  int nuevo_j = robot->pos.j;

  switch (direccion) {
  case UP:
    nuevo_i--;
    break;
  case DOWN:
    nuevo_i++;
    break;
  case LEFT:
    nuevo_j--;
    break;
  case RIGHT:
    nuevo_j++;
    break;
  }

  if (es_movimiento_valido(mapa, nuevo_i, nuevo_j)) {
    actualizar_posicion(robot, nuevo_i, nuevo_j);

    // Copiar la posición actual del robot
    Punto *pos_copia = punto_copiar(&robot->pos);
    robot->visitados =
        glist_agregar_inicio(robot->visitados, pos_copia,
                             (FuncionCopiadora) punto_copiar);

    // Copiar la dirección del movimiento
    Direccion *dir_copia = direccion_copiar(&direccion);
    robot->movimientos =
        pila_apilar(robot->movimientos, dir_copia,
                    (FuncionCopiadora) direccion_copiar);

    direccion_imprimir(&direccion);
    mostrar_robot_mapa(robot, mapa);

    return 1;
  }

  return 0;
}

int robot_retroceder(Robot robot, Mapa mapa) {
  if (pila_es_vacia(robot->movimientos))
    return 0;

  // Obtener la última dirección desde la pila
  Direccion *ultima_direccion = pila_tope(robot->movimientos);
  if (!ultima_direccion)
    return 0;

  // Mover el robot en la dirección opuesta
  int mov = robot_mover(robot, mapa, direccion_opuesta(*ultima_direccion));

  if (mov)
    // Desapilo el movimiento que acabo de hacer
    robot->movimientos =
        pila_desapilar(robot->movimientos,
                       (FuncionDestructora) direccion_destruir);

  // Desapilo el movimiento que use para retroceder
  robot->movimientos =
      pila_desapilar(robot->movimientos,
                     (FuncionDestructora) direccion_destruir);

  return mov;
}

int robot_ir_a_destino(Robot robot, Mapa mapa) {
  if (robot_en_destino(robot))
    return 1;

  Punto ultima_posicion = { -1, -1 };

  // Sigo la ruta optimista por nodos no visitado hasta que no puedo mas
  while (punto_comparar(ultima_posicion, robot->pos) != 0) {
    ultima_posicion = robot->pos;
    // Si el robot esta arriba del destino
    if (robot->pos.i < robot->dest.i &&
        !glist_include(robot->visitados, &(Punto) {
                       robot->pos.i + 1, robot->pos.j}
                       , (FuncionComparadora) punto_compararp)
        ) {
      robot_mover(robot, mapa, DOWN);

    }
    // Si el robot esta abajo del destino
    if (robot->pos.i > robot->dest.i &&
        !glist_include(robot->visitados, &(Punto) {
                       robot->pos.i - 1, robot->pos.j}
                       , (FuncionComparadora) punto_compararp)
        ) {
      robot_mover(robot, mapa, UP);

    }
    // Si el robot esta a la derecha del destino
    if (robot->pos.j > robot->dest.j &&
        !glist_include(robot->visitados, &(Punto) {
                       robot->pos.i, robot->pos.j - 1}
                       , (FuncionComparadora) punto_compararp)
        ) {
      robot_mover(robot, mapa, LEFT);

    }
    // Si el robot esta a la izquierda del destino
    if (robot->pos.j < robot->dest.j &&
        !glist_include(robot->visitados, &(Punto) {
                       robot->pos.i, robot->pos.j + 1}
                       , (FuncionComparadora) punto_compararp)
        ) {
      robot_mover(robot, mapa, RIGHT);

    }
  }

  // Una vez que no puedo avanzar por la ruta optimista
  if (!robot_en_destino(robot)) {
    //Voy para donde pueda y no haya ido antes
    if (!glist_include(robot->visitados, &(Punto) {
                       robot->pos.i + 1, robot->pos.j}
                       , (FuncionComparadora) punto_compararp)
        && robot_mover(robot, mapa, DOWN)
        );
    else if (!glist_include(robot->visitados, &(Punto) {
                            robot->pos.i - 1, robot->pos.j}
                            , (FuncionComparadora) punto_compararp)
             && robot_mover(robot, mapa, UP)
        );
    else if (!glist_include(robot->visitados, &(Punto) {
                            robot->pos.i, robot->pos.j - 1}
                            , (FuncionComparadora) punto_compararp)
             && robot_mover(robot, mapa, LEFT)
        );
    else if (!glist_include(robot->visitados, &(Punto) {
                            robot->pos.i, robot->pos.j + 1}
                            , (FuncionComparadora) punto_compararp)
             && robot_mover(robot, mapa, RIGHT)
        );
    else
      // Si no puedo moverme a ningun lugar donde no haya estado retrocedo
      robot_retroceder(robot, mapa);
  }
  return robot_ir_a_destino(robot, mapa);
}
