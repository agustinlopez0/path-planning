#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "mapa.h"
#include "colaprioridad.h"
#include "glist.h"
#include <unistd.h>

typedef struct {
  int x, y;
} Punto;

/**
 * @brief Estructura que representa un robot y la información necesaria para su funcionamiento.
 * 
 * @param pos Posición actual del robot.
 * @param dest Posición destino del robot.
 * @param mapa Matriz de caracteres que representa al mapa en el que se encuentra el robot.
 * @param camino Lista de caracteres que representa el camino que siguio el robot desde su posicion inicial.
 */
typedef struct {
  Punto *pos;
  Punto *dest;
  Mapa *mapa;
  GList camino;
} _Robot;

typedef _Robot *Robot;

/**
 * @brief Estructura que representa un nodo de la cola de prioridad.
 * 
 * @param costo Costo del nodo.
 * @param pos Posición del nodo.
 */
typedef struct {
  unsigned int costo;
  Punto pos;
} _Nodo;

typedef _Nodo *Nodo;

/**
 * @brief Estructura que representa una celda del mapa con información para calcular la ruta al destino.
 * 
 * @param padre Posición del nodo anterior en el recorrido del robot en el camino optimo a la posicion actual
 * @param costo Costo calculado para llegar a la celda.
 */
typedef struct {
  Punto padre;
  int costo;
} CeldaInfo;

/**
 * @brief Crea un nuevo robot con los campos inicializados.
 * 
 * @param pos Posición inicial del robot.
 * @param dest Posición destino del robot.
 * @param N Número de filas del mapa.
 * @param M Número de columnas del mapa.
 * @return Robot creado.
 */
Robot robot_crear(Punto pos, Punto dest, int N, int M);

/** 
 * @brief Crea una matriz de CeldaInfo con los costos y padres inicializados.
 * 
 * @param N Número de filas del mapa.
 * @param M Número de columnas del mapa.
 * @return CeldaInfo** CeldaInfo inicializada.
 */
CeldaInfo **celda_info_crear(int N, int M);

/** 
 * @brief Destruye y libera la memoria de una matriz de celdaInfo.
 * 
 * @param celdaInfo CeldaInfo a liberar.
 * @param N Número de filas del mapa.
 */
void celda_info_destruir(CeldaInfo ** celdaInfo, int N);

/** 
 * @brief Destruye un robot y libera la memoria.
 * 
 * @param robot Robot a destruir.
 */
void robot_destruir(Robot robot);

/** 
 * @brief Una vez calculado los costos, se mueve hacia el destino por la ruta calculada hasta chocar con un obstáculo o una celda desconocida.
 * 
 * @param celdaInfo CeldaInfo del robot.
 * @param robot Robot a mover.
 * @return int 1 si se llegó al destino, 0 en caso contrario.
 */
int ir_a_destino(CeldaInfo ** celdaInfo, Robot robot);

/** 
 * @brief Usa el sensor del robot y actualiza el mapa cargado en memoria.
 * 
 * @param robot Robot a usar el sensor.
 * @return int Cambios realizados.
 */
int usar_sensor(Robot robot);

/** 
 * @brief Calcula la ruta del robot y se acerca lo máximo posible al objetivo sin entrar en celdas desconocidas (ni obviamente obstaculos).
 * 
 * @param robot Robot a calcular la ruta.
 * @return int 1 si se debe seguir calculando la ruta, 0 en caso contrario.
 */
int calcular_ruta(Robot robot);

void imprimir_char(char *a) {
  printf("%c", *a);
}

