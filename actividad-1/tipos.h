#ifndef TIPOS_H
#define TIPOS_H

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionVisitante)(void *dato);


#endif /* TIPOS_H */