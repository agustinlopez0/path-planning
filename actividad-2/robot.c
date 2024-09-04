#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "mapa.h"
#include "colaprioridad.h"
#include "dglist.h"
#include <unistd.h>
#include "robotAux.h"

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
 * @brief Una vez calculado los costos, se mueve hacia el destino por la ruta calculada hasta chocar con un obstáculo o una celda desconocida.
 * 
 * @param celdaInfo CeldaInfo del robot.
 * @param robot Robot a mover.
 * @return int 1 si se llegó al destino, 0 en caso contrario.
 */
int ir_a_destino(CeldaInfo ** celdaInfo, Robot robot);

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
  dglist_recorrer(robot->camino, (FuncionVisitante) imprimir_char);
  printf("\n");
  fflush(stdout);

  robot_destruir(robot);
  return 0;
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
  DGList camino = dglist_crear();

  Punto destino = *robot->dest;

  for (Punto p = destino; p.x != -1 && p.y != -1; p = celdaInfo[p.x][p.y].padre)
    dglist_agregar_inicio(camino, &p, (FuncionCopiadora) punto_copiar);


  for (GNode * node = camino->first; node != NULL; node = node->next) {
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
        dglist_agregar_final(robot->camino, &a, (FuncionCopiadora) char_copiar);
      robot->pos->x = p.x;
      robot->pos->y = p.y;

    } else {
      dglist_destruir(camino, free);

      return 0;
    }
  }

  dglist_destruir(camino, free);
  return 1;
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