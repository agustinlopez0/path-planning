typedef int Pila;
typedef int TablaHash;


typedef struct {
  int i ;
  int j ;
} _Punto ;

typedef _Punto * Punto ;

typedef enum {
  LEFT ,
  RIGHT ,
  UP ,
  DOWN
} Direccion ;

typedef struct {
  Punto pos ;
  Punto dest ;
  Pila movimientos ;
  TablaHash visitados ;
} _Robot ;
typedef _Robot * Robot ;