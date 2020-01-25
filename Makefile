CC=gcc
AR=ar
OBJECTS_MAIN=main.o
OBJECTS_LIB=tree.o
FLAGS= -Wall -g

all: frequency

frequency: $(OBJECTS_MAIN) libmytree.a 
	$(CC) $(FLAGS) -o frequency $(OBJECTS_MAIN) libmytree.a 
libmytree.a: $(OBJECTS_LIB) tree.h
	$(AR) -rcs libmytree.a $(OBJECTS_LIB)
tree.o: tree.c tree.h
	$(CC) $(FLAGS) -c -fPIC tree.c
main.o: main.c tree.c tree.h 
	$(CC) $(FLAGS) -c main.c 

.PHONY: clean frequency

clean:
	rm -f *.o *.a frequency
