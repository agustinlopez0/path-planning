# Variables
CC = gcc
CFLAGS = -Wall -Wextra
INDENT = indent
INDENT_FLAGS = -kr -brf -i2 -nut
SRC = main.c
EXEC = robot
INPUT1 = laberinto.txt
INPUT2 = laberinto2.txt
INPUT3 = laberinto3.txt
INPUT4 = laberinto4.txt
INPUT5 = laberinto5.txt
INPUT6 = laberinto6.txt
BACKUP = *.c~

# Fuentes
SOURCES = $(SRC) robot.c mapa.c pila.c glist.c simulacion.c punto.c direccion.c

# Reglas
all: indent $(EXEC) exec

indent: $(SOURCES)
	$(INDENT) $(INDENT_FLAGS) $(SOURCES)

$(EXEC): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC)

exec: $(EXEC)
	./$(EXEC) $(INPUT5)

clean:
	rm -f $(BACKUP) $(EXEC)

memcheck: $(EXEC)
	valgrind --leak-check=full -s ./$(EXEC) $(INPUT5)
