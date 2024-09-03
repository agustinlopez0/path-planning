#include "bheap.h"


BHeap bheap_crear(size_t capacidad, FuncionComparadora comp, FuncionDestructora destroy) {
  BHeap heap = malloc(sizeof(struct _BHeap));
  heap->arr = malloc(sizeof(void *) * (capacidad + 1));
  heap->capacidad = capacidad;
  heap->ultimo = 0;
  heap->comp = comp;
  heap->destr = destroy;
  return heap;
}

int bheap_es_vacio(BHeap heap) {
  return heap->ultimo == 0;
}

static int hijo_izq(int i) {
  return 2 * i;
}
static int hijo_der(int i) {
  return 2 * i + 1;
}
static int padre(int i) {
  return i / 2;
}
static void swap(void **a, void **b) {
  void *aux = *a;
  *a = *b;
  *b = aux;
}

static void flotar(BHeap heap, int pos_dato_flotar) {
  for (int i = pos_dato_flotar; i > 1 && heap->comp(heap->arr[i], heap->arr[padre(i)]) > 0; i = padre(i)) {
    swap(&heap->arr[i], &heap->arr[padre(i)]);
  }
}

void bheap_insertar(BHeap heap, void *dato) {
  if (heap->ultimo == heap->capacidad - 1) {
    heap->capacidad *= 2;
    heap->arr = realloc(heap->arr, sizeof(void *) * heap->capacidad);
  }

  heap->arr[++heap->ultimo] = dato;

  flotar(heap, heap->ultimo);
}

void bheap_destruir(BHeap heap) {
  if (heap == NULL)
    return;

  if (heap->destr != NULL)
    for (int i = 1; i <= heap->ultimo; i++)
      heap->destr(heap->arr[i]);

  free(heap->arr);
  free(heap);
}

static void hundir(BHeap heap, int pos_dato) {

  int es_mayor = 1;

  while (hijo_izq(pos_dato) <= heap->ultimo && es_mayor) {      // mientras tenga un hijo y sea mayor a alguno
    int mayor_hijo = hijo_izq(pos_dato);
    if (hijo_der(pos_dato) <= heap->ultimo && heap->comp(heap->arr[hijo_der(pos_dato)], heap->arr[mayor_hijo]) > 0)
      mayor_hijo = hijo_der(pos_dato);
    if (heap->comp(heap->arr[pos_dato], heap->arr[mayor_hijo]) > 0)
      es_mayor = 0;
    else {
      swap(&heap->arr[pos_dato], &heap->arr[mayor_hijo]);
      pos_dato = mayor_hijo;
    }
  }
}

void bheap_eliminar(BHeap heap, size_t pos) {
  swap(&heap->arr[pos], &heap->arr[heap->ultimo]);
  if (heap->destr != NULL)
    heap->destr(heap->arr[heap->ultimo]);

  heap->ultimo--;
  hundir(heap, pos);
}
