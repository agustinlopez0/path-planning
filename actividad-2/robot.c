#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "mapa.h"
#include "colaprioridad.h"
#include "glist.h"
#include <unistd.h>

void imprimir_char(char *a) {
  printf("%c", *a);
}
void imprimir_char_stderr(char *a) {
  fprintf(stderr, "%c", *a);
}

typedef struct {
  int x, y;
} Punto;

typedef struct {
  Punto *pos;
  Punto *dest;
  Mapa *mapa;
  GList camino;
} _Robot;

typedef _Robot *Robot;

void robot_destruir(Robot robot) {
  free(robot->pos);
  free(robot->dest);
  glist_destruir(robot->camino, free);
  mapa_destruir(robot->mapa);
  free(robot);
}

void robot_set_mapa(Robot robot) {
  size_t n = mapa_num_filas(robot->mapa);
  size_t m = mapa_num_columnas(robot->mapa);
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++)
      mapa_escribir(robot->mapa, i, j, '?');
  mapa_escribir(robot->mapa, robot->pos->x, robot->pos->y, '.');
  mapa_escribir(robot->mapa, robot->dest->x, robot->dest->y, '.');
}

void imprimir_robot(Robot robot) {
  fprintf(stderr, "Robot: (%d, %d) -> (%d, %d)\n",
          robot->pos->x, robot->pos->y, robot->dest->x, robot->dest->y);
}

Robot robot_crear(Punto pos, Punto dest, int N, int M) {
  Robot robot = malloc(sizeof(_Robot));
  robot->pos = malloc(sizeof(Punto));
  robot->pos->x = pos.x;
  robot->pos->y = pos.y;

  robot->dest = malloc(sizeof(Punto));
  robot->dest->x = dest.x;
  robot->dest->y = dest.y;

  robot->camino = glist_crear();

  robot->mapa = mapa_crear(N, M);
  robot_set_mapa(robot);

  return robot;
}

typedef struct {
  unsigned int costo;
  Punto pos;
} _Nodo;

typedef _Nodo *Nodo;

typedef struct {
  Punto padre;
  int costo;
} CeldaInfo;

void liberarCeldaInfo(CeldaInfo ** celdaInfo, int N) {
  for (int i = 0; i < N; i++) {
    free(celdaInfo[i]);
  }
  free(celdaInfo);
}

void imprimir_celdaInfo(CeldaInfo ** celdaInfo, int N, int M) {
  // Imprime el estado actual del mapa (para depuración)
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      fprintf(stderr, "(%10d {%2d, %2d}) |", celdaInfo[i][j].costo,
              celdaInfo[i][j].padre.x, celdaInfo[i][j].padre.y);
    }
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "\n\n");
}

CeldaInfo **inicializarCeldaInfo(int N, int M) {
  CeldaInfo **celdaInfo = malloc(N * sizeof(CeldaInfo *));
  for (int i = 0; i < N; i++) {
    celdaInfo[i] = malloc(M * sizeof(CeldaInfo));
    for (int j = 0; j < M; j++) {
      celdaInfo[i][j].costo = INT_MAX;
      celdaInfo[i][j].padre = (Punto) {
      -1, -1};                  // Indica que no hay predecesor
    }
  }

  return celdaInfo;
}

void imprimir_mapa(Robot robot) {
  fprintf(stderr, "\n-------------------\n");
  for (size_t i = 0; i < mapa_num_filas(robot->mapa); i++) {
    for (size_t j = 0; j < mapa_num_columnas(robot->mapa); j++) {
      if (i == (size_t) robot->pos->x && j == (size_t) robot->pos->y) {
        fprintf(stderr, "R ");
      } else if (i == (size_t) robot->dest->x
                 && j == (size_t) robot->dest->y) {
        fprintf(stderr, "D ");
      } else {
        fprintf(stderr, "%c ", mapa_leer(robot->mapa, i, j));
      }
    }
    fprintf(stderr, " |\n");
  }
  fprintf(stderr, "-------------------\n");

  usleep(200000);
}

