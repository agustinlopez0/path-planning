CC = gcc
CFLAGS = -Wall -Wextra
EXEC = robot
SOURCES = robot.c mapa.c colaprioridad.c bheap.c glist.c
SENSOR_EXEC = sensor

$(EXEC): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC)

$(SENSOR_EXEC): sensor.c
	$(CC) $(CFLAGS) sensor.c -o $(SENSOR_EXEC)

clean:
	rm -f $(EXEC) $(EXEC2) $(SENSOR_EXEC) feedback a.out *~

