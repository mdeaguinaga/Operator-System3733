CC=gcc

all: driver1 driver2

driver1: driver1.o myio.o
	$(CC) -o driver1 driver1.o myio.o

driver2: driver2.o myio.o
	$(CC) -o driver2 driver2.o myio.o

myio.o: myio.c myio.h
	$(CC) -c myio.c

driver1.o: driver1.c myio.c
	$(CC) -c driver1.c

driver2.o: driver2.c myio.c
	$(CC) -c driver2.c

clean:
	rm -f *.o driver1 driver2