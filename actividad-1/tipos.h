#ifndef TIPOS_H
#define TIPOS_H

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionVisitante)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);
typedef int (*Predicado) (void *dato);


#endif /* TIPOS_H */