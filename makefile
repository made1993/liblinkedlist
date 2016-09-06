FLAGS=-Wall -std=gnu99 -pedantic -O3

all: linkedList.o lib

lib: obj/linkedList.o
	mkdir -p lib
	ar r  lib/liblinkedList.a obj/linkedList.o

clean:
	rm -rf obj lib

linkedList.o:
	mkdir -p obj
	gcc $(FLAGS) -c src/linkedList.c -o obj/linkedList.o
