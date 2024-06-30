# Variables
CC = gcc
CFLAGS = -Wall -Wextra
INDENT = indent
INDENT_FLAGS = -kr -brf -i2 -nut
SRC = main.c
EXEC = robot
INPUT = laberinto.txt
BACKUP = $(SRC)~

# Fuentes
SOURCES = $(SRC) robot.c mapa.c pila.c glist.c simulacion.c punto.c direccion.c

# Reglas
all: indent $(EXEC) exec

indent: $(SOURCES)
	$(INDENT) $(INDENT_FLAGS) $(SOURCES)

$(EXEC): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC)

exec: $(EXEC)
	./$(EXEC) $(INPUT)

clean:
	rm -f $(BACKUP) $(EXEC)

memcheck: $(EXEC)
	valgrind --leak-check=full -s ./$(EXEC) $(INPUT)
