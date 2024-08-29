#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash.h" // Incluye la librería uthash
#define INT_MAX 2147483647

typedef struct {
    int x, y;
} Coordenada;

typedef struct {
    Coordenada coord;
    char estado; // '.' para espacio libre, '#' para obstáculo
    int g, rhs;
    int h; // heurística (distancia manhattan)
    UT_hash_handle hh; // macro para manejar la tabla hash
} NodoMapa;

typedef struct {
    NodoMapa* nodo;
    int prioridad;
} NodoCola;

typedef struct {
    NodoCola* elementos;
    int size;
    int capacidad;
} ColaPrioridad;

NodoMapa* mapa = NULL; // Tabla hash para representar el mapa
ColaPrioridad* cola_prioridad;

NodoMapa* destino; // Nodo que representa la posición del destino
NodoMapa* start; // Nodo que representa la posición inicial

// Función para calcular la heurística (distancia Manhattan)
int calcular_heuristica(Coordenada a, Coordenada b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Función para agregar una celda al mapa
void agregar_celda(int x, int y, char estado) {
    NodoMapa* nodo;
    Coordenada key = {x, y};
    
    // Busca si ya existe una celda con las coordenadas (x, y)
    HASH_FIND(hh, mapa, &key, sizeof(Coordenada), nodo);
    
    // Si no existe, la crea y la agrega al mapa
    if (!nodo) {
        nodo = (NodoMapa*)malloc(sizeof(NodoMapa));
        nodo->coord = key;
        nodo->estado = estado;
        HASH_ADD(hh, mapa, coord, sizeof(Coordenada), nodo);
    } else {
        // Si ya existe, actualiza el estado
        nodo->estado = estado;
    }
}

// Función para obtener el estado de una celda del mapa
char obtener_estado_celda(int x, int y) {
    NodoMapa* nodo;
    Coordenada key = {x, y};
    
    // Busca la celda en el mapa
    HASH_FIND(hh, mapa, &key, sizeof(Coordenada), nodo);
    
    // Si la celda existe, devuelve su estado, sino devuelve '?'
    return nodo ? nodo->estado : '?';
}

// Función para liberar la memoria de la tabla hash
void liberar_mapa() {
    NodoMapa *nodo, *tmp;
    
    // Itera y libera todos los nodos de la tabla hash
    HASH_ITER(hh, mapa, nodo, tmp) {
        HASH_DEL(mapa, nodo); // Elimina el nodo de la tabla hash
        free(nodo); // Libera la memoria del nodo
    }
}


void imprimir_resultados() {
    fprintf(stderr, "Robot ha llegado al destino.\n");
    fprintf(stderr, "Posición final: (%d, %d)\n", start->coord.x, start->coord.y);
}




// Inicialización de la cola de prioridad
ColaPrioridad* crear_cola_prioridad(int capacidad) {
    ColaPrioridad* cola = (ColaPrioridad*)malloc(sizeof(ColaPrioridad));
    if (!cola) {
        fprintf(stderr, "Error: No se pudo asignar memoria para la cola de prioridad.\n");
        exit(EXIT_FAILURE);
    }
    cola->elementos = (NodoCola*)malloc(sizeof(NodoCola) * capacidad);
    if (!cola->elementos) {
        fprintf(stderr, "Error: No se pudo asignar memoria para los elementos de la cola.\n");
        exit(EXIT_FAILURE);
    }
    cola->size = 0;
    cola->capacidad = capacidad;
    return cola;
}

void intercambiar(NodoCola* a, NodoCola* b) {
    NodoCola temp = *a;
    *a = *b;
    *b = temp;
}



// Actualizar la cola de prioridad al cambiar el tamaño
void push(ColaPrioridad* cola, NodoMapa* nodo, int prioridad) {
    for (int i = 0; i < cola->size; i++) {
        if (cola->elementos[i].nodo == nodo) {
            cola->elementos[i].prioridad = prioridad;
            while (i != 0 && cola->elementos[i].prioridad < cola->elementos[(i - 1) / 2].prioridad) {
                intercambiar(&cola->elementos[i], &cola->elementos[(i - 1) / 2]);
                i = (i - 1) / 2;
            }
            return;
        }
    }

    if (cola->size == cola->capacidad) {
        cola->capacidad *= 2;
        cola->elementos = (NodoCola*)realloc(cola->elementos, sizeof(NodoCola) * cola->capacidad);
        if (!cola->elementos) {
            fprintf(stderr, "Error: No se pudo reasignar memoria para los elementos de la cola.\n");
            exit(EXIT_FAILURE);
        }
    }
    cola->elementos[cola->size].nodo = nodo;
    cola->elementos[cola->size].prioridad = prioridad;
    int i = cola->size++;
    while (i != 0 && cola->elementos[i].prioridad < cola->elementos[(i - 1) / 2].prioridad) {
        intercambiar(&cola->elementos[i], &cola->elementos[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}


NodoMapa* pop(ColaPrioridad* cola) {
    if (cola->size == 0) return NULL;
    NodoMapa* nodo = cola->elementos[0].nodo;
    cola->elementos[0] = cola->elementos[--cola->size];
    int i = 0;
    while ((2 * i + 1) < cola->size) {
        int menor = (2 * i + 1);
        if ((2 * i + 2) < cola->size && cola->elementos[2 * i + 2].prioridad < cola->elementos[menor].prioridad)
            menor = 2 * i + 2;
        if (cola->elementos[i].prioridad <= cola->elementos[menor].prioridad) break;
        intercambiar(&cola->elementos[i], &cola->elementos[menor]);
        i = menor;
    }
    return nodo;
}

int cola_prioridad_vacia(ColaPrioridad* cola) {
    return cola->size == 0;
}


void inicializar() {
    cola_prioridad = crear_cola_prioridad(100); // Cola de prioridad con capacidad inicial

    // Inicializar valores de g y rhs para cada celda conocida
    NodoMapa* nodo, *tmp;
    HASH_ITER(hh, mapa, nodo, tmp) {
        nodo->g = INT_MAX;
        nodo->rhs = INT_MAX;
    }

    // Inicializar el nodo destino
    destino->rhs = 0;
    push(cola_prioridad, destino, calcular_heuristica(destino->coord, start->coord));
}


void actualizar_rhs(NodoMapa* nodo) {
    if (nodo->coord.x == destino->coord.x && nodo->coord.y == destino->coord.y) return; // No actualiza el destino
    int min_rhs = INT_MAX;
    NodoMapa* vecino;
    Coordenada dirs[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < 4; i++) {
        Coordenada vecino_coord = {nodo->coord.x + dirs[i].x, nodo->coord.y + dirs[i].y};
        HASH_FIND(hh, mapa, &vecino_coord, sizeof(Coordenada), vecino);
        if (vecino && vecino->g != INT_MAX) {
            int temp_rhs = vecino->g + 1;
            if (temp_rhs < min_rhs) min_rhs = temp_rhs;
        }
    }
    nodo->rhs = min_rhs;
}

void actualizar_celda(int x, int y, char estado) {
    fprintf(stderr, "Actualizando celda (%d, %d) con estado '%c'\n", x, y, estado);
    NodoMapa* nodo;
    Coordenada key = {x, y};
    HASH_FIND(hh, mapa, &key, sizeof(Coordenada), nodo);
    if (!nodo) {
        nodo = (NodoMapa*)malloc(sizeof(NodoMapa));
        nodo->coord = key;
        nodo->estado = estado;
        nodo->g = INT_MAX;
        nodo->rhs = INT_MAX;
        HASH_ADD(hh, mapa, coord, sizeof(Coordenada), nodo);
    } else {
        nodo->estado = estado;
    }

    actualizar_rhs(nodo); // Actualiza el RHS incluso si el nodo ya existía

    if (cola_prioridad_vacia(cola_prioridad) || nodo->g != nodo->rhs) {
        push(cola_prioridad, nodo, nodo->rhs + calcular_heuristica(nodo->coord, start->coord));
    }
}



void usar_sensor(int x, int y, int* distancias) {
    printf("? %d %d\n", x, y);
    fflush(stdout);

    if (scanf("%d %d %d %d", &distancias[0], &distancias[1], &distancias[2], &distancias[3]) != 4) {
        fprintf(stderr, "Error: Lectura de distancias fallida.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Distancias leídas: %d %d %d %d\n", distancias[0], distancias[1], distancias[2], distancias[3]);

    int D = 10;
    Coordenada direcciones[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < 4; i++) {
        Coordenada adyacente = {x + direcciones[i].x, y + direcciones[i].y};
        char nuevo_estado = (distancias[i] > D) ? '.' : '#';
        actualizar_celda(adyacente.x, adyacente.y, nuevo_estado);
    }
}



void actualizar_rhs_g() {
    NodoMapa* nodo;
    while (!cola_prioridad_vacia(cola_prioridad)) {
        nodo = pop(cola_prioridad);
        if (nodo->g > nodo->rhs) {
            nodo->g = nodo->rhs;
        } else {
            nodo->g = INT_MAX;
            actualizar_rhs(nodo);
        }
        actualizar_rhs(nodo);
    }
}

void replanificar(int x, int y) {
    NodoMapa* nodo;
    Coordenada key = {x, y};
    HASH_FIND(hh, mapa, &key, sizeof(Coordenada), nodo);
    if (nodo && nodo->estado == '#') {
        actualizar_celda(x, y, '#');
        actualizar_rhs_g();
    }
}


int no_ha_llegado_al_destino() {
    return !(start->coord.x == destino->coord.x && start->coord.y == destino->coord.y);
}
Coordenada obtener_mejor_direccion() {
    Coordenada dirs[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    NodoMapa* mejor_vecino = NULL;
    int min_g = INT_MAX;

    for (int i = 0; i < 4; i++) {
        Coordenada vecino_coord = {start->coord.x + dirs[i].x, start->coord.y + dirs[i].y};
        NodoMapa* vecino;
        HASH_FIND(hh, mapa, &vecino_coord, sizeof(Coordenada), vecino);
        if (vecino && vecino->g < min_g) {
            min_g = vecino->g;
            mejor_vecino = vecino;
        }
    }

    Coordenada direccion = {0, 0};
    if (mejor_vecino) {
        direccion = (Coordenada){mejor_vecino->coord.x - start->coord.x, mejor_vecino->coord.y - start->coord.y};
    }

    fprintf(stderr, "Dirección obtenida: (%d, %d)\n", direccion.x, direccion.y);
    return direccion;
}


void avanzar(Coordenada direccion) {
    start->coord.x += direccion.x;
    start->coord.y += direccion.y;
}


void mover_robot() {
    int i = 0;
    while (no_ha_llegado_al_destino()) {
        if(i++ == 5500) break; // Limitar el número de iteraciones para evitar bucles infinitos
        Coordenada direccion = obtener_mejor_direccion();
        Coordenada siguiente = {start->coord.x + direccion.x, start->coord.y + direccion.y};
        NodoMapa* nodo;
        HASH_FIND(hh, mapa, &siguiente, sizeof(Coordenada), nodo);
        if (!nodo || nodo->estado == '?' || nodo->estado == '#') {
            int distancias[4];
            usar_sensor(start->coord.x, start->coord.y, distancias);
            replanificar(siguiente.x, siguiente.y);
        }
        avanzar(direccion);

        // Añadir depuración aquí para verificar la posición actual
        fprintf(stderr, "Moviendo a dirección (%d, %d). Posición actual: (%d, %d)\n",
                direccion.x, direccion.y, start->coord.x, start->coord.y);
        
        imprimir_resultados(); // Asegúrate de definir esta función
    }
    fprintf(stderr, "BREAKPOINT %d.\n", i);
}




int main() {

    int N, M, D;
    scanf("%d%d%d", &N, &M, &D);
    int i1 , j1;
    scanf("%d%d", &i1, &j1);
    int i2 , j2;
    scanf("%d%d", &i2, &j2);

    fprintf(stderr, "N: %d, M: %d, D: %d\n", N, M, D);
    fprintf(stderr, "Posición inicial: (%d, %d)\n", i1, j1);
    fprintf(stderr, "Posición destino: (%d, %d)\n", i2, j2);


// Inicializar el mapa y los nodos start y destino
    agregar_celda(i1, j1, '.'); // Ejemplo de celda inicial
    agregar_celda(i2, j2, '.'); // Ejemplo de celda destino

    Coordenada inicio = {i1, j1};
    Coordenada fin = {i2, j2};

    // Crear nodos para start y destino
    start = (NodoMapa*)malloc(sizeof(NodoMapa));
    start->coord = inicio;
    start->estado = '.';
    start->g = INT_MAX;
    start->rhs = INT_MAX;
    HASH_ADD(hh, mapa, coord, sizeof(Coordenada), start);

    destino = (NodoMapa*)malloc(sizeof(NodoMapa));
    destino->coord = fin;
    destino->estado = '.';
    destino->g = INT_MAX;
    destino->rhs = 0;
    HASH_ADD(hh, mapa, coord, sizeof(Coordenada), destino);

    // Mensajes de depuración para los nodos iniciales
    fprintf(stderr, "Nodo inicial: (%d, %d) con estado '%c'\n", start->coord.x, start->coord.y, start->estado);
    fprintf(stderr, "Nodo destino: (%d, %d) con estado '%c'\n", destino->coord.x, destino->coord.y, destino->estado);

    // Inicializar la cola de prioridad y el nodo destino
    inicializar();

    // Mueve el robot hasta el destino
    mover_robot();
    
    // Liberar recursos
    liberar_mapa();
    free(cola_prioridad->elementos);
    free(cola_prioridad);

    return 0;
}
