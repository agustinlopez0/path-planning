Punto *punto_copiar(Punto * a) {
  Punto *nuevoPunto = malloc(sizeof(Punto));
  *nuevoPunto = *a;
  return nuevoPunto;
}

Robot robot_crear(Punto pos, Punto dest) {
  Robot robot = malloc(sizeof(_Robot));
  robot->pos = pos;
  robot->dest = dest;
  robot->movimientos = pila_crear();
  robot->visitados = glist_crear();
  robot->visitados =
      glist_agregar_inicio(robot->visitados, &pos,
                           (FuncionCopiadora) punto_copiar);
  return robot;
}

void mostrar_robot_mapa(Robot robot, Mapa mapa) {
  for (int i = 0; i < mapa->alto; i++) {
    printf("\t");
    for (int j = 0; j < mapa->ancho; j++) {
      Punto aux = { i, j };
      if (punto_comparar(aux, robot->pos) == 0)
        printf("R");
      else if (punto_comparar(aux, robot->dest) == 0)
        printf("D");
      else if (glist_include(robot->visitados, &(Punto) {
                             i, j}
                             , (FuncionComparadora) punto_compararp))
        printf("_");
      else
        printf("%c", mapa->coord[i][j]);
    }
    printf("\n");
  }
  getchar();
}

/**
 * Si el robot se puede mover en la direccion dada actualiza la posicion del robot
 * y devuelve 1, en caso contrario devuelve 0
 * "Si al intentar moverse a esa direccion se choca con un obstaculo devuelve 0,
 * sino lo mueve en esa direccion"
 */
int robot_mover(Robot robot, Mapa mapa, Direccion direccion) {
  int ret = 0;
  if (direccion == UP) {
    if (robot->pos.i - 1 >= 0
        && mapa->coord[robot->pos.i - 1][robot->pos.j] != '#') {
      robot->pos.i--;
      ret = 1;
    }
  } else if (direccion == DOWN) {
    if (robot->pos.i + 1 < mapa->alto
        && mapa->coord[robot->pos.i + 1][robot->pos.j] != '#') {
      robot->pos.i++;
      ret = 1;
    }
  } else if (direccion == LEFT) {
    if (robot->pos.j - 1 >= 0
        && mapa->coord[robot->pos.i][robot->pos.j - 1] != '#') {
      robot->pos.j--;
      ret = 1;
    }
  } else if (direccion == RIGHT) {
    if (robot->pos.j + 1 < mapa->ancho
        && mapa->coord[robot->pos.i][robot->pos.j + 1] != '#') {
      robot->pos.j++;
      ret = 1;
    }
  }
  if (ret) {
    robot->visitados =
        glist_agregar_inicio(robot->visitados, &robot->pos,
                             (FuncionCopiadora) punto_copiar);
    robot->movimientos =
        pila_apilar(robot->movimientos, &direccion,
                    (FuncionCopiadora) direccion_copiar);
    mostrar_robot_mapa(robot, mapa);

  }


  return ret;
}

int robot_retroceder(Robot robot, Mapa mapa) {
  if (pila_es_vacia(robot->movimientos))
    return 0;

  Direccion *ultima_direccion = pila_tope(robot->movimientos);
  int mov = robot_mover(robot, mapa, direccion_opuesta(*ultima_direccion));
  robot->movimientos =
      pila_desapilar(robot->movimientos,
                     (FuncionDestructora) direccion_destruir);
  robot->movimientos =
      pila_desapilar(robot->movimientos,
                     (FuncionDestructora) direccion_destruir);

  return mov;
}

void robot_destruir(Robot robot) {
  free(robot);
}

Direccion direccion_opuesta(Direccion direccion) {
  if (direccion == UP)
    return DOWN;
  if (direccion == DOWN)
    return UP;
  if (direccion == RIGHT)
    return LEFT;
  return RIGHT;
}

void mapa_destruir(Mapa mapa) {
  for (int i = 0; i < mapa->alto; i++)
    free(mapa->coord[i]);
  free(mapa->coord);
}

void robot_imprimir(Robot robot) {
  printf("Robot:");
  printf("\tPosicion: (%d, %d)\n", robot->pos.i, robot->pos.j);
  printf("\tDestino: (%d, %d)\n", robot->dest.i, robot->dest.j);
}

void mapa_imprimir(Mapa mapa) {
  printf("Mapa:\n");
  printf("\tDimensiones: %dx%d\n", mapa->alto, mapa->ancho);
  for (int i = 0; i < mapa->alto; i++) {
    printf("\t");
    for (int j = 0; j < mapa->ancho; j++)
      printf("%c", mapa->coord[i][j]);
    printf("\n");
  }
}

/**
 * Devuelve 0 si los puntos son iguales, cualquier otro valor si son distintos
 */
int punto_comparar(Punto a, Punto b) {
  return !(a.i == b.i && a.j == b.j);
}

int robot_en_destino(Robot robot) {
  return punto_comparar(robot->pos, robot->dest) == 0;
}

/**
 * 
 */


/**
 * Retorna 0 si estan alineados respecto al eje x.
 * Un valor positivo si b esta a la izquierda de a
 * Un valor negativo si b esta a la derecha de a
 */
int punto_distancia_x(Punto a, Punto b) {
  return a.j - b.j;
}

/**
 * Retorna 0 si estan alineados respecto al eje y.
 * Un valor positivo si b esta arriba de a
 * Un valor negativo si a esta arriba de b
 */
int punto_distancia_y(Punto a, Punto b) {
  return a.i - b.i;
}

void direccion_destruir(Direccion * a) {
  free(a);
}

Direccion *direccion_copiar(Direccion * a) {
  Direccion *copia = malloc(sizeof(Direccion));
  *copia = *a;
  return copia;
}

void punto_imprimir(Punto * punto) {
  printf("(%d, %d) ", punto->i, punto->j);
}

int punto_compararp(Punto * a, Punto * b) {
  return !(a->i == b->i && a->j == b->j);
}

void direccion_imprimir(Direccion * direccion) {
  if (*direccion == UP)
    printf("U");
  else if (*direccion == DOWN)
    printf("D");
  else if (*direccion == LEFT)
    printf("L");
  else if (*direccion == RIGHT)
    printf("R");
}

int robot_ir_a_destino(Robot robot, Mapa mapa) {
  // glist_recorrer(robot->visitados, (FuncionVisitante) punto_imprimir);
  if (robot_en_destino(robot))
    return 1;

  // printf("Movimiento %d\n", robot_mover(robot, mapa, LEFT));
  // printf("Movimiento %d\n", robot_mover(robot, mapa, RIGHT));
  // printf("Movimiento %d\n", robot_mover(robot, mapa, RIGHT));
  // printf("Movimiento %d\n", robot_mover(robot, mapa, RIGHT));
  // printf("Movimiento %d\n", robot_mover(robot, mapa, RIGHT));
  // printf("Retroceso %d\n", robot_retroceder(robot, mapa));
  // printf("Movimiento %d\n", robot_mover(robot, mapa, RIGHT));
  // printf("Retroceso %d\n", robot_retroceder(robot, mapa));


  Punto ultima_posicion = { -1, -1 };
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
    puts("");
  }

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
      robot_retroceder(robot, mapa);
  }
  // puts("\nRetroceso: ");
  // mostrar_robot_mapa(robot, mapa);
  return robot_ir_a_destino(robot, mapa);
}
