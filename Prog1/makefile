all: prog1generator prog1sorter

prog1generator: prog1generator.o getArgs.o
	gcc prog1generator.o getArgs.o -o prog1generator

prog1generator.o: prog1generator.c 
	gcc -c -g prog1generator.c -o prog1generator.o

prog1sorter: prog1sorter.o timeval.o getArgs.o
	gcc timeval.o prog1sorter.o getArgs.o -o prog1sorter

prog1sorter.o: prog1sorter.c
	gcc -c prog1sorter.c -o prog1sorter.o

timeval: timeval.o
	gcc timeval.o -o timeval

timeval.o: timeval.c
	gcc -c timeval.c -o timeval.o

getArgs: getArgs.o
	gcc getArgs.o -o getArgs

getArgs.o: getArgs.c
	gcc -c getArgs.c -o getArgs.o

clean:
	rm *.o
	rm -f prog1generator
	rm -f prog1sorter
