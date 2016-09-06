FLAGS=-Wall -std=gnu99 -pedantic -O3

all: linkedList.o lib

lib: obj/linkedList.o
	mkdir -p libs
	ar r  libs/liblinkedList.a obj/linkedList.o

clean:
	rm -rf obj libs tests

linkedList.o:
	mkdir -p obj
	gcc $(FLAGS) -c src/linkedList.c -o obj/linkedList.o

tests:
	mkdir -p tests
	gcc $(FLAGS) src/tests/test.c -Llibs -llinkedList -o tests/test
