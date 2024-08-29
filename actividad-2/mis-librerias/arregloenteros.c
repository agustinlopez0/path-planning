#include "arregloenteros.h"

ArregloEnteros* arreglo_enteros_crear(size_t capacidad){
    ArregloEnteros *arr = malloc(sizeof(ArregloEnteros));
    
    int* direccion = malloc(sizeof(int) * capacidad);
    
    arr->direccion = direccion;
    arr->capacidad = capacidad;

    return arr;
}

void arreglo_enteros_destruir(ArregloEnteros* arr){
    free(arr->direccion);
    free(arr);
}

int arreglo_enteros_leer(ArregloEnteros* arreglo, size_t pos){
    assert(pos < arreglo_enteros_capacidad(arreglo));
    return arreglo->direccion[pos];
}

void arreglo_enteros_escribir(ArregloEnteros* arreglo, size_t pos, int dato){
    assert(pos < arreglo_enteros_capacidad(arreglo));
    arreglo->direccion[pos] = dato;
}

int arreglo_enteros_capacidad(ArregloEnteros* arreglo){
    return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros* arreglo){
    printf("- Capacidad arreglo: %d\n", arreglo->capacidad);
    for(int i = 0; i < arreglo_enteros_capacidad(arreglo); i++){
        printf("Posicion %i: %i\n", i, arreglo_enteros_leer(arreglo, i));
    }
    printf("-\n\n");
}

void arreglo_enteros_ajustar(ArregloEnteros* arreglo, size_t capacidad){
    if(capacidad != arreglo_enteros_capacidad(arreglo)){
        arreglo->direccion = realloc(arreglo->direccion, sizeof(int) * capacidad);
        arreglo->capacidad = capacidad;
    }
}

void arreglo_enteros_insertar(ArregloEnteros* arreglo, size_t pos, int dato){
    assert(pos < arreglo_enteros_capacidad(arreglo));
    
    arreglo_enteros_ajustar(arreglo, arreglo_enteros_capacidad(arreglo)+1);

    int aux = dato;
    for(int i = pos; i < arreglo_enteros_capacidad(arreglo); i++){
        int dato_a_escribir = aux;
        aux = arreglo_enteros_leer(arreglo, i);
        arreglo_enteros_escribir(arreglo, i, dato_a_escribir);
    }
}

void arreglo_enteros_eliminar(ArregloEnteros* arreglo, size_t pos){
    assert(pos < arreglo_enteros_capacidad(arreglo));

    int aux = 0;
    for(int i = arreglo_enteros_capacidad(arreglo) - 1; i >= pos; i--){
        int dato_a_escribir = aux;
        aux = arreglo_enteros_leer(arreglo, i);
        arreglo_enteros_escribir(arreglo, i, dato_a_escribir);
    }
    arreglo_enteros_imprimir(arreglo);
    arreglo_enteros_ajustar(arreglo, arreglo_enteros_capacidad(arreglo) - 1);
}