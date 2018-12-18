CC = cc
COPS =

all: a3p1 a3p2 a3p3

a3p1: assign3part1.c 
	$(CC) $(COPS) -o a3p1 assign3part1.c
a3p2: assign3part2.c phypages.c pagetable.c
	$(CC) $(COPS) -o a3p2 assign3part2.c phypages.c pagetable.c
a3p3: assign3part3.c phypages.c pagetable.c 
	$(CC) $(COPS) -o a3p3 assign3part3.c phypages.c pagetable.c -lm
clean:
	rm -f a3p1 a3p2 a3p3 *.o