int main() {
  int N, M, alcanceSensor;
  Punto pos, dest;
  scanf("%d%d%d", &N, &M, &alcanceSensor);
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

// Setea los valores iniciales del mapa de un robot
void robot_set_mapa(Robot robot) {
  size_t n = mapa_num_filas(robot->mapa);
  size_t m = mapa_num_columnas(robot->mapa);
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++)
      mapa_escribir(robot->mapa, i, j, '?');
  mapa_escribir(robot->mapa, robot->pos->x, robot->pos->y, '.');
  mapa_escribir(robot->mapa, robot->dest->x, robot->dest->y, '.');
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

CeldaInfo **celda_info_crear(int N, int M) {
  CeldaInfo **celdaInfo = malloc(N * sizeof(CeldaInfo *));
  for (int i = 0; i < N; i++) {
    celdaInfo[i] = malloc(M * sizeof(CeldaInfo));
    for (int j = 0; j < M; j++) {
      celdaInfo[i][j].costo = INT_MAX;
      celdaInfo[i][j].padre = (Punto) {
      -1, -1};
    }
  }

  return celdaInfo;
}

void celda_info_destruir(CeldaInfo ** celdaInfo, int N) {
  for (int i = 0; i < N; i++) {
    free(celdaInfo[i]);
  }
  free(celdaInfo);
}

void robot_destruir(Robot robot) {
  free(robot->pos);
  free(robot->dest);
  glist_destruir(robot->camino, free);
  mapa_destruir(robot->mapa);
  free(robot);
}

// Funcion que se utiliza para agregar el indicador de dirección al camino
char *char_copiar(char *a) {
  char *b = malloc(sizeof(char));
  *b = *a;
  return b;
}
// Funcion que se utiliza para realizar una copia fisica de un punto
Punto *punto_copiar(Punto * a) {
  Punto *b = malloc(sizeof(Punto));
  b->x = a->x;
  b->y = a->y;
  return b;
}
int ir_a_destino(CeldaInfo ** celdaInfo, Robot robot) {
  GList camino = glist_crear();

  Punto destino = *robot->dest;

  for (Punto p = destino; p.x != -1 && p.y != -1; p = celdaInfo[p.x][p.y].padre) {
    camino = glist_agregar_inicio(camino, &p, (FuncionCopiadora) punto_copiar);
  }

  for (GNode * node = camino; node != NULL; node = node->next) {
    Punto p = *(Punto *) node->data;
    if (mapa_leer(robot->mapa, p.x, p.y) == '.') {
      char a = '-';
      if (p.y < robot->pos->y)
        a = 'L';
      else if (p.y > robot->pos->y)
        a = 'R';
      else if (p.x < robot->pos->x)
        a = 'U';
      else if (p.x > robot->pos->x)
        a = 'D';
      
      if(a == 'L' || a == 'R' || a == 'U' || a == 'D')
        robot->camino = glist_agregar_final(robot->camino, &a, (FuncionCopiadora) char_copiar);
      robot->pos->x = p.x;
      robot->pos->y = p.y;

    } else {
      glist_destruir(camino, free);
      return 0;
    }
  }

  glist_destruir(camino, free);
  return 1;
}

// Retorna el máximo de un arreglo de 4 enteros
int sensor_max(int *arr) {
  int max = arr[0];
  for (int i = 1; i < 4; i++)
    if (arr[i] > max)
      max = arr[i];
  return max;
}
int usar_sensor(Robot robot) {
  // Enviar la posición actual del robot para usar el sensor
  printf("? %d %d\n", robot->pos->x, robot->pos->y);
  fflush(stdout);

  int cambios = 0;
  int distancias[4];

  scanf("%d %d %d %d", &distancias[0], &distancias[1], &distancias[2], &distancias[3]);

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

      if (nuevo_x >= 0 && (size_t) nuevo_x < num_filas && nuevo_y >= 0 && (size_t) nuevo_y < num_columnas) {
        if (mapa_leer(robot->mapa, nuevo_x, nuevo_y) == '?') {
          cambios++;
          mapa_escribir(robot->mapa, nuevo_x, nuevo_y, marca);
        }
      }
    }

    // Marcar el obstáculo si está dentro del rango del sensor
    if (d < sensor_max(distancias)) {
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

unsigned int distancia_manhattan(Punto a, Punto b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}
int comparar_nodos(Nodo nodoA, Nodo nodoB) {
  return nodoB->costo - nodoA->costo;
}
int calcular_ruta(Robot robot) {

  usar_sensor(robot);

  Punto inicio = *robot->pos;
  Punto destino = *robot->dest;

  int N = mapa_num_filas(robot->mapa);
  int M = mapa_num_columnas(robot->mapa);

  ColaPrioridad cola = cola_prioridad_crear(N * M, (FuncionComparadora) comparar_nodos,
                                            NULL);

  CeldaInfo **celdaInfo = celda_info_crear(N, M);

  // Inicialización del nodo de inicio
  celdaInfo[inicio.x][inicio.y].costo = 0;
  celdaInfo[inicio.x][inicio.y].padre = (Punto) {
  -1, -1};                      // Nodo inicial sin padre
  Nodo nodoInicio = malloc(sizeof(_Nodo));
  nodoInicio->costo = 0;
  nodoInicio->pos = inicio;

  cola_prioridad_insertar(cola, nodoInicio);

  Nodo nodo;
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
          int penalizacionCeldaDesconocida = 10 * N * M;
          int nuevoCosto = nodo->costo + 1;
          nuevoCosto += distancia_manhattan(destino, (Punto) {
                                            nx, ny});
          nuevoCosto += (celda == '?' ? penalizacionCeldaDesconocida : 0);

          if (nuevoCosto < celdaInfo[nx][ny].costo) {
            celdaInfo[nx][ny].costo = nuevoCosto;
            celdaInfo[nx][ny].padre = nodo->pos;
            Nodo vecino = malloc(sizeof(_Nodo));
            vecino->costo = nuevoCosto;
            vecino->pos = (Punto) {
            nx, ny};

            cola_prioridad_insertar(cola, vecino);
          }
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

  celda_info_destruir(celdaInfo, N);

  return ret;
}