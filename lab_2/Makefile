CC=gcc -std=c99
CFLAGS=-c -Wall -Isrc -Ilib
LDFLAGS=-Isrc -Ilib
SOURCES=main.c src/RoundRobin.c lib/QueueVector.c lib/pair.c src/Item.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

#clean:
#	rm -rf *.o;