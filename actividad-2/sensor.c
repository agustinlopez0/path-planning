#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 100
// leer_archivo()
// - lee el archivo `data` segun el formato especificado en el trabajo.
// - n, m, max_d, i1, j1, i2 y j2 son parametros de salida. Se corresponden con
//   los valores N, M, D, i1, j1, i2 y j2, respectivamente.
// - Devuelve un arreglo de arreglos con las filas del entorno, o NULL en caso
//   de que el formato sea invalido
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

char** leer_archivo(FILE* data, int* n, int* m, int* max_d, int* i1, int* j1, int* i2, int* j2) {
	// Esta funcion se puede completar usando el lector de archivos que escribio para la actividad 1
  char linea[MAX_BUFFER_SIZE];

  // Validar la primera línea
  char checkFinal;
  if (fgets(linea, MAX_BUFFER_SIZE, data) == NULL) {
    fprintf(stderr, "Error de lectura en linea: 1\n");
    return NULL;
  }

  if (cantidad_espacios(linea) != 2
      || sscanf(linea, "%d %d %d%c", n, m, max_d, &checkFinal) != 4 || checkFinal != '\n') {
    fprintf(stderr, "Error: Formato de archivo inválido en linea: 1\n");
    return NULL;
  }
  // Validar la segunda línea
  if (fgets(linea, MAX_BUFFER_SIZE, data) == NULL) {
    fprintf(stderr, "Error de lectura en linea: 2\n");
    return NULL;
  }
  if (cantidad_espacios(linea) != 1
      || sscanf(linea, "%d %d%c", i1, j1, &checkFinal) != 3
      || checkFinal != '\n') {
    fprintf(stderr, "Error: Formato de archivo inválido en linea: 2\n");
    return NULL;
  }

  // Validar la tercera línea
  if (fgets(linea, MAX_BUFFER_SIZE, data) == NULL) {
    fprintf(stderr, "Error de lectura en linea: 3\n");
    return NULL;
  }
  if (cantidad_espacios(linea) != 1
      || sscanf(linea, "%d %d%c", i2, j2, &checkFinal) != 3
      || checkFinal != '\n') {
    fprintf(stderr, "Error: Formato de archivo inválido en linea: 3\n");
    return NULL;
  }
	//************************************************************** */
  char ** coord = malloc(sizeof(char *) * *n);
  if (coord == NULL) {
    fprintf(stderr, "Error: No se pudo asignar memoria\n");
    return NULL;
  }

 for (int i = 0; i < *n; i++) {
    coord[i] = malloc(sizeof(char) * (*m + 1));
    if (coord[i] == NULL) {
      fprintf(stderr, "Error: No se pudo asignar memoria\n");
      return NULL;
    }

    if (fscanf(data, "%s", coord[i]) != 1
        || strlen(coord[i]) != (size_t)*m
        || !es_cadena_valida(coord[i])) {
      fprintf(stderr, "Error: Formato de archivo inválido en linea: %d\n",
              i + 4);
      for (int j = 0; j <= i; j++)
        free(coord[j]);
      free(coord);
      return NULL;
    }
  }

  if (coord[*i1][*j1] == '#'
      || *i1 >= *n
      || *j1 >= *m) {
    fprintf(stderr, "El robot se encuentra sobre un obstaculo\n");
    return NULL;
  }
  if (coord[*i2][*j2] ==
      '#' || *i2 >= *n
      || *j2 >= *m) {
    fprintf(stderr,
            "El destino del robot se encuentra sobre un obstaculo\n");
    return NULL;
  }
  return coord;
}

// El resto de este archivo no tiene relevancia para el estudiante.

int coordenada_valida(int n, int m, int i, int j) {
	return 0 <= i && i < n && 0 <= j && j < m;
}

int lanzar_rayo(char** mapa, int n, int m, int i, int j, int di, int dj, int max_dist) {
	int dist = 0;
	while (coordenada_valida(n, m, i, j) && mapa[i][j] != '#') {
		dist++;
		i += di; j += dj;
	}
	return dist > max_dist ? max_dist+1 : dist;
}

int correr_sensor(char** mapa, int n, int m, int i, int j, int* d, int max_d) {
	if (!coordenada_valida(n, m, i, j)) return 0;
	d[0] = lanzar_rayo(mapa, n, m, i, j, -1, 0, max_d); // arriba
	d[1] = lanzar_rayo(mapa, n, m, i, j,  1, 0, max_d); // abajo
	d[2] = lanzar_rayo(mapa, n, m, i, j, 0, -1, max_d); // izquierda
	d[3] = lanzar_rayo(mapa, n, m, i, j, 0,  1, max_d); // derecha
	return 1;
}

void caracter_inesperado(char c) {
	fprintf(stderr, "Comando invalido. Caracter inesperado: '%c' (ascii %d)\n", c, (int)c); fflush(stderr);
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Uso: ./sensor <archivo>\n"); fflush(stderr);
		return EXIT_FAILURE;
	}

	FILE* data = fopen(argv[1], "r");
	if (!data) {
		fprintf(stderr, "No existe el archivo\n"); fflush(stderr);
		return EXIT_FAILURE;
	}

	int n, m, max_d;
	int i1, j1;
	int i2, j2;
	char** mapa;
	if ((mapa = leer_archivo(data, &n, &m, &max_d, &i1, &j1, &i2, &j2)) == NULL) {
		fprintf(stderr, "Formato de archivo invalido\n");
		fclose(data);
		return EXIT_FAILURE;
	}
	fclose(data);

	printf("%d %d %d\n", n, m, max_d);
	printf("%d %d\n", i1, j1);
	printf("%d %d\n", i2, j2);
	fflush(stdout);

	// for(int i = 0; i < n; i++){
	// 	fprintf(stderr, "%s\n", mapa[i]);
	// }

	int operaciones = 0;

	while (1) {
		char c = getchar();

		if (isspace(c)) continue;
		else if (c == '?') {

			c = getchar();
			if (c != ' ') caracter_inesperado(c);

			int i, j;
			if (scanf("%d%d", &i, &j) != 2) caracter_inesperado(c);

			operaciones++;
			int d[4] = {};
			correr_sensor(mapa, n, m, i, j, d, max_d);

			// fprintf(stderr, "sensor: ");
			for (int i = 0; i < 4; ++i) {
				// fprintf(stderr, "%d%c", d[i], i == 3 ? '\n' : ' ');
				printf("%d%c", d[i], i == 3 ? '\n' : ' ');
			}
			// fprintf(stderr, "\n");
			fflush(stdout);

		} else if (c == '!') {

			c = getchar();
			if (c != ' ') caracter_inesperado(c);

			int distancia = 0;
			int i = i1, j = j1;
			while (1) {
				distancia++;
				c = getchar();
				/**/ if (c == 'U') i -= 1;
				else if (c == 'D') i += 1;
				else if (c == 'L') j -= 1;
				else if (c == 'R') j += 1;
				else if (c == '\n') break;
				else caracter_inesperado(c);
			}

			if (i == i2 && j == j2) {
				fprintf(stderr, "El robot llego a su destino.\n");
				fprintf(stderr, "Operaciones realizadas: %d, Distancia recorrida: %d\n", operaciones, distancia);
				return EXIT_SUCCESS;
			} else {
				fprintf(stderr, "El robot no llego a su destino. Posicion final: (%d, %d).\n", i, j);
				return EXIT_FAILURE;
			}

		} else {
			caracter_inesperado(c);
		}
	}
}
