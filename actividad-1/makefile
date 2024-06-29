# Variables
CC = gcc
CFLAGS = -Wall -Wextra
INDENT = indent
INDENT_FLAGS1 = -kr -brf -i2 -l80 -nut
INDENT_FLAGS = -kr -brf -i2 -nut
SRC = main.c
EXEC = robot
INPUT = laberinto.txt
BACKUP = $(SRC)~

# Reglas
all: indent $(EXEC) exec

indent: $(SRC)
	$(INDENT) $(INDENT_FLAGS) $(SRC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) robot.c mapa.c pila.c glist.c -o $(EXEC)

exec: $(EXEC)
	./$(EXEC) $(INPUT)

clean:
	rm -f $(BACKUP) $(EXEC)

memcheck: $(EXEC)
	valgrind --leak-check=full -s ./$(EXEC) $(INPUT)
