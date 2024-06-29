#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "robot.h"
#include "mapa.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Uso: %s <nombre_archivo>\n", argv[0]);
    return 1;
  }

  /*Abre el archivo e inicializa mapa y robot con los datos */
  printf("Abriendo archivo: %s\n", argv[1]);
  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[1]);
    return 1;
  }

  Mapa mapa = malloc(sizeof(_Mapa));

  int dummy;
  Punto robotPos, robotDest;
  fscanf(f, "%d %d %d", &mapa->alto, &mapa->ancho, &dummy);
  fscanf(f, "%d %d", &robotPos.i, &robotPos.j);
  fscanf(f, "%d %d", &robotDest.i, &robotDest.j);
  Robot robot = robot_crear(robotPos, robotDest);

  mapa->coord = malloc(sizeof(char *) * mapa->alto);
  for (int i = 0; i < mapa->alto; i++) {
    mapa->coord[i] = malloc(sizeof(char) * (mapa->ancho + 1));
    fscanf(f, "%s", mapa->coord[i]);
  }

  fclose(f);
  /*Una vez cargados los datos cierra el archivo */


  mostrar_robot_mapa(robot, mapa);
  // robot_imprimir(robot);
  // mapa_imprimir(mapa);

  puts("Recorrido:\n");
  robot_ir_a_destino(robot, mapa);
  puts("");
  mapa_destruir(mapa);
  // robot_destruir(robot);


  return 0;
}
