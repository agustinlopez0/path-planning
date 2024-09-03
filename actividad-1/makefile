CC = gcc
CFLAGS = -Wall -Wextra
EXEC = main
SOURCES = main.c robot.c mapa.c pila.c glist.c simulacion.c punto.c direccion.c tablahash.c leerArchivo.c

$(EXEC): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC)

clean:
	rm -f $(BACKUP) $(EXEC)
