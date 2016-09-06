flags= -Wall -ansi

all: linkedList.o lib 

lib: obj/linkedList.o
	ar r  lib/liblinkedList.a obj/linkedList.o

clean:
	rm -f obj/*.o lib/*.a

linkedList.o:
	gcc -o obj/linkedList.o -c src/linkedList.c
