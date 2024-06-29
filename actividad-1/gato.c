  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include "queue.h"

  #define MAX 100

  typedef struct {
      int i, j;
  } Punto;

  typedef enum {
      LEFT,
      RIGHT,
      UP,
      DOWN
  } Direccion;

  typedef struct {
      Punto pos;
      Punto dest;
  } _Robot;

  typedef _Robot *Robot;

  typedef struct {
      char **coord;
      int ancho, alto;
  } _Mapa;

  typedef _Mapa *Mapa;

  typedef struct {
      Robot robot;
  } RobotWrapper;

  // Verifica si una posición es válida
  bool esValido(Mapa mapa, int x, int y) {
      return (x >= 0 && x < mapa->alto && y >= 0 && y < mapa->ancho && mapa->coord[x][y] == '.');
  }

  // Función para reconstruir el camino desde el objetivo hasta el inicio
  void reconstruirCamino(Punto predecesores[MAX][MAX], Punto inicio, Punto objetivo) {
      Punto actual = objetivo;
      printf("Camino:\n");
      while (actual.i != inicio.i || actual.j != inicio.j) {
          printf("(%d, %d) <- ", actual.i, actual.j);
          actual = predecesores[actual.i][actual.j];
      }
      printf("(%d, %d)\n", inicio.i, inicio.j);
  }

  // Función de copia para usar con la cola
  void* copiarRobot(void* data) {
      RobotWrapper* newRobot = malloc(sizeof(RobotWrapper));
      newRobot->robot = malloc(sizeof(_Robot));
      newRobot->robot->pos = ((RobotWrapper*)data)->robot->pos;
      newRobot->robot->dest = ((RobotWrapper*)data)->robot->dest;
      return newRobot;
  }

  // Función destructora para usar con la cola
  void destruirRobot(void* data) {
      // free(((RobotWrapper*)data)->robot);
      // free(data);
  }


  // Función principal para encontrar el camino
  void encontrarCamino(Mapa mapa, Robot inicio, Punto objetivo) {
      int movimientos[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
      Queue queue = cola_crear();
      bool visitados[MAX][MAX] = {false};
      Punto predecesores[MAX][MAX];

      RobotWrapper inicioWrapper = {inicio};
      cola_encolar(queue, &inicioWrapper, copiarRobot);
      visitados[inicio->pos.i][inicio->pos.j] = true;

      while (!cola_es_vacia(queue)) {
          RobotWrapper* actualWrapper = (RobotWrapper*)cola_inicio(queue);
          Robot actual = actualWrapper->robot;
          cola_desencolar(queue, destruirRobot);

          if (actual->pos.i == objetivo.i && actual->pos.j == objetivo.j) {
              reconstruirCamino(predecesores, inicio->pos, objetivo);
              cola_destruir(queue, destruirRobot);
              return;
          }

          for (int i = 0; i < 4; i++) {
              int nuevo_i = actual->pos.i + movimientos[i][0];
              int nuevo_j = actual->pos.j + movimientos[i][1];

              if (esValido(mapa, nuevo_i, nuevo_j) && !visitados[nuevo_i][nuevo_j]) {
                  Robot nuevoRobot = malloc(sizeof(_Robot));
                  nuevoRobot->pos.i = nuevo_i;
                  nuevoRobot->pos.j = nuevo_j;
                  nuevoRobot->dest = actual->dest;

                  RobotWrapper nuevaRobotWrapper = {nuevoRobot};
                  cola_encolar(queue, &nuevaRobotWrapper, copiarRobot);
                  visitados[nuevo_i][nuevo_j] = true;
                  predecesores[nuevo_i][nuevo_j] = actual->pos;
              }
          }
      }

      printf("No se encontró camino\n");
      cola_destruir(queue, destruirRobot);
  }

  int main() {
      char *tablero_data[] = {
          ".#..#",
          "....#",
          "##.##",
          "#....",
          "#..#.",
          "####."
      };
      
      Mapa mapa = malloc(sizeof(_Mapa));
      mapa->ancho = 5;
      mapa->alto = 6;
      mapa->coord = malloc(mapa->alto * sizeof(char *));
      for (int i = 0; i < mapa->alto; i++) {
          mapa->coord[i] = tablero_data[i];
      }

      Robot inicio = malloc(sizeof(_Robot));
      inicio->pos.i = 0;
      inicio->pos.j = 0;
      inicio->dest.i = 5;
      inicio->dest.j = 4;

      encontrarCamino(mapa, inicio, inicio->dest);

      // Liberar la memoria del mapa y el robot
      free(mapa->coord);
      free(mapa);
      free(inicio);

      return 0;
  }
