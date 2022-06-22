CC=gcc
CFLAGS=-c -std=c99
DIRS=-Icontroller/dialog -Imodel/tree/binary -Icontroller/graph
SOURCES=main.c controller/dialog/Dialog.c tree/BinaryTree.c tree/BNode.c controller/graph/GraphGenerator.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all: $(SOURCES)  $(EXECUTABLE)

.c.o:
	@($(CC) $(DIRS) $(CFLAGS) $< -o $@)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -lreadline -o $@

clean:
	find -not \( -wholename '*/cmake-build-debug/*' \) -name '*.o' -delete