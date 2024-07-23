#include "arregloenteros.h"

int main() {

  ArregloEnteros* arr = arreglo_enteros_crear(3);

  arreglo_enteros_escribir(arr, 0, 1);
  arreglo_enteros_escribir(arr, 1, 30);
  arreglo_enteros_escribir(arr, 1, 32);
  arreglo_enteros_escribir(arr, 2, 99);

  arreglo_enteros_imprimir(arr);

  arreglo_enteros_insertar(arr, 0, 15);
  arreglo_enteros_insertar(arr, 0, 16);
  arreglo_enteros_insertar(arr, 3, 168);


  arreglo_enteros_imprimir(arr);

  arreglo_enteros_ajustar(arr, arreglo_enteros_capacidad(arr) * 2);

  arreglo_enteros_imprimir(arr);


  arreglo_enteros_destruir(arr);

  return 0;
}