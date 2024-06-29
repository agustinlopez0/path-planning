#include "pila.h"

Pila pila_crear(void){
    return glist_crear();
}

void pila_destruir(Pila pila, FuncionDestructora destroy){
    glist_destruir(pila, destroy);
} 

int pila_es_vacia(Pila pila){
    return glist_vacia(pila);
}

void* pila_tope(Pila pila){
    assert(!pila_es_vacia(pila));
    return glist_primer_elemento(pila);
}

Pila pila_apilar(Pila pila, void* dato, FuncionCopiadora copy){
    return glist_agregar_inicio(pila, dato, copy);
}

Pila pila_desapilar(Pila pila, FuncionDestructora destroy){
    return glist_eliminar_inicio(pila, destroy);
}

void pila_recorrer(Pila pila, FuncionVisitante visit){
    glist_recorrer(pila, visit);
}