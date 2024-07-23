#include "matriz.h"

/*
** Implementacion utilizando un arreglo bidimensional (arreglo de punteros a arreglo)
*/

struct Matriz_ {
  double **elem;
  size_t fil, col;
};


Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {
  Matriz* matriz = malloc(sizeof(Matriz));
  matriz->fil = numFilas;
  matriz->col = numColumnas;
  matriz->elem = malloc(sizeof(double *) * numFilas); 

  for(int i = 0; i < numFilas; i++){
    matriz->elem[i] = malloc(sizeof(double) * numColumnas);
  }

  printf("- Matriz de %zux%zu creada -\n", matriz_num_filas(matriz), matriz_num_columnas(matriz));

  return matriz;
}

void matriz_destruir(Matriz* matriz) {
  for (int i = 0; i < matriz_num_filas(matriz); i++){
    free(matriz->elem[i]);
  }

  free(matriz->elem);
  free(matriz);

  printf("- Matriz destruida -\n");
}

double matriz_leer(Matriz* matriz, size_t fil, size_t col) {
  return matriz->elem[fil][col];
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {
  matriz->elem[fil][col] = val;
  // printf("- Valor %f ingresado en la posicion (%zu, %zu) -\n", matriz_leer(matriz, fil, col), fil, col);
}

size_t matriz_num_filas(Matriz* matriz) {
  return matriz->fil;
}

size_t matriz_num_columnas(Matriz* matriz) {
  return matriz->col;
}

void matriz_intercambiar_filas(Matriz* matriz, size_t fil1, size_t fil2){
  if(fil1 <= matriz_num_filas(matriz) && fil2 <= matriz_num_filas(matriz) && fil1 != fil2){
    double* aux = matriz->elem[fil1];
    matriz->elem[fil1] = matriz->elem[fil2];    
    matriz->elem[fil2] = aux;   
        
    printf("- Se intercambiaron las filas %zu y %zu", fil1, fil2);    
  } else {
    printf("- Intercambio mal definido -\n");
  }
}
  
void matriz_insertar_fila(Matriz* matriz, Matriz* fila, size_t numFila){

  if(matriz_num_filas(fila) == 1 && matriz_num_columnas(matriz) == matriz_num_columnas(fila)){
    matriz->elem = realloc(matriz->elem, sizeof(double *) * (matriz_num_filas(matriz) + 1));
    matriz->fil += 1;

    double* nueva_fila = malloc(sizeof(double) * matriz_num_columnas(matriz));
    for(int i = 0; i < matriz_num_columnas(fila); i++){
      nueva_fila[i] = matriz_leer(fila, 0, i);
    }

    double* aux = nueva_fila;
    for(int i = numFila; i < matriz_num_filas(matriz); i++){
      double* fila_a_colocar = aux;
      aux = matriz->elem[i];
      matriz->elem[i] = fila_a_colocar;
    } 
    
  } else {
    printf("- Insertar mal definido -\n");
  }

}



