#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*FuncionVisitanteInt)(int dato);
typedef void (*FuncionVisitanteExtra) (int dato, void *extra);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitanteInt visit);

/**
 * Recorrido preorden del arbol con modelo iterativo y uso de pila
*/
void btree_recorrer_preorden(BTree arbol, FuncionVisitanteInt visit);

/**
 * Retorna el numero de nodos del arbol
*/
int btree_nnodos(BTree arbol);

/**
 * Retorna 1 si el numero dado se encuentra en el arbol y 0 en caso contrario
*/
int btree_buscar(BTree arbol, int dato);

/**
 * Retorna un nuevo arbol copia del arbol dado
*/
BTree btree_copiar(BTree arbol);

/**
 * Retorna la altura del arbol
*/
int btree_altura(BTree arbol);

/**
 * Retorna el numero de nodos que se encuentran a la profundidad dada
*/
int btree_nnodos_profundidad(BTree arbol, int profundidad);

/**
 * Retorna la profundidad del nodo que contiene al numero dado y 
 * -1 si no se encuentra en el arbol
*/
int btree_profundidad(BTree arbol, int dato);

/**
 * Retorna la suma total de los datos del arbol
*/
int btree_sumar(BTree arbol);

/**
 * Recorrido del arbol con parametro extra
*/
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden,
                          FuncionVisitanteExtra visit, void *extra);

/**
 * Recorrido BFS del arbol
*/
void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit);

#endif /* __BTREE_H__ */
