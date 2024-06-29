#include "contacto.h"

Contacto *contacto_crear(char *nombre, char *telefono, unsigned int edad) {
  Contacto *nuevo = malloc(sizeof(Contacto));

  nuevo->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
  strcpy(nuevo->nombre, nombre);

  nuevo->tel = malloc(sizeof(char) * (strlen(telefono) + 1));
  strcpy(nuevo->tel, telefono);

  nuevo->edad = edad;

  return nuevo;
}

Contacto *contacto_copia(Contacto *contacto) {
  Contacto *copia =
      contacto_crear(contacto->nombre, contacto->tel, contacto->edad);
  return copia;
}

int contacto_comparar(Contacto *c1, Contacto *c2) {
  return (strcmp(c1->nombre, c2->nombre));
}

void contacto_destruir(Contacto *contacto) {
  free(contacto->nombre);
  free(contacto->tel);
  free(contacto);
}

void contacto_imprimir(Contacto *contacto) {
  printf("%s, %s, %d.\n", contacto->nombre, contacto->tel, contacto->edad);
}

int mayor_60 (Contacto *contacto){
  return (contacto->edad >= 60);
}