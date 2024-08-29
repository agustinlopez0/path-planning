#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "matriz.h"
#include <unistd.h>
#include "colaprioridad.h"

typedef struct {
  int x, y;
} Punto;


typedef struct {
  Punto *pos;
  Punto *dest;
  int sensor;
  Matriz *mapa;
  char *camino;
} _Robot;

typedef _Robot *Robot;

void robot_destruir(Robot robot) {
  free(robot->pos);
  free(robot->dest);
  free(robot->camino);
  matriz_destruir(robot->mapa);
  free(robot);
}


void robot_set_mapa(Robot robot) {
  size_t n = matriz_num_filas(robot->mapa);
  size_t m = matriz_num_columnas(robot->mapa);
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++)
      matriz_escribir(robot->mapa, i, j, '?');
  matriz_escribir(robot->mapa, robot->pos->x, robot->pos->y, '.');
  matriz_escribir(robot->mapa, robot->dest->x, robot->dest->y, '.');
}

void imprimir_robot(Robot robot) {
  fprintf(stderr, "Robot: [%d] (%d, %d) -> (%d, %d)\n", robot->sensor,
          robot->pos->x, robot->pos->y, robot->dest->x, robot->dest->y);
}
Robot robot_crear(Punto pos, Punto dest, int sensor, int N, int M) {
  Robot robot = malloc(sizeof(_Robot));
  robot->pos = malloc(sizeof(Punto));
  robot->pos->x = pos.x;
  robot->pos->y = pos.y;

  robot->dest = malloc(sizeof(Punto));
  robot->dest->x = dest.x;
  robot->dest->y = dest.y;

  robot->camino = malloc(1000 * sizeof(char));
  robot->camino[0] = '\0';

  robot->sensor = sensor;

  robot->mapa = matriz_crear(N, M);
  robot_set_mapa(robot);

  return robot;
}

typedef struct {
  unsigned int costo;
  int prioridad;
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

int ir_a_destino(CeldaInfo ** celdaInfo, Robot robot) {
  fprintf(stderr, "ir_a_destino\n");
  Punto camino[25];
  int longitud = 0;
  Punto destino = *robot->dest;
  for (Punto p = destino; p.x != -1 && p.y != -1;
       p = celdaInfo[p.x][p.y].padre) {
    camino[longitud++] = p;
  }

  for (int i = longitud - 1; i >= 0; i--) {
    Punto *p = malloc(sizeof(Punto));
    p->x = camino[i].x;
    p->y = camino[i].y;
    if (matriz_leer(robot->mapa, p->x, p->y) == '.'
        || matriz_leer(robot->mapa, p->x, p->y) == 's') {
      // Si la celda a la que me muevo esta a la izquierda agrego una 'L' al camino
      if (p->y < robot->pos->y) {
        strcat(robot->camino, "L");
      } else if (p->y > robot->pos->y) {
        strcat(robot->camino, "R");
      } else if (p->x < robot->pos->x) {
        strcat(robot->camino, "U");
      } else if (p->x > robot->pos->x) {
        strcat(robot->camino, "D");
      }
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
    int distancias[4];
    // Leer las distancias desde el sensor
    scanf("%d %d %d %d", &distancias[0], &distancias[1], &distancias[2], &distancias[3]);
    fprintf(stderr, "usar_sensor (%d, %d) %d %d %d %d\n",
            robot->pos->x, robot->pos->y, distancias[0], distancias[1], distancias[2], distancias[3]);

    size_t num_filas = matriz_num_filas(robot->mapa);
    size_t num_columnas = matriz_num_columnas(robot->mapa);

    int dx[4] = { -1, 1, 0, 0 };  // Movimiento en filas (arriba, abajo, izquierda, derecha)
    int dy[4] = { 0, 0, -1, 1 };  // Movimiento en columnas
    char marca = '.';              // Marca para espacios libres
    char obstaculo = '#';          // Marca para obstáculos

    for (int i = 0; i < 4; i++) {
        int d = distancias[i];
        int x = robot->pos->x + dx[i];
        int y = robot->pos->y + dy[i];

        // Actualizar posiciones en la dirección correspondiente
        for (int j = 1; j < d; j++) {
            int nuevo_x = robot->pos->x + j * dx[i];
            int nuevo_y = robot->pos->y + j * dy[i];

            if (nuevo_x >= 0 && nuevo_x < num_filas && nuevo_y >= 0 && nuevo_y < num_columnas) {
                if (matriz_leer(robot->mapa, nuevo_x, nuevo_y) == '?') {
                    cambios++;
                    matriz_escribir(robot->mapa, nuevo_x, nuevo_y, marca);
                }
            }
        }

        // Marcar el obstáculo si está dentro del rango del sensor
        if (d <= robot->sensor) {
            int obstaculo_x = robot->pos->x + d * dx[i];
            int obstaculo_y = robot->pos->y + d * dy[i];

            if (obstaculo_x >= 0 && obstaculo_x < num_filas && obstaculo_y >= 0 && obstaculo_y < num_columnas) {
                matriz_escribir(robot->mapa, obstaculo_x, obstaculo_y, obstaculo);
            }
        }
    }

    // Imprimir el mapa actualizado
    imprimir_mapa(robot);
    return cambios;
}


// comparar_nodos(a, b) > 0 => a->prioridad < b->prioridad

int comparar_nodos(Nodo nodoA, Nodo nodoB) {
  return nodoB->prioridad - nodoA->prioridad;
}

void no_hacer_nada(Nodo a) {
  // No hacer nada
}

int calcular_ruta(Robot robot) {
  Punto inicio = *robot->pos;
  Punto destino = *robot->dest;

  int N = matriz_num_filas(robot->mapa);
  int M = matriz_num_columnas(robot->mapa);

  ColaPrioridad cola =
      cola_prioridad_crear(N * M, (FuncionComparadora) comparar_nodos,
                           (FuncionDestructora) no_hacer_nada);

  CeldaInfo **celdaInfo;
  inicializarCeldaInfo(&celdaInfo, N, M);

  // Inicialización de celdaInfo
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      celdaInfo[i][j].costo = INT_MAX;
      celdaInfo[i][j].padre = (Punto) {
      -1, -1};                  // Indica que no hay predecesor
    }
  }

  // Inicialización del nodo de inicio
  celdaInfo[inicio.x][inicio.y].costo = 0;
  celdaInfo[inicio.x][inicio.y].padre = (Punto) {
  -1, -1};                      // Nodo inicial sin padre
  Nodo nodoInicio = malloc(sizeof(_Nodo));
  nodoInicio->costo = 0;
  nodoInicio->prioridad = 0;
  nodoInicio->pos = inicio;

  cola_prioridad_insertar(cola, nodoInicio);

  Nodo nodo = cola_prioridad_maximo(cola);

  while (cola_prioridad_es_vacia(cola) == 0
         && !(nodo->pos.x == destino.x && nodo->pos.y == destino.y)) {
    cola_prioridad_eliminar_maximo(cola);

    // Actualiza vecinos
    int dx[4] = { 0, 0, -1, 1 };
    int dy[4] = { -1, 1, 0, 0 };
    for (int i = 0; i < 4; i++) {
      int nx = nodo->pos.x + dx[i];
      int ny = nodo->pos.y + dy[i];
      if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
        char celda = matriz_leer(robot->mapa, nx, ny);
        if (celda != '#') {
          int distanciaEstimado =
              abs(destino.x - nx) + abs(destino.y - ny);
          int nuevoCosto = nodo->costo + 1 + distanciaEstimado + (celda == '?' ? 1000 : 0);        // Costo base uniforme

          if (nuevoCosto < celdaInfo[nx][ny].costo) {
            celdaInfo[nx][ny].costo = nuevoCosto;
            celdaInfo[nx][ny].padre = nodo->pos;        // Establece el predecesor
            Nodo vecino = malloc(sizeof(_Nodo));
            vecino->costo = nuevoCosto;
            vecino->prioridad = nuevoCosto;
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
    nodo = cola_prioridad_maximo(cola);
  }

  // Imprime el estado actual del mapa (para depuración)
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      fprintf(stderr, "(%10d {%2d, %2d}) |", celdaInfo[i][j].costo,
              celdaInfo[i][j].padre.x, celdaInfo[i][j].padre.y);
    }
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "\n\n");

  cola_prioridad_destruir(cola);        // Liberar memoria de cola
  if (ir_a_destino(celdaInfo, robot)) { // Si el camino encontrado es correcto
    liberarCeldaInfo(celdaInfo, N);     // Liberar memoria de celdaInfo

    return 0;
  } else {                      // Si el camino encontrado pasa por algún obstáculo
    usar_sensor(robot);
    liberarCeldaInfo(celdaInfo, N);     // Liberar memoria de celdaInfo
    return 1;
  }
}





int main() {

  int N, M, d;
  Punto pos, dest;

  scanf("%d%d%d", &N, &M, &d);
  scanf("%d%d", &pos.x, &pos.y);
  scanf("%d%d", &dest.x, &dest.y);

  Robot robot = robot_crear(pos, dest, d, N, M);

  usar_sensor(robot);

  while (calcular_ruta(robot));

  fprintf(stderr, "! %s\n", robot->camino);
  printf("! %s\n", robot->camino);
  
  robot_destruir(robot);

  return 0;
}
