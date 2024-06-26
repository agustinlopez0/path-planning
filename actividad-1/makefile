CC = gcc
CFLAGS = -Wall -Wextra
INDENT = indent
INDENT_FLAGS = -kr -brf -i2 -l80 -nut
SRC = main.c
EXEC = robot
INPUT = laberinto.txt
BACKUP = $(SRC)~

all: indent $(EXEC) exec

indent: $(SRC)
	$(INDENT) $(INDENT_FLAGS) $(SRC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

exec: $(EXEC)
	./$(EXEC) $(INPUT)

clean:
	rm -f $(BACKUP) $(EXEC)
