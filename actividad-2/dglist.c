#include <stdlib.h>
#include "dglist.h"

DGList dglist_crear(void) {
  DGList list = malloc(sizeof(_DGList));
  list->first = NULL;
  list->last = NULL;
  return list;
}

int dglist_vacia(DGList list) {
  return (list->first == NULL && list->last == NULL);
}

void dglist_agregar_inicio(DGList list, void *data, FuncionCopiadora copy) {
  GNode *newNode = malloc(sizeof(GNode));
  newNode->next = list->first;
  newNode->data = copy(data);

  if(dglist_vacia(list)) list->last = newNode;
  
  list->first = newNode;
}

void dglist_agregar_final(DGList list, void *data, FuncionCopiadora copy) {
  GNode *newNode = malloc(sizeof(GNode));
  newNode->next = NULL;
  newNode->data = copy(data);

  if (dglist_vacia(list)) list->first = newNode;
  else list->last->next = newNode;

  list->last = newNode;
}

void dglist_recorrer(DGList list, FuncionVisitante visit) {
  for (GNode * node = list->first; node != NULL; node = node->next)
    visit(node->data);
}

void dglist_destruir(DGList list, FuncionDestructora destroy) {

  GNode *nodeToDelete, *nodeIdx = list->first;
  while(nodeIdx != NULL) {
    nodeToDelete = nodeIdx;
    nodeIdx = nodeIdx->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
  free(list);
}