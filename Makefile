CC = gcc
CFLAGS = -g -Wall

# Compile mymalloc.c into an object file (mymalloc.o)
mymalloc.o: mymalloc.c
	$(CC) $(CFLAGS) -c mymalloc.c -o mymalloc.o

# Link the object files (mymalloc.o and memgrind.c) into the final executable
memgrind: memgrind.c
	$(CC) $(CFLAGS) -o memgrind memgrind.c

clean:
	rm -f mymalloc.o memgrind

test: memgrind
	  ./memgrind
