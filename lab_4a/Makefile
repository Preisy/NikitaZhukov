CC=gcc
CFLAGS=-c -std=c99
DIRS=-Icontroller -Itree -Iview
SOURCES=main.c \
	controller/TreeController.c \
	tree/Tree.c \
	tree/Node.c \
	view/Dialog.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all: $(SOURCES)  $(EXECUTABLE)

.c.o:
	@($(CC) $(DIRS) $(CFLAGS) $< -o $@)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -lreadline -o $@

clean:
	find -not \( -wholename '*/cmake-build-debug/*' \) -name '*.o' -delete