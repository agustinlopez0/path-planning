#include <stdlib.h>
#include "glist.h"

GList glist_crear(void) {
  return NULL;
}

int glist_vacia(GList list) {
  return (list == NULL);
}

GList glist_agregar_inicio(GList list, void *data, FuncionCopiadora copy) {
  GNode *newNode = malloc(sizeof(GNode));
  newNode->next = list;
  newNode->data = copy(data);

  return newNode;
}

GList glist_agregar_final(GList list, void *data, FuncionCopiadora copy) {
  GNode *newNode = malloc(sizeof(GNode));
  newNode->next = NULL;
  newNode->data = copy(data);

  if (glist_vacia(list))
    return newNode;

  GNode *node = list;
  for (; node->next; node = node->next);

  node->next = newNode;

  return list;
}

void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode * node = list; node != NULL; node = node->next)
    visit(node->data);
}

void *glist_primer_elemento(GList list) {
  if (glist_vacia(list))
    return NULL;
  return list->data;
}

GList glist_eliminar_inicio(GList list, FuncionDestructora destroy) {
  if (glist_vacia(list))
    return NULL;
  GNode *nodeToDelete = list;
  list = list->next;
  destroy(nodeToDelete->data);
  free(nodeToDelete);
  return list;
}

void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}
