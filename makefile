flags= -Wall -std=c11 -pedantic

all: linkedList.o lib

lib: obj/linkedList.o
	mkdir lib
	ar r  lib/liblinkedList.a obj/linkedList.o

clean:
	rm -rf obj lib

linkedList.o:
	mkdir obj
	gcc -c src/linkedList.c -o obj/linkedList.o
