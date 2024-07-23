
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

# indent: $(SOURCES)
# 	$(INDENT) $(INDENT_FLAGS) $(SOURCES)

# $(EXEC): $(SOURCES)
# 	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC)

robot:
	gcc -Wall -Wextra robot.c pila.c punto.c matriz_bi.c glist.c direccion.c funcioneslistas.c -o robot

sensor: 
	gcc -Wall -Wextra sensor.c -o sensor

# exec: $(EXEC)
# 	./$(EXEC) $(INPUT10)

clean:
	rm robot sensor feedback a.out

# memcheck: $(EXEC)
# 	valgrind --leak-check=full -s ./$(EXEC) $(INPUT5)

