CC = cc
COPS =

all: assign1-0 assign1 runall

assign1-0: assign1-0.c pslibrary.c
	$(CC) $(COPS) -o assign1-0 assign1-0.c pslibrary.c

assign1: assign1.c pslibrary.c
	$(CC) $(COPS) -o assign1 assign1.c pslibrary.c

runall: runall.c pslibrary.c
	$(CC) $(COPS) -o runall runall.c pslibrary.c
clean:
	rm -f assign1-0 assign1 *.o
