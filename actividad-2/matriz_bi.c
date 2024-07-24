#include "matriz.h"

/*
** Implementacion utilizando un arreglo bidimensional (arreglo de punteros a arreglo)
*/

struct Matriz_ {
  char **elem;
  size_t fil, col;
};


Matriz *matriz_crear(size_t numFilas, size_t numColumnas) {
  Matriz *matriz = malloc(sizeof(Matriz));
  matriz->fil = numFilas;
  matriz->col = numColumnas;
  matriz->elem = malloc(sizeof(char *) * numFilas);

  for (unsigned int i = 0; i < numFilas; i++) {
    matriz->elem[i] = malloc(sizeof(char) * numColumnas);
  }

  // printf("- Matriz de %zux%zu creada -\n", matriz_num_filas(matriz), matriz_num_columnas(matriz));

  return matriz;
}

void matriz_destruir(Matriz * matriz) {
  for (unsigned int i = 0; i < matriz_num_filas(matriz); i++) {
    free(matriz->elem[i]);
  }

  free(matriz->elem);
  free(matriz);

  // printf("- Matriz destruida -\n");
}

char matriz_leer(Matriz * matriz, size_t fil, size_t col) {
  if (fil >= matriz_num_filas(matriz)) {
    fprintf(stderr, "\nmatriz_leer: FILA FUERA DE RANGO (%ld %ld)\n", fil,
            col);
    return 0;
  }
  if (col >= matriz_num_columnas(matriz)) {
    fprintf(stderr, "\nmatriz_leer: COLUMNA FUERA DE RANGO (%ld %ld)\n",
            fil, col);
    return 0;
  }
  return matriz->elem[fil][col];
}

void matriz_escribir(Matriz * matriz, size_t fil, size_t col, char val) {
  if (fil >= matriz_num_filas(matriz)) {
    fprintf(stderr,
            "\nmatriz_escribir: FILA FUERA DE RANGO (%ld %ld)/val:%c\n",
            fil, col, val);
    return;
  }
  if (col >= matriz_num_columnas(matriz)) {
    fprintf(stderr,
            "\nmatriz_escribir: COLUMNA FUERA DE RANGO (%ld %ld)/val:%c\n",
            fil, col, val);
    return;
  } else {
    matriz->elem[fil][col] = val;
  }
  // printf("- Valor %f ingresado en la posicion (%zu, %zu) -\n", matriz_leer(matriz, fil, col), fil, col);
}

size_t matriz_num_filas(Matriz * matriz) {
  return matriz->fil;
}

size_t matriz_num_columnas(Matriz * matriz) {
  return matriz->col;
}

void matriz_intercambiar_filas(Matriz * matriz, size_t fil1, size_t fil2) {
  if (fil1 <= matriz_num_filas(matriz) && fil2 <= matriz_num_filas(matriz)
      && fil1 != fil2) {
    char *aux = matriz->elem[fil1];
    matriz->elem[fil1] = matriz->elem[fil2];
    matriz->elem[fil2] = aux;

    // printf("- Se intercambiaron las filas %zu y %zu", fil1, fil2);    
  } else {
    // printf("- Intercambio mal definido -\n");
  }
}

void matriz_insertar_fila(Matriz * matriz, Matriz * fila, size_t numFila) {

  if (matriz_num_filas(fila) == 1
      && matriz_num_columnas(matriz) == matriz_num_columnas(fila)) {
    matriz->elem =
        realloc(matriz->elem,
                sizeof(char *) * (matriz_num_filas(matriz) + 1));
    matriz->fil += 1;

    char *nueva_fila = malloc(sizeof(char) * matriz_num_columnas(matriz));
    for (unsigned int i = 0; i < matriz_num_columnas(fila); i++) {
      nueva_fila[i] = matriz_leer(fila, 0, i);
    }

    char *aux = nueva_fila;
    for (unsigned int i = numFila; i < matriz_num_filas(matriz); i++) {
      char *fila_a_colocar = aux;
      aux = matriz->elem[i];
      matriz->elem[i] = fila_a_colocar;
    }

  } else {
    // printf("- Insertar mal definido -\n");
  }

}
