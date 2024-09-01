/**
 * @file main.c
 * @brief Programa principal para la simulación de navegación de un robot en un mapa.
 *
 * Este programa lee un archivo de configuración que describe las dimensiones del mapa,
 * la posición inicial y destino del robot, así como la disposición del mapa con obstáculos
 * y caminos libres. Luego, crea un robot y un mapa basados en estos datos y simula la
 * navegación del robot hasta alcanzar su destino.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "simulacion.h"

#define MAX_BUFFER_SIZE 100

/**
 * @brief Estructura que almacena los datos leídos desde el archivo de configuración.
 */
typedef struct {
  size_t alto, ancho;
  Punto posRobot;
  Punto destRobot;
  char **coord;
} _FileData;

typedef _FileData *FileData;

/**
 * @brief Lee un archivo de configuración y carga los datos en una estructura FileData.
 *
 * @param nombre_archivo Nombre del archivo de configuración.
 * @return Puntero a la estructura FileData creada con los datos del archivo, o NULL si hay errores.
 */
FileData leer_archivo(const char *nombre_archivo);

/**
 * @brief Libera la memoria asignada a una estructura FileData y sus campos.
 *
 * @param fileData Puntero a la estructura FileData a destruir.
 */
void filedata_destruir(FileData fileData);

/**
 * @brief Verifica si una cadena está compuesta únicamente por caracteres válidos ('#' y '.').
 *
 * @param cadena Cadena a verificar.
 * @return 1 si la cadena es válida, 0 si no lo es.
 */
int es_cadena_valida(const char *cadena);

/**
 * @brief Cuenta la cantidad de espacios en blanco en una cadena.
 *
 * @param cadena Cadena en la que contar los espacios en blanco.
 * @return Número de espacios en blanco encontrados.
 */
int cantidad_espacios(const char *cadena);

/**
 * @brief Valida el formato de un archivo de configuración y carga los datos en una estructura FileData.
 *
 * @param f Puntero al archivo de configuración abierto en modo lectura.
 * @param fileData Estructura donde se almacenarán los datos leídos.
 * @return 1 si el formato es válido y los datos se cargan correctamente, 0 si hay errores.
 */
int validar_formato(FILE * f, FileData fileData);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Uso: %s <archivo de entrada>\n", argv[0]);
    return 1;
  }
  // Leer y validar el archivo de configuración
  char *nombreArchivo = argv[1];
  FileData fileData = leer_archivo(nombreArchivo);

  if (!fileData)
    return 1;

  // Crear el robot y el mapa con los datos del archivo
  Robot robot = robot_crear(fileData->posRobot, fileData->destRobot);
  Mapa mapa = mapa_crear(fileData->alto, fileData->ancho, fileData->coord);
  free(fileData);

  // Mostrar el estado inicial del robot en el mapa
  mostrar_robot_mapa(robot, mapa);

  // Simular el movimiento del robot hacia su destino
  puts("Recorrido:");
  robot_ir_a_destino(robot, mapa);
  puts("");

  mapa_destruir(mapa);
  robot_destruir(robot);

  return 0;
}

void filedata_destruir(FileData fileData) {
  punto_destruir(fileData->posRobot);
  punto_destruir(fileData->destRobot);
  for (unsigned int i = 0; i < fileData->alto; i++)
    free(fileData->coord[i]);
  free(fileData->coord);
  free(fileData);
}

int es_cadena_valida(const char *cadena) {
  while (*cadena) {
    if (*cadena != '#' && *cadena != '.')
      return 0;
    cadena++;
  }
  return 1;
}

int cantidad_espacios(const char *cadena) {
  int cont = 0;
  while (*cadena) {
    if (*cadena == ' ')
      cont++;
    cadena++;
  }
  return cont;
}

int validar_formato(FILE * f, FileData fileData) {
  char linea[MAX_BUFFER_SIZE];

  // Validar la primera línea
  char checkFinal;
  if (fgets(linea, MAX_BUFFER_SIZE, f) == NULL) {
    fprintf(stderr, "Error de lectura en linea: 1\n");
    return 0;
  }

  int dummy;
  if (cantidad_espacios(linea) != 2
      || sscanf(linea, "%ld %ld %d%c", &fileData->alto, &fileData->ancho,
                &dummy, &checkFinal) != 4 || checkFinal != '\n') {
    fprintf(stderr, "Error: Formato de archivo inválido en linea: 1\n");
    return 0;
  }
  // Validar la segunda línea
  int posI, posJ;
  if (fgets(linea, MAX_BUFFER_SIZE, f) == NULL) {
    fprintf(stderr, "Error de lectura en linea: 2\n");
    return 0;
  }

  if (cantidad_espacios(linea) != 1
      || sscanf(linea, "%d %d%c", &posI, &posJ, &checkFinal) != 3
      || checkFinal != '\n') {
    fprintf(stderr, "Error: Formato de archivo inválido en linea: 2\n");
    return 0;
  }

  fileData->posRobot = punto_crear(posI, posJ);

  // Validar la tercera línea
  int destI, destJ;
  if (fgets(linea, MAX_BUFFER_SIZE, f) == NULL) {
    fprintf(stderr, "Error de lectura en linea: 3\n");
    return 0;
  }
  if (cantidad_espacios(linea) != 1
      || sscanf(linea, "%d %d%c", &destI, &destJ, &checkFinal) != 3
      || checkFinal != '\n') {
    fprintf(stderr, "Error: Formato de archivo inválido en linea: 3\n");
    return 0;
  }

  fileData->destRobot = punto_crear(destI, destJ);

  return 1;
}

FileData leer_archivo(const char *nombre_archivo) {
  FILE *f = fopen(nombre_archivo, "r");
  if (f == NULL) {
    fprintf(stderr, "Error: No se pudo abrir el archivo %s\n",
            nombre_archivo);
    return NULL;
  }


  FileData fileData = malloc(sizeof(_FileData));

  if (!validar_formato(f, fileData)) {
    free(fileData);
    fclose(f);
    return NULL;
  }

  fileData->coord = malloc(sizeof(char *) * fileData->alto);

  for (unsigned int i = 0; i < fileData->alto; i++) {
    fileData->coord[i] = malloc(sizeof(char) * (fileData->ancho + 1));

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
