#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "matriz.h"
#include <unistd.h>

typedef struct {
  int x, y;
} Punto;

typedef struct {
  Punto *pos;   /**< Posición actual del robot */
  Punto *dest;   /**< Destino del robot */
  int sensor;
  Matriz *mapa;
} _Robot;

typedef _Robot *Robot;

typedef struct {
  int costo;
  int prioridad;
  Punto pos;
} Nodo;

typedef struct {
  Nodo *nodos;
  int capacidad;
  int size;
} ColaPrioridad;

typedef struct {
  Punto padre;
  int costo;
} CeldaInfo;

void intercambiar(Nodo * a, Nodo * b) {
  Nodo temp = *a;
  *a = *b;
  *b = temp;
}

void burbujeoHaciaArriba(ColaPrioridad * cola, int i) {
  while (i > 0
         && cola->nodos[i].prioridad <
         cola->nodos[(i - 1) / 2].prioridad) {
    intercambiar(&cola->nodos[i], &cola->nodos[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void burbujeoHaciaAbajo(ColaPrioridad * cola, int i) {
  int izq = 2 * i + 1;
  int der = 2 * i + 2;
  int menor = i;

  if (izq < cola->size
      && cola->nodos[izq].prioridad < cola->nodos[menor].prioridad) {
    menor = izq;
  }
  if (der < cola->size
      && cola->nodos[der].prioridad < cola->nodos[menor].prioridad) {
    menor = der;
  }
  if (menor != i) {
    intercambiar(&cola->nodos[i], &cola->nodos[menor]);
    burbujeoHaciaAbajo(cola, menor);
  }
}

void inicializarCola(ColaPrioridad * cola, int capacidad) {
  cola->nodos = (Nodo *) malloc(capacidad * sizeof(Nodo));
  cola->capacidad = capacidad;
  cola->size = 0;
}

void insertarNodo(ColaPrioridad * cola, Nodo nodo) {
  if (cola->size < cola->capacidad) {
    cola->nodos[cola->size] = nodo;
    burbujeoHaciaArriba(cola, cola->size);
    cola->size++;
  }
}

Nodo extraerNodoConPrioridad(ColaPrioridad * cola) {
  Nodo nodo = cola->nodos[0];
  cola->size--;
  cola->nodos[0] = cola->nodos[cola->size];
  burbujeoHaciaAbajo(cola, 0);
  return nodo;
}

#define INF INT_MAX

void liberarCeldaInfo(CeldaInfo ** celdaInfo, int N) {
  for (int i = 0; i < N; i++) {
    free(celdaInfo[i]);
  }
  free(celdaInfo);
}

void inicializarCeldaInfo(CeldaInfo *** celdaInfo, int N, int M) {
  *celdaInfo = (CeldaInfo **) malloc(N * sizeof(CeldaInfo *));
  for (int i = 0; i < N; i++) {
    (*celdaInfo)[i] = (CeldaInfo *) malloc(M * sizeof(CeldaInfo));
  }
}

void imprimir_mapa(Robot robot) {
  fprintf(stderr, "\n-------------------\n");
  for (size_t i = 0; i < matriz_num_filas(robot->mapa); i++) {
    for (size_t j = 0; j < matriz_num_columnas(robot->mapa); j++) {
      if (i == (size_t) robot->pos->x && j == (size_t) robot->pos->y) {
        fprintf(stderr, "R ");
      } else if (i == (size_t) robot->dest->x
                 && j == (size_t) robot->dest->y) {
        fprintf(stderr, "D ");
      } else {
        fprintf(stderr, "%c ", matriz_leer(robot->mapa, i, j));
      }
    }
    fprintf(stderr, " |\n");
  }
  fprintf(stderr, "-------------------\n");

  usleep(200000);
}

int imprimirCamino(CeldaInfo ** celdaInfo, Robot robot) {
  Punto camino[25];
  int longitud = 0;
  Punto destino = *robot->dest;
  for (Punto p = destino; p.x != -1 && p.y != -1;
       p = celdaInfo[p.x][p.y].padre) {
    camino[longitud++] = p;
  }

  fprintf(stderr, "Camino encontrado:\n");
  for (int i = longitud - 1; i >= 0; i--) {
    Punto *p = malloc(sizeof(Punto));
    p->x = camino[i].x;
    p->y = camino[i].y;
    if (matriz_leer(robot->mapa, p->x, p->y) == '.'
        || matriz_leer(robot->mapa, p->x, p->y) == 's') {
      robot->pos = p;
    } else {
      return 0;
    }
    imprimir_mapa(robot);
    fprintf(stderr, "(%d, %d) - (%c)\n", camino[i].x, camino[i].y,
            matriz_leer(robot->mapa, camino[i].x, camino[i].y));
  }
  return 1;
}

int usar_sensor(Robot robot) {
  // Enviar la posición actual del robot para usar el sensor
  printf("? %d %d\n", robot->pos->x, robot->pos->y);
  fflush(stdout);

  matriz_escribir(robot->mapa, robot->pos->x, robot->pos->y, 's');

  int cambios = 0;

  int d1, d2, d3, d4;
  // Leer las distancias desde el sensor
  scanf("%d %d %d %d", &d1, &d2, &d3, &d4);
  fprintf(stderr, "usar_sensor (%d, %d) ", robot->pos->x, robot->pos->y);
  fprintf(stderr, "%d %d %d %d:", d1, d2, d3, d4);

  size_t num_filas = matriz_num_filas(robot->mapa);
  size_t num_columnas = matriz_num_columnas(robot->mapa);

  // Actualizar posiciones hacia arriba
  if (d1 > 1) {
    for (int i = 1; i < d1; i++) {
      if ((robot->pos->x - i) >= 0) {
        if (matriz_leer(robot->mapa, robot->pos->x - i, robot->pos->y) ==
            '?') {
          cambios++;
          matriz_escribir(robot->mapa, robot->pos->x - i, robot->pos->y,
                          '.');
        }
      }
    }
  }

  if (d1 <= robot->sensor && (robot->pos->x - d1) >= 0) {
    matriz_escribir(robot->mapa, robot->pos->x - d1, robot->pos->y, '#');
  }
  // Actualizar posiciones hacia abajo
  if (d2 > 1) {
    for (int i = 1; i < d2; i++) {
      if ((size_t) (robot->pos->x + i) < num_filas) {
        if (matriz_leer(robot->mapa, robot->pos->x + i, robot->pos->y) ==
            '?') {
          cambios++;
          matriz_escribir(robot->mapa, robot->pos->x + i, robot->pos->y,
                          '.');
        }
      }
    }
  }
  if (d2 <= robot->sensor && (size_t) (robot->pos->x + d2) < num_filas) {
    matriz_escribir(robot->mapa, robot->pos->x + d2, robot->pos->y, '#');
  }
  // Actualizar posiciones hacia la izquierda
  if (d3 > 1) {
    for (int i = 1; i < d3; i++) {
      if ((robot->pos->y - i) >= 0) {
        if (matriz_leer(robot->mapa, robot->pos->x, robot->pos->y - i) ==
            '?') {
          cambios++;
          matriz_escribir(robot->mapa, robot->pos->x, robot->pos->y - i,
                          '.');
        }
      }
    }
  }

  if (d3 <= robot->sensor && (robot->pos->y - d3) >= 0) {
    matriz_escribir(robot->mapa, robot->pos->x, robot->pos->y - d3, '#');
  }
  // Actualizar posiciones hacia la derecha
  if (d4 > 1) {
    for (int i = 1; i < d4; i++) {
      if ((size_t) (robot->pos->y + i) < num_columnas) {
        if (matriz_leer(robot->mapa, robot->pos->x, robot->pos->y + i) ==
            '?') {
          cambios++;
          matriz_escribir(robot->mapa, robot->pos->x, robot->pos->y + i,
                          '.');
        }
      }
    }
  }

  if (d4 <= robot->sensor && (size_t) (robot->pos->y + d4) < num_columnas) {
    matriz_escribir(robot->mapa, robot->pos->x, robot->pos->y + d4, '#');
  }
  // Imprimir el mapa actualizado
  imprimir_mapa(robot);
  return cambios;
}

#include <math.h>               // Para la función fabs()

void d_star_lite(Robot robot) {
  Punto inicio = *robot->pos;
  Punto destino = *robot->dest;
  int N = matriz_num_filas(robot->mapa);
  int M = matriz_num_columnas(robot->mapa);
  ColaPrioridad cola;
  inicializarCola(&cola, N * M);
  int costos[N][M];
  CeldaInfo **celdaInfo;
  inicializarCeldaInfo(&celdaInfo, N, M);

  // Inicialización de costos y celdaInfo
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      costos[i][j] = INF;
      celdaInfo[i][j].costo = INF;
      celdaInfo[i][j].padre = (Punto) {
      -1, -1};                  // Indica que no hay predecesor
    }
  }

  // Inicialización del nodo de inicio
  costos[inicio.x][inicio.y] = 0;
  celdaInfo[inicio.x][inicio.y].costo = 0;
  celdaInfo[inicio.x][inicio.y].padre = (Punto) {
  -1, -1};                      // Nodo inicial sin padre
  Nodo nodoInicio = { 0, 0, inicio };
  insertarNodo(&cola, nodoInicio);

  while (cola.size > 0) {
    Nodo nodo = extraerNodoConPrioridad(&cola);

    // Verifica si se ha llegado al destino
    if (nodo.pos.x == destino.x && nodo.pos.y == destino.y) {
      if (!imprimirCamino(celdaInfo, robot)) {
        usar_sensor(robot);
        d_star_lite(robot);
        return;
      }
      free(cola.nodos);         // Liberar memoria de la cola
      liberarCeldaInfo(celdaInfo, N);   // Liberar memoria de celdaInfo
      return;
    }

    // Actualiza vecinos
    int dx[4] = { 0, 0, -1, 1 };        // Movimiento horizontal y vertical
    int dy[4] = { -1, 1, 0, 0 };        // Movimiento vertical y horizontal
    for (int i = 0; i < 4; i++) {
      int nx = nodo.pos.x + dx[i];
      int ny = nodo.pos.y + dy[i];
      if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
        char celda = matriz_leer(robot->mapa, nx, ny);
        if (celda != '#') {
          int distanciaEstimado =
              fabs(destino.x - nx) + fabs(destino.y - ny);
          int nuevoCosto = nodo.costo + 1 + distanciaEstimado;  // Costo uniforme más heurística
          if (celda == '?') {
            nuevoCosto += 10;   // Penalización para celdas con '?'
          }
          if (nuevoCosto < costos[nx][ny]) {
            costos[nx][ny] = nuevoCosto;
            celdaInfo[nx][ny].costo = nuevoCosto;
            celdaInfo[nx][ny].padre = nodo.pos; // Establece el predecesor
            Nodo vecino = { nuevoCosto, nuevoCosto, { nx, ny }
            };
            insertarNodo(&cola, vecino);
          }
        }
      }
    }
  }
  free(cola.nodos);             // Liberar memoria de la cola
  liberarCeldaInfo(celdaInfo, N);       // Liberar memoria de celdaInfo
}




void robot_set_mapa(Robot robot) {
  int n = (int) matriz_num_filas(robot->mapa);
  int m = (int) matriz_num_columnas(robot->mapa);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      matriz_escribir(robot->mapa, i, j, '?');
  matriz_escribir(robot->mapa, robot->pos->x, robot->pos->y, '.');
  matriz_escribir(robot->mapa, robot->dest->x, robot->dest->y, '.');

  // matriz_escribir(robot->mapa, 0, 0, '.');
  // matriz_escribir(robot->mapa, 1, 0, '.');
  // matriz_escribir(robot->mapa, 2, 0, '.');
  // matriz_escribir(robot->mapa, 3, 0, '.');
  // matriz_escribir(robot->mapa, 4, 0, '.');
  // matriz_escribir(robot->mapa, 0, 1, '.');
  // matriz_escribir(robot->mapa, 1, 1, '#');
  // matriz_escribir(robot->mapa, 2, 1, '#');
  // matriz_escribir(robot->mapa, 3, 1, '#');
  // matriz_escribir(robot->mapa, 4, 1, '.');
  // matriz_escribir(robot->mapa, 0, 2, '.');
  // matriz_escribir(robot->mapa, 1, 2, '#');
  // matriz_escribir(robot->mapa, 2, 2, '.');
  // matriz_escribir(robot->mapa, 3, 2, '.');
  // matriz_escribir(robot->mapa, 4, 2, '.');
  // matriz_escribir(robot->mapa, 0, 3, '.');
  // matriz_escribir(robot->mapa, 1, 3, '#');
  // matriz_escribir(robot->mapa, 2, 3, '.');
  // matriz_escribir(robot->mapa, 3, 3, '#');
  // matriz_escribir(robot->mapa, 4, 3, '.');
  // matriz_escribir(robot->mapa, 0, 4, '.');
  // matriz_escribir(robot->mapa, 1, 4, '.');
  // matriz_escribir(robot->mapa, 2, 4, '.');
  // matriz_escribir(robot->mapa, 3, 4, '#');
  // matriz_escribir(robot->mapa, 4, 4, '.');
}

int main() {
  Robot robot = malloc(sizeof(_Robot));
  Punto a = { 0, 0 }, b = { 2, 2 };
  robot->pos = &a;
  robot->dest = &b;

  int N, M;
  scanf("%d%d%d", &N, &M, &robot->sensor);
  robot->mapa = matriz_crear(N, M);

  scanf("%d%d", &robot->pos->x, &robot->pos->y);
  scanf("%d%d", &robot->dest->x, &robot->dest->y);

  robot_set_mapa(robot);
  // matriz_escribir(robot->mapa, 0, 0, '.');
  // matriz_escribir(robot->mapa, 1, 0, '.');
  // matriz_escribir(robot->mapa, 2, 0, '.');
  // matriz_escribir(robot->mapa, 3, 0, '.');
  // matriz_escribir(robot->mapa, 4, 0, '.');

  // matriz_escribir(robot->mapa, 0, 1, '.');
  // matriz_escribir(robot->mapa, 1, 1, '#');
  // matriz_escribir(robot->mapa, 2, 1, '#');
  // matriz_escribir(robot->mapa, 3, 1, '#');
  // matriz_escribir(robot->mapa, 4, 1, '.');

  // matriz_escribir(robot->mapa, 0, 2, '#');
  // matriz_escribir(robot->mapa, 1, 2, '#');
  // matriz_escribir(robot->mapa, 2, 2, '.');
  // matriz_escribir(robot->mapa, 3, 2, '.');
  // matriz_escribir(robot->mapa, 4, 2, '.');

  // matriz_escribir(robot->mapa, 0, 3, '.');
  // matriz_escribir(robot->mapa, 1, 3, '#');
  // matriz_escribir(robot->mapa, 2, 3, '.');
  // matriz_escribir(robot->mapa, 3, 3, '#');
  // matriz_escribir(robot->mapa, 4, 3, '.');

  // matriz_escribir(robot->mapa, 0, 4, '.');
  // matriz_escribir(robot->mapa, 1, 4, '.');
  // matriz_escribir(robot->mapa, 2, 4, '.');
  // matriz_escribir(robot->mapa, 3, 4, '.');
  // matriz_escribir(robot->mapa, 4, 4, '.');

  // imprimir_mapa(robot);
  usar_sensor(robot);
  // imprimir_mapa(robot);

  d_star_lite(robot);

  matriz_destruir(robot->mapa);
  free(robot);
  printf("! RRRRDDLL\n");
  return 0;
}
