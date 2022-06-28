CC=gcc -std=c99
CFLAGS=-c -Isrc -Ilib
LDFLAGS=-Llib -Wl,-Rlib -lqueue
SOURCES=main.c src/RoundRobin.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
