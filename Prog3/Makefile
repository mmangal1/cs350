all: prog3ipc

prog3ipc: prog3ipc.o
	gcc prog3ipc.o -o prog3ipc -lrt

prog3ipc.o: prog3ipc.c
	gcc -c prog3ipc.c -o prog3ipc.o

clean:
	rm -f *.o
	rm -f prog3ipc
