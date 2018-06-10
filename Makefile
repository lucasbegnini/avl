all : myavl

myavl:	clean main.o avltree.o
	g++	-o myavl main.o avltree.o

main.o:	avlproject.cpp stdafx.h avltree.h
	g++	-o main.o avlproject.cpp -c -W -Wall -ansi -pedantic

avltree.o:	avltree.cpp stdafx.h
	g++	-o avltree.o avltree.cpp -c -W -Wall -ansi -pedantic

clean:
	rm	-rf	*.o myavl teste.out
