#include "glist.h"

GList glist_crear() { return NULL; }

void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

int glist_vacia(GList list) { return (list == NULL); }

GList glist_agregar_inicio(GList list, void *data, FuncionCopiadora copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);

  return newNode;
}

GList glist_agregar_final(GList list, void *data, FuncionCopiadora copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = NULL;
  newNode->data = copy(data);

  if(glist_vacia(list)){
    return newNode;
  }

  GNode *node = list;
  for(; node->next; node = node->next);
  
  node->next = newNode;

  return list;
}

void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

GList glist_filtrar(GList lista, FuncionCopiadora c, Predicado p){
  GList lista_filtrada = glist_crear();
  for(GNode *temp = lista; temp != NULL; temp = temp->next){
    p(temp->data);
    if( p(temp->data) ){
      lista_filtrada = glist_agregar_inicio(lista_filtrada, temp->data, c);
    }
  }
  return lista_filtrada;
}

void* glist_primer_elemento(GList list){
    return list->data;
}

GList glist_eliminar_final(GList lista, FuncionDestructora destroy){
    if(glist_vacia(lista)) return NULL;
    if(lista->next == NULL) {
        destroy(lista);
        return NULL;
    }
    GNode *nodo = lista;
    for(; nodo->next->next; nodo = nodo->next);
    destroy(nodo->next);
    nodo->next = NULL;
    return lista;
}

GList glist_eliminar_inicio(GList lista, FuncionDestructora destroy){
  if(glist_vacia(lista)) return NULL;
  GNode *nodoAEliminar = lista;
  lista = lista->next;
  destroy(nodoAEliminar->data);
  free(nodoAEliminar);
  return lista;
}

int glist_include(GList lista, void * dato, FuncionComparadora comp){
  if(glist_vacia(lista)) return 0;
  if(comp(lista->data, dato) == 0) return 1;
  return glist_include(lista->next, dato, comp);
}