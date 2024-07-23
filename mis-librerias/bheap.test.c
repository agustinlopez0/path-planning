#include "bheap.c"
#include "contacto.h"

int main(){

  BHeap heap = bheap_crear(3, (FuncionComparadora)contacto_comparar,
    (FuncionDestructora)contacto_destruir);
  Contacto *contactos[6];
  contactos[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  contactos[1] = contacto_crear("Moni Argento", "3412684759", 60);
  contactos[2] = contacto_crear("Coqui Argento", "3415694286", 32);
  contactos[3] = contacto_crear("Paola Argento", "3416259862", 29);
  contactos[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  contactos[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);

  /*
  0             Pepe
  1     Paola        Dardo
  2  Moni   Maria  Coqui 
  */
  /*
  0              Moni                        Dardo           
  1      Paola          Dardo  =>    Paola            Coqui
  2   Pepe    Maria  Coqui        Pepe   Maria              
  */
   /*
  0             Pepe         
  1     Dardo            Coqui
  2  Paola   Maria             
  */

  for (int i = 0; i < 6; ++i)
    bheap_insertar(heap, contactos[i]);

  puts("Heap:");
  bheap_recorrer(heap, (FuncionVisitante)contacto_imprimir);

  bheap_eliminar(heap, 5);
  bheap_eliminar(heap, 1);

  puts("Heap:");
  bheap_recorrer(heap, (FuncionVisitante)contacto_imprimir);

  bheap_destruir(heap);




  return 0;
}