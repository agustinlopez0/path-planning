# Variables
CC = gcc
CFLAGS = -Wall -Wextra
INDENT = indent
INDENT_FLAGS = -kr -brf -i2 -nut
SRC = main.c
EXEC = robot
INPUT1 = laberintos/laberinto.txt
INPUT2 = laberintos/laberinto2.txt
INPUT3 = laberintos/laberinto3.txt
INPUT4 = laberintos/laberinto4.txt
INPUT5 = laberintos/laberinto5.txt
INPUT6 = laberintos/laberinto6.txt
INPUT7 = laberintos/laberinto7.txt
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
