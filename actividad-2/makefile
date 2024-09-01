
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
# SOURCES = $(SRC)

# # Reglas
# all: $(EXEC)

indent:
	indent -kr -brf -i2 -nut robot.c pila.c punto.c matriz.c glist.c direccion.c funcioneslistas.c

# $(EXEC): $(SOURCES)
# 	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC)

robot:
	gcc -Wall -Wextra robot.c matriz.c colaprioridad.c bheap.c -o robot
	
robot2:
	gcc -Wall -Wextra robot2.c matriz_bi.c -o robot2

sensor: 
	gcc -Wall -Wextra sensor.c -o sensor

# exec: $(EXEC)
# 	./$(EXEC) $(INPUT10)

clean:
	rm robot sensor feedback a.out *~

# memcheck: $(EXEC)
# valgrind --leak-check=full -s ./$(EXEC) $(INPUT5)

