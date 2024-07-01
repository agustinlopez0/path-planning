#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "simulacion.h"

#define MAX_BUFFER_SIZE 100

typedef struct {
  size_t alto, ancho;
  Punto posRobot;
  Punto destRobot;
  char **coord;
} FileData;

void filedata_destruir(FileData *fileData){
  punto_destruir(fileData->posRobot);
  punto_destruir(fileData->destRobot);
  for(unsigned int i = 0; i < fileData->alto; i++)
    free(fileData->coord[i]);
  free(fileData->coord);
  free(fileData);
}

/**
 * Si la cadena esta conformada unicamente por '#' y '.' retorna 1,
 *   retorna 0 en caso contrario
 */
int es_cadena_valida(const char *cadena) {
  while (*cadena) {
    if (*cadena != '#' && *cadena != '.')
      return 0;
    cadena++;
  }
  return 1;
}

/**
 * Retorna la cantidad de espacios de una cadena
 */
int cantidad_espacios(const char *cadena) {
  int cont = 0;
  while (*cadena) {
    if (*cadena == ' ')
      cont++;
    cadena++;
  }
  return cont;
}

int validar_formato(FILE * f, FileData * fileData) {
  char linea[MAX_BUFFER_SIZE];

  // Validar la primera línea
  char checkFinal;
  if (fgets(linea, MAX_BUFFER_SIZE, f) == NULL) {
    fprintf(stderr, "Error de lectura en linea: 1\n");
    return 1;
  }
  if (cantidad_espacios(linea) != 2
      || sscanf(linea, "%ld %ld %c%c", &fileData->alto, &fileData->ancho,
                &checkFinal, &checkFinal) != 4 || checkFinal != '\n') {
    fprintf(stderr, "Error: Formato de archivo inválido en linea: 1\n");
    return 1;
  }
  // Validar la segunda línea
  int posI, posJ;
  if (fgets(linea, MAX_BUFFER_SIZE, f) == NULL) {
    fprintf(stderr, "Error de lectura en linea: 2\n");
    return 1;
  }
  if (cantidad_espacios(linea) != 1
      || sscanf(linea, "%d %d%c", &posI, &posJ, &checkFinal) != 3
      || checkFinal != '\n') {
    fprintf(stderr, "Error: Formato de archivo inválido en linea: 2\n");
    return 1;
  }
  fileData->posRobot = punto_crear(posI, posJ);

  // Validar la tercera línea
  int destI, destJ;
  if (fgets(linea, MAX_BUFFER_SIZE, f) == NULL) {
    fprintf(stderr, "Error de lectura en linea: 3\n");
    return 1;
  }
  if (cantidad_espacios(linea) != 1
      || sscanf(linea, "%d %d%c", &destI, &destJ, &checkFinal) != 3
      || checkFinal != '\n') {
    fprintf(stderr, "Error: Formato de archivo inválido en linea: 3\n");
    return 1;
  }
  fileData->destRobot = punto_crear(destI, destJ);

  return 0;
}

FileData *leer_archivo(const char *nombre_archivo) {
  FILE *f = fopen(nombre_archivo, "r");
  if (f == NULL) {
    fprintf(stderr, "Error: No se pudo abrir el archivo %s\n",
            nombre_archivo);
    return NULL;
  }


  FileData *fileData = malloc(sizeof(FileData));
  if (fileData == NULL) {
    fprintf(stderr, "Error: No se pudo asignar memoria %s\n",
            nombre_archivo);
    return NULL;
  }

  if (validar_formato(f, fileData) != 0) {
    free(fileData);
    fclose(f);
    return NULL;
  }

  fileData->coord = malloc(sizeof(char *) * fileData->alto);
  if (fileData->coord == NULL) {
    fprintf(stderr, "Error: No se pudo asignar memoria %s\n",
            nombre_archivo);
    return NULL;
  }

  for (unsigned int i = 0; i < fileData->alto; i++) {
    fileData->coord[i] = malloc(sizeof(char) * (fileData->ancho + 1));
    if (fileData->coord[i] == NULL) {
      fprintf(stderr, "Error: No se pudo asignar memoria %s\n",
              nombre_archivo);
      return NULL;
    }

    if (fscanf(f, "%s", fileData->coord[i]) != 1
        || strlen(fileData->coord[i]) != fileData->ancho
        || !es_cadena_valida(fileData->coord[i])) {
      fprintf(stderr, "Error: Formato de archivo inválido en linea: %d\n",
              i + 4);
      for (unsigned int j = 0; j <= i; j++)
        free(fileData->coord[j]);
      free(fileData->coord);
      punto_destruir(fileData->posRobot);
      punto_destruir(fileData->destRobot);
      free(fileData);
      fclose(f);
      return NULL;
    }
  }

  if (fileData->coord[fileData->posRobot->i][fileData->posRobot->j] == '#'
      || (size_t) fileData->posRobot->i >= fileData->alto
      || (size_t) fileData->posRobot->j >= fileData->ancho) {
    fprintf(stderr, "El robot se encuentra sobre un obstaculo\n");
    filedata_destruir(fileData);
    fclose(f);
    return NULL;
  }
  if (fileData->coord[fileData->destRobot->i][fileData->destRobot->j] ==
      '#' || (size_t) fileData->destRobot->i >= fileData->alto
      || (size_t) fileData->destRobot->j >= fileData->ancho) {
    fprintf(stderr,
            "El destino del robot se encuentra sobre un obstaculo\n");
    filedata_destruir(fileData);
    fclose(f);
    return NULL;
  }

  fclose(f);
  return fileData;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Uso: %s <archivo de entrada>\n", argv[0]);
    return 1;
  }

  FileData *fileData = leer_archivo(argv[1]);
  if (fileData == NULL) {
    return 1;
  }

  Robot robot = robot_crear(fileData->posRobot, fileData->destRobot);
  Mapa mapa = mapa_crear(fileData->alto, fileData->ancho, fileData->coord);
  free(fileData);

  mostrar_robot_mapa(robot, mapa);

  puts("Recorrido:");
  robot_ir_a_destino(robot, mapa);
  puts("");

  mapa_destruir(mapa);
  robot_destruir(robot);

  return 0;
}