Punto *punto_copiar(Punto * a) {
  Punto *b = malloc(sizeof(Punto));
  b->x = a->x;
  b->y = a->y;
  return b;
}

char *char_copiar(char *a) {
  char *b = malloc(sizeof(char));
  *b = *a;
  return b;
}

int ir_a_destino(CeldaInfo ** celdaInfo, Robot robot) {
  GList camino = glist_crear();

  Punto destino = *robot->dest;

  for (Punto p = destino; p.x != -1 && p.y != -1;
       p = celdaInfo[p.x][p.y].padre) {
    camino =
        glist_agregar_inicio(camino, &p, (FuncionCopiadora) punto_copiar);
  }

  for (GNode * node = camino; node != NULL; node = node->next) {
    Punto p = *(Punto *) node->data;
    if (mapa_leer(robot->mapa, p.x, p.y) == '.'
        || mapa_leer(robot->mapa, p.x, p.y) == 's') {
      if (p.y < robot->pos->y) {
        char a = 'L';
        robot->camino =
            glist_agregar_final(robot->camino, &a,
                                (FuncionCopiadora) char_copiar);
      } else if (p.y > robot->pos->y) {
        char a = 'R';
        robot->camino =
            glist_agregar_final(robot->camino, &a,
                                (FuncionCopiadora) char_copiar);
      } else if (p.x < robot->pos->x) {
        char a = 'U';
        robot->camino =
            glist_agregar_final(robot->camino, &a,
                                (FuncionCopiadora) char_copiar);
      } else if (p.x > robot->pos->x) {
        char a = 'D';
        robot->camino =
            glist_agregar_final(robot->camino, &a,
                                (FuncionCopiadora) char_copiar);
      }
      robot->pos->x = p.x;
      robot->pos->y = p.y;

    } else {
      glist_destruir(camino, free);
      return 0;
    }
    imprimir_celdaInfo(celdaInfo, mapa_num_filas(robot->mapa),
                       mapa_num_columnas(robot->mapa));
    imprimir_mapa(robot);
  }

  glist_destruir(camino, free);
  return 1;
}

