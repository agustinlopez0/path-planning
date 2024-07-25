#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "matriz.h"
// #include "funcioneslistas.h"
#include "tipos2.h"

typedef struct {
    int costo;
    int prioridad;
    Punto pos;
} Nodo;

typedef struct {
    Nodo *nodos;
    int capacidad;
    int tamaño;
} ColaPrioridad;

typedef struct {
    Punto padre;
    int costo;
} CeldaInfo;

void intercambiar(Nodo *a, Nodo *b) {
    Nodo temp = *a;
    *a = *b;
    *b = temp;
}

void burbujeoHaciaArriba(ColaPrioridad *cola, int i) {
    while (i > 0 && cola->nodos[i].prioridad < cola->nodos[(i - 1) / 2].prioridad) {
        intercambiar(&cola->nodos[i], &cola->nodos[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void burbujeoHaciaAbajo(ColaPrioridad *cola, int i) {
    int izq = 2 * i + 1;
    int der = 2 * i + 2;
    int menor = i;

    if (izq < cola->tamaño && cola->nodos[izq].prioridad < cola->nodos[menor].prioridad) {
        menor = izq;
    }
    if (der < cola->tamaño && cola->nodos[der].prioridad < cola->nodos[menor].prioridad) {
        menor = der;
    }
    if (menor != i) {
        intercambiar(&cola->nodos[i], &cola->nodos[menor]);
        burbujeoHaciaAbajo(cola, menor);
    }
}

void inicializarCola(ColaPrioridad *cola, int capacidad) {
    cola->nodos = (Nodo *)malloc(capacidad * sizeof(Nodo));
    cola->capacidad = capacidad;
    cola->tamaño = 0;
}

void insertarNodo(ColaPrioridad *cola, Nodo nodo) {
    if (cola->tamaño < cola->capacidad) {
        cola->nodos[cola->tamaño] = nodo;
        burbujeoHaciaArriba(cola, cola->tamaño);
        cola->tamaño++;
    }
}

Nodo extraerNodoConPrioridad(ColaPrioridad *cola) {
    Nodo nodo = cola->nodos[0];
    cola->tamaño--;
    cola->nodos[0] = cola->nodos[cola->tamaño];
    burbujeoHaciaAbajo(cola, 0);
    return nodo;
}

#define INF INT_MAX

void imprimirCamino(Punto destino, CeldaInfo** celdaInfo) {
    Punto camino[25];
    int longitud = 0;

    for (Punto p = destino; p.x != -1 && p.y != -1; p = celdaInfo[p.x][p.y].padre) {
        camino[longitud++] = p;
    }

    fprintf(stderr, "Camino encontrado:\n");
    for (int i = longitud - 1; i >= 0; i--) {
        fprintf(stderr, "(%d, %d)\n", camino[i].x, camino[i].y);
    }
}
void liberarCeldaInfo(CeldaInfo **celdaInfo, int N) {
    for (int i = 0; i < N; i++) {
        free(celdaInfo[i]);
    }
    free(celdaInfo);
}
void inicializarCeldaInfo(CeldaInfo ***celdaInfo, int N, int M) {
    *celdaInfo = (CeldaInfo **)malloc(N * sizeof(CeldaInfo *));
    for (int i = 0; i < N; i++) {
        (*celdaInfo)[i] = (CeldaInfo *)malloc(M * sizeof(CeldaInfo));
    }
}

void d_star_lite(Robot robot) {
    Punto inicio = *robot->pos;
    Punto destino = *robot->dest;
    int N = matriz_num_filas(robot->mapa);
    int M = matriz_num_columnas(robot->mapa);
    ColaPrioridad cola;
    inicializarCola(&cola, N * M);

    int costos[N][M];
    CeldaInfo **celdaInfo;
    inicializarCeldaInfo(&celdaInfo, N, M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            costos[i][j] = INF;
            celdaInfo[i][j].costo = INF;
            celdaInfo[i][j].padre = (Punto){-1, -1}; // Indica que no hay predecesor
        }
    }

    costos[inicio.x][inicio.y] = 0;
    celdaInfo[inicio.x][inicio.y].costo = 0;
    celdaInfo[inicio.x][inicio.y].padre = (Punto){-1, -1}; // Nodo inicial sin padre

    Nodo nodoInicio = {0, 0, inicio};
    insertarNodo(&cola, nodoInicio);

    while (cola.tamaño > 0) {
        Nodo nodo = extraerNodoConPrioridad(&cola);

        if (nodo.pos.x == destino.x && nodo.pos.y == destino.y) {
            imprimirCamino(destino, celdaInfo);
            free(cola.nodos); // Liberar memoria de la cola
            liberarCeldaInfo(celdaInfo, N); // Liberar memoria de celdaInfo
            return;
        }

        // Actualiza vecinos
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if ((dx == 0 && dy == 0) || (dx != 0 && dy != 0)) continue;
                
                int nx = nodo.pos.x + dx;
                int ny = nodo.pos.y + dy;
                
                if (nx >= 0 && nx < N && ny >= 0 && ny < M && matriz_leer(robot->mapa, nx, ny) != '#') {
                    int nuevoCosto = nodo.costo + 1; // Asumiendo costo uniforme
                    if (nuevoCosto < costos[nx][ny]) {
                        costos[nx][ny] = nuevoCosto;
                        celdaInfo[nx][ny].costo = nuevoCosto;
                        celdaInfo[nx][ny].padre = nodo.pos; // Establece el predecesor
                        Nodo vecino = {nuevoCosto, nuevoCosto, {nx, ny}};
                        insertarNodo(&cola, vecino);
                    }
                }
            }
        }
    }

    fprintf(stderr, "No se encontró un camino\n");
    free(cola.nodos); // Liberar memoria de la cola
    liberarCeldaInfo(celdaInfo, N); // Liberar memoria de celdaInfo
}


int main() {
    Robot robot = malloc(sizeof(_Robot));
    Punto a = {0, 0}, b = {2, 2};
    robot->pos = &a;
    robot->dest = &b;

    int N, M;
    scanf("%d%d%d", &N, &M, &robot->sensor);
    robot->mapa = matriz_crear(N, M);

    robot->mapa = matriz_crear(N, M);
    matriz_escribir(robot->mapa, 0, 0, '.');
    matriz_escribir(robot->mapa, 1, 0, '.');
    matriz_escribir(robot->mapa, 2, 0, '.');
    matriz_escribir(robot->mapa, 3, 0, '.');
    matriz_escribir(robot->mapa, 4, 0, '.');
    matriz_escribir(robot->mapa, 0, 1, '.');
    matriz_escribir(robot->mapa, 1, 1, '#');
    matriz_escribir(robot->mapa, 2, 1, '#');
    matriz_escribir(robot->mapa, 3, 1, '#');
    matriz_escribir(robot->mapa, 4, 1, '.');
    matriz_escribir(robot->mapa, 0, 2, '.');
    matriz_escribir(robot->mapa, 1, 2, '#');
    matriz_escribir(robot->mapa, 2, 2, '.');
    matriz_escribir(robot->mapa, 3, 2, '.');
    matriz_escribir(robot->mapa, 4, 2, '.');
    matriz_escribir(robot->mapa, 0, 3, '.');
    matriz_escribir(robot->mapa, 1, 3, '#');
    matriz_escribir(robot->mapa, 2, 3, '.');
    matriz_escribir(robot->mapa, 3, 3, '#');
    matriz_escribir(robot->mapa, 4, 3, '.');
    matriz_escribir(robot->mapa, 0, 4, '.');
    matriz_escribir(robot->mapa, 1, 4, '.');
    matriz_escribir(robot->mapa, 2, 4, '.');
    matriz_escribir(robot->mapa, 3, 4, '.');
    matriz_escribir(robot->mapa, 4, 4, '.');

    d_star_lite(robot);

    // free(robot->mapa);
    // free(robot);
    printf("! RRRRDDLL\n");
    return 0;
}
