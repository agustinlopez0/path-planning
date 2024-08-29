#include "colaprioridad.h"
#include <time.h>

typedef struct {
  char* tarea;
  int prioridad;
} _ToDo;

typedef _ToDo *ToDo;

ToDo to_do_crear(char* tarea, int prioridad){
  ToDo to_do = malloc(sizeof(_ToDo));
  to_do->prioridad = prioridad;
  to_do->tarea = malloc(sizeof(char) * (strlen(tarea) + 1));
  strcpy(to_do->tarea, tarea);
  return to_do;
}

int to_do_comparar(ToDo a, ToDo b){
  if(a->prioridad == b->prioridad) return 0;
  return a->prioridad > b->prioridad ? 1 : -1;
}

void to_do_destruir(ToDo a){
  free(a->tarea);
  free(a);
}

void to_do_imprimir(ToDo a){
  printf("Prioridad: %3d - Tarea: %s\n", a->prioridad, a->tarea);
}

ToDo* to_do_copiar(ToDo* a){
  return a;
}

int main(){

  srand(time(NULL));

  char* arreglo_tareas[] = {"hacer la cama", "cocinar", "lavar platos",
  "lavar ropa", "sacar basura", "hacer tarea", "hacer mandados"};

  ToDo* arreglo_to_do = malloc(sizeof(ToDo) * 7);
  for(int i = 0; i < 7; i++)
    arreglo_to_do[i] = to_do_crear(arreglo_tareas[i], rand() % 50);

  ColaPrioridad tareas = 
    cola_prioridad_crear_desde_arr((void**)arreglo_to_do, 7,
    (FuncionCopiadora)to_do_copiar, (FuncionDestructora)to_do_destruir,
    (FuncionComparadora)to_do_comparar);

  cola_prioridad_recorrer(tareas, (FuncionVisitante)to_do_imprimir);
  puts("-------");
  for(int i = 0; i < 7; i++){
    puts("\nHacer YA");
    to_do_imprimir(cola_prioridad_maximo(tareas));
    cola_prioridad_eliminar_maximo(tareas);
  }

  cola_prioridad_destruir(tareas);

  puts("");
  return 0;
}