int max(int *arr) {
  int max = arr[0];
  for (int i = 1; i < 4; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

int usar_sensor(Robot robot) {
  // Enviar la posición actual del robot para usar el sensor
  printf("? %d %d\n", robot->pos->x, robot->pos->y);
  fflush(stdout);

  mapa_escribir(robot->mapa, robot->pos->x, robot->pos->y, 's');

  int cambios = 0;
  int distancias[4];

  scanf("%d %d %d %d", &distancias[0], &distancias[1], &distancias[2],
        &distancias[3]);

  size_t num_filas = mapa_num_filas(robot->mapa);
  size_t num_columnas = mapa_num_columnas(robot->mapa);

  int dx[4] = { -1, 1, 0, 0 };
  int dy[4] = { 0, 0, -1, 1 };
  char marca = '.';
  char obstaculo = '#';

  for (int i = 0; i < 4; i++) {
    int d = distancias[i];

    // Actualizar posiciones en la dirección correspondiente
    for (int j = 1; j < d; j++) {
      int nuevo_x = robot->pos->x + j * dx[i];
      int nuevo_y = robot->pos->y + j * dy[i];

      if (nuevo_x >= 0 && (size_t) nuevo_x < num_filas && nuevo_y >= 0
          && (size_t) nuevo_y < num_columnas) {
        if (mapa_leer(robot->mapa, nuevo_x, nuevo_y) == '?') {
          cambios++;
          mapa_escribir(robot->mapa, nuevo_x, nuevo_y, marca);
        }
      }
    }

    // Marcar el obstáculo si está dentro del rango del sensor
    if (d < max(distancias)) {
      int obstaculo_x = robot->pos->x + d * dx[i];
      int obstaculo_y = robot->pos->y + d * dy[i];

      if (obstaculo_x >= 0 && (size_t) obstaculo_x < num_filas
          && obstaculo_y >= 0 && (size_t) obstaculo_y < num_columnas) {
        mapa_escribir(robot->mapa, obstaculo_x, obstaculo_y, obstaculo);
      }
    }
  }

  return cambios;
}

int comparar_nodos(Nodo nodoA, Nodo nodoB) {
  return nodoB->costo - nodoA->costo;
}

#define UNUSED(x) (void)(x)

void no_hacer_nada(Nodo a) {
  UNUSED(a);
}

unsigned int distancia_manhattan(Punto a, Punto b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

int calcular_ruta(Robot robot) {

  usar_sensor(robot);

  Punto inicio = *robot->pos;
  Punto destino = *robot->dest;

  int N = mapa_num_filas(robot->mapa);
  int M = mapa_num_columnas(robot->mapa);

  ColaPrioridad cola =
      cola_prioridad_crear(N * M, (FuncionComparadora) comparar_nodos,
                           (FuncionDestructora) no_hacer_nada);

  CeldaInfo **celdaInfo = inicializarCeldaInfo(N, M);

  // Inicialización del nodo de inicio
  celdaInfo[inicio.x][inicio.y].costo = 0;
  celdaInfo[inicio.x][inicio.y].padre = (Punto) {
  -1, -1};                      // Nodo inicial sin padre
  Nodo nodoInicio = malloc(sizeof(_Nodo));
  nodoInicio->costo = 0;
  nodoInicio->pos = inicio;

  cola_prioridad_insertar(cola, nodoInicio);

  Nodo nodo = cola_prioridad_maximo(cola);
  int llegoADestino = 0;

  while (!cola_prioridad_es_vacia(cola) && !llegoADestino) {

    nodo = cola_prioridad_maximo(cola);
    cola_prioridad_eliminar_maximo(cola);

    // Actualiza vecinos
    int dx[4] = { 0, 0, -1, 1 };
    int dy[4] = { -1, 1, 0, 0 };
    for (int i = 0; i < 4; i++) {
      int nx = nodo->pos.x + dx[i];
      int ny = nodo->pos.y + dy[i];
      if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
        char celda = mapa_leer(robot->mapa, nx, ny);
        if (celda != '#') {
          int nuevoCosto =
              nodo->costo + 1 + distancia_manhattan(destino, (Punto) { nx,
                                                    ny }) + (celda ==
                                                             '?' ? 1000 :
                                                             0);

          if (nuevoCosto < celdaInfo[nx][ny].costo) {
            celdaInfo[nx][ny].costo = nuevoCosto;
            celdaInfo[nx][ny].padre = nodo->pos;
            Nodo vecino = malloc(sizeof(_Nodo));
            vecino->costo = nuevoCosto;
            vecino->pos = (Punto) {
            nx, ny};

            cola_prioridad_insertar(cola, vecino);
          }
        } else {
          celdaInfo[nx][ny].costo = INT_MAX;
          celdaInfo[nx][ny].padre = (Punto) {
          -1, -1};              // Indica que no hay predecesor
        }
      }
    }

    llegoADestino = nodo->pos.x == destino.x && nodo->pos.y == destino.y;
    free(nodo);
  }


  while (!cola_prioridad_es_vacia(cola)) {
    Nodo nodo = cola_prioridad_maximo(cola);
    cola_prioridad_eliminar_maximo(cola);
    free(nodo);
  }

  cola_prioridad_destruir(cola);

  // Verifica si siguiendo la ruta calculada se llega al destino o se descubre algun obstaculo
  int ret = !ir_a_destino(celdaInfo, robot);

  liberarCeldaInfo(celdaInfo, N);

  return ret;
}





int main() {
  int N, M, sensor_size;
  Punto pos, dest;
  scanf("%d%d%d", &N, &M, &sensor_size);
  scanf("%d%d", &pos.x, &pos.y);
  scanf("%d%d", &dest.x, &dest.y);

  Robot robot = robot_crear(pos, dest, N, M);

  while (calcular_ruta(robot));

  printf("! ");
  glist_recorrer(robot->camino, (FuncionVisitante) imprimir_char);
  printf("\n");

  fflush(stdout);

  robot_destruir(robot);

  return 0;
}
