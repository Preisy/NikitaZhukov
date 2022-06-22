CC=gcc
CFLAGS= -c -fPIC -std=c99

SOURCES=QueueVector.c QueueList.c Pair.c
OBJECTS=$(SOURCES:.c=.o)
LDFLAGS=-shared

all: $(OBJECTS)
ifdef vector
	@echo 'dynamic vector lib'
	$(CC) Pair.o QueueVector.o -shared -o libqueue.so
else
	@echo 'dynamic list lib'
	$(CC) Pair.o QueueList.o -shared -o libqueue.so
endif


clean:
	rm -rf *.o
	rm -rf *.so

