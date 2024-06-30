#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "simulacion.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Uso: %s <archivo de entrada>\n", argv[0]);
    return 1;
  }

  printf("Abriendo archivo: %s\n", argv[1]);
  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[1]);
    return 1;
  }

  Mapa mapa = malloc(sizeof(_Mapa));

  int dummy;
  Punto robotPos, robotDest;

  // Verificar que se puedan leer los primeros tres números
  if (fscanf(f, "%ld %ld %d", &mapa->alto, &mapa->ancho, &dummy) != 3) {
    fprintf(stderr, "Formato de archivo inválido en la primera línea\n");
    fclose(f);
    return 1;
  }
  // Verificar que se puedan leer los siguientes dos puntos
  if (fscanf(f, "%d %d", &robotPos.i, &robotPos.j) != 2) {
    fprintf(stderr, "Formato de archivo inválido en la segunda línea\n");
    fclose(f);
    return 1;
  }

  if (fscanf(f, "%d %d", &robotDest.i, &robotDest.j) != 2) {
    fprintf(stderr, "Formato de archivo inválido en la tercera línea\n");
    fclose(f);
    return 1;
  }

  Robot robot = robot_crear(robotPos, robotDest);

  mapa->coord = malloc(sizeof(char *) * mapa->alto);
  for (unsigned int i = 0; i < mapa->alto; i++) {
    mapa->coord[i] = malloc(sizeof(char) * (mapa->ancho + 1));
    assert(mapa->coord[i] != NULL);

    if (fscanf(f, "%s", mapa->coord[i]) != 1) {
      fprintf(stderr, "Formato de archivo inválido en la línea %d\n",
              i + 4);
      fclose(f);
      return 1;
    }
    // Verificar que la línea tenga la longitud correcta
    if (strlen(mapa->coord[i]) != mapa->ancho) {
      fprintf(stderr, "Longitud de fila incorrecta en la línea %d\n",
              i + 4);
      fclose(f);
      return 1;
    }
  }

  mostrar_robot_mapa(robot, mapa);

  fclose(f);

  puts("Recorrido:");
  robot_ir_a_destino(robot, mapa);
  puts("");
  mapa_destruir(mapa);
  robot_destruir(robot);


  return 0;
}
