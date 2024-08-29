#include "btree.h"
#include "pila.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
};

void* id(void * x) {return x;}
void no_destruir(void* x) {}

BTree btree_crear() { return NULL; }

void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

int btree_empty(BTree nodo) { return nodo == NULL; }

BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitanteInt visit) {
  if(btree_empty(arbol)) return;
   
  if(orden == BTREE_RECORRIDO_PRE) visit(arbol->dato);
  btree_recorrer(arbol->left, orden, visit);
  if(orden == BTREE_RECORRIDO_IN) visit(arbol->dato);
  btree_recorrer(arbol->right, orden, visit);
  if(orden == BTREE_RECORRIDO_POST) visit(arbol->dato);
  
}

void destruir_nodo(void* a) {free(a);}

void btree_recorrer_preorden(BTree arbol, FuncionVisitanteInt visit){
  if(btree_empty(arbol)) return;

  Pila pila_de_nodos = pila_crear();
  pila_de_nodos = pila_apilar(pila_de_nodos, arbol, id);

  while(!pila_es_vacia(pila_de_nodos)){
    BTree nodo_actual = pila_tope(pila_de_nodos);
    visit(nodo_actual->dato);

    pila_de_nodos = pila_desapilar(pila_de_nodos, destruir_nodo);

    if(!btree_empty(nodo_actual->right))
      pila_de_nodos = pila_apilar(pila_de_nodos, nodo_actual->right, id);
    if(!btree_empty(nodo_actual->left))
      pila_de_nodos = pila_apilar(pila_de_nodos, nodo_actual->left, id);
  }

  pila_destruir(pila_de_nodos, destruir_nodo);
}

int btree_nnodos(BTree arbol){
  if(arbol == NULL) return 0;
  return 1 + btree_nnodos(arbol->left) + btree_nnodos(arbol->right);
}

int btree_buscar(BTree arbol, int dato){
  if(arbol == NULL) return 0;
  return (arbol->dato == dato) || btree_buscar(arbol->left, dato) || btree_buscar(arbol->right, dato);
}

BTree btree_copiar(BTree arbol){
  if (arbol == NULL) return btree_crear();
  return btree_unir(arbol->dato, btree_copiar(arbol->left), btree_copiar(arbol->right));
}

static int max(int a, int b){ return a > b ? a : b; }

int btree_altura(BTree arbol){
  if(arbol == NULL) return -1;
  return 1 + max(btree_altura(arbol->left), btree_altura(arbol->right));
}

int btree_nnodos_profundidad(BTree arbol, int profundidad){
  if(arbol == NULL) return 0;
  if(profundidad == 0) return 1;
  return btree_nnodos_profundidad(arbol->left, profundidad - 1) +
          btree_nnodos_profundidad(arbol->right, profundidad - 1);

}

// int btree_profundidad(BTree arbol, int dato){
//   if(arbol == NULL) return -1;
//   if(arbol->dato == dato) return 1;
//   return btree_profundidad(arbol->left, dato);
// }

int btree_sumar(BTree arbol){
  if(arbol == NULL) return 0;
  return arbol->dato + btree_sumar(arbol->left) + btree_sumar(arbol->right);
}

void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden,
                          FuncionVisitanteExtra visit, void *extra){
  if(btree_empty(arbol)) return;
   
  if(orden == BTREE_RECORRIDO_PRE) visit(arbol->dato, extra);
  btree_recorrer_extra(arbol->left, orden, visit, extra);
  if(orden == BTREE_RECORRIDO_IN) visit(arbol->dato, extra);
  btree_recorrer_extra(arbol->right, orden, visit, extra);
  if(orden == BTREE_RECORRIDO_POST) visit(arbol->dato, extra);
  
}

void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit){
  
}

/*
               x                15 = 2⁴ - 0
       /               \        7 15
       x               x        7 15 2³ - 1
   /       \       /       \    3 7 
   x       x       x       x    3 7  2² - 1
 /   \   /   \   /   \   /   \  1 3
 x   x   x   x   x   x   x   x  1 3  2¹ - 1
/ \ / \ / \ / \ / \ / \ / \ / \ 0 1  
x x x x x x x x x x x x x x 7 x 0 1  2⁰ - 1
*/
/*
               x                
       /               \        
       x               x        
   /       \       /       \    
   x       x       x       x    
 /   \   /   \   /   \   /   \ 
 x   x   x   x   x   x   x   x  
/ \ / \ / \ / \ / \ / \ / \ / \  
x x x x x x x x x x x x x x 7 x 
*/