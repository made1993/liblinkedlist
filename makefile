FLAGS=-Wall -std=gnu99 -pedantic -O3

all: linkedList.o lib tests

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
	gcc $(FLAGS) src/tests/test_create.c -Llibs -llinkedList -o tests/test_create
	gcc $(FLAGS) src/tests/test_insert.c -Llibs -llinkedList -o tests/test_insert
	gcc $(FLAGS) src/tests/test_find.c -Llibs -llinkedList -o tests/test_find
