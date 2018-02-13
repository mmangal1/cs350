all: prog2tree

prog2tree: prog2tree.o
	gcc prog2tree.o -o prog2tree

prog2tree.o : prog2tree.c
	gcc -c prog2tree.c -o prog2tree.o

clean:
	rm *.o
	rm -f prog2tree
