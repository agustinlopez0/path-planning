#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "simulacion.h"
#include "leerArchivo.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Uso: %s <archivo de entrada>\n", argv[0]);
    return 1;
  }

  char *nombreArchivo = argv[1];
  FileData fileData = leer_archivo(nombreArchivo);

  if (!fileData)
    return 1;

  Robot robot = robot_crear(fileData->posRobot, fileData->destRobot);
  Mapa mapa = mapa_crear(fileData->alto, fileData->ancho, fileData->coord);
  free(fileData);

  printf("Recorrido: ");
  robot_ir_a_destino(robot, mapa);
  puts("");

  printf("El robot %s llegó a su destino\n",
         robot_en_destino(robot) ? "sí" : "no");

  mapa_destruir(mapa);
  robot_destruir(robot);

  return 0;
}

