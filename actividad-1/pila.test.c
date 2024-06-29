#include "pila.h"
#include "contacto.h"

int main() {

  Pila pila = pila_crear();
  Contacto *contactos[6];
  contactos[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  contactos[1] = contacto_crear("Moni Argento", "3412684759", 60);
  contactos[2] = contacto_crear("Coqui Argento", "3415694286", 32);
  contactos[3] = contacto_crear("Paola Argento", "3416259862", 29);
  contactos[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  contactos[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);

  for (int i = 0; i < 6; ++i) {
    pila =
        pila_apilar(pila, contactos[i], (FuncionCopiadora)contacto_copia);
    contacto_destruir(contactos[i]);
  }

  puts("Pila:");
  pila_recorrer(pila, (FuncionVisitante)contacto_imprimir);

  pila = pila_desapilar(pila, (FuncionDestructora)contacto_destruir);
  pila = pila_desapilar(pila, (FuncionDestructora)contacto_destruir);
  pila = pila_desapilar(pila, (FuncionDestructora)contacto_destruir);
  pila = pila_desapilar(pila, (FuncionDestructora)contacto_destruir);

  puts("Pila:");
  pila_recorrer(pila, (FuncionVisitante)contacto_imprimir);

  pila_destruir(pila, (FuncionDestructora)contacto_destruir);

  return 0;
}