# Variables generales
CC = gcc
CFLAGS = -Wall -Wextra
INDENT = indent
INDENT_FLAGS = -kr -brf -i2 -nut
EXEC = robot
BACKUP = *.c~

# Archivos de entrada
INPUT_DIR = laberintos
INPUT_FILES = $(wildcard $(INPUT_DIR)/*.txt)

# Fuentes del proyecto
SOURCES = main.c robot.c mapa.c pila.c glist.c simulacion.c punto.c direccion.c

# Selección de archivo de entrada según índice
INPUT_INDEX ?= 1
SELECTED_INPUT := $(word $(INPUT_INDEX), $(INPUT_FILES))

# Reglas
all: indent $(EXEC)

indent: $(SOURCES)
	$(INDENT) $(INDENT_FLAGS) $(SOURCES)

$(EXEC): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC)

run: $(EXEC) $(SELECTED_INPUT)
	./$(EXEC) $(SELECTED_INPUT)

clean:
	rm -f $(BACKUP) $(EXEC)

memcheck: $(EXEC) $(SELECTED_INPUT)
	valgrind --leak-check=full -s --track-origins=yes ./$(EXEC) $(SELECTED_INPUT)

.PHONY: all indent run clean memcheck

# Uso make run INPUT_INDEX=1


# # Variables
# CC = gcc
# CFLAGS = -Wall -Wextra
# INDENT = indent
# INDENT_FLAGS = -kr -brf -i2 -nut
# SRC = main.c
# EXEC = robot
# INPUT1 = laberintos/laberinto.txt
# INPUT2 = laberintos/laberinto2.txt
# INPUT3 = laberintos/laberinto3.txt
# INPUT4 = laberintos/laberinto4.txt
# INPUT5 = laberintos/laberinto5.txt
# INPUT6 = laberintos/laberinto6.txt
# INPUT7 = laberintos/laberinto7.txt
# INPUT8 = laberintos/laberinto8.txt
# INPUT9 = laberintos/laberinto9.txt
# INPUT10 = laberintos/laberinto10.txt
# BACKUP = *.c~

# # Fuentes
# SOURCES = $(SRC) robot.c mapa.c pila.c glist.c simulacion.c punto.c direccion.c

# # Reglas
# all: indent $(EXEC) exec

# indent: $(SOURCES)
# 	$(INDENT) $(INDENT_FLAGS) $(SOURCES)

# $(EXEC): $(SOURCES)
# 	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC)

# exec: $(EXEC)
# 	./$(EXEC) $(INPUT10)

# clean:
# 	rm -f $(BACKUP) $(EXEC)

# memcheck: $(EXEC)
# 	valgrind --leak-check=full -s ./$(EXEC) $(INPUT5)
