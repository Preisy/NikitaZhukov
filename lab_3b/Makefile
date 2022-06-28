CC=gcc
CFLAGS=-c -std=c99
DIRS=-Igraph
SOURCES=main.c KeySpaces.c Table.c Utils.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all: $(SOURCES)  $(EXECUTABLE)

.c.o:
	@($(CC) $(DIRS) $(CFLAGS) $< -o $@)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -lm -o $@

clean:
	find -not \( -wholename '*/cmake-build-debug/*' \) -name '*.o' -delete
