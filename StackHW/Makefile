CC=g++-4.8
CFLAGS=-c -Wall

all: main main2

calc: main

vectordemo: main2

main: main.o Vector.o Stack.o LinkedList.o Node.o
	$(CC) main.o Vector.o Stack.o LinkedList.o Node.o -o main

main2: main2.o Vector.o Stack.o LinkedList.o Node.o
	$(CC) main2.o Vector.o Stack.o LinkedList.o Node.o -o main2

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

main2.o: main2.cpp
	$(CC) $(CFLAGS) main2.cpp

Vector.o: Vector.cpp Vector.h
	$(CC) $(CFLAGS) Vector.cpp

Stack.o: Stack.cpp Stack.h
	$(CC) $(CFLAGS) Stack.cpp

LinkedList.o: LinkedList.cpp LinkedList.h
	$(CC) $(CFLAGS) LinkedList.cpp

Node.o: Node.cpp Node.h
	$(CC) $(CFLAGS) Node.cpp

clean:
	rm -rf *o main