CC=g++-4.8
CFLAGS=-c -Wall

all: main

main: main.o PQueue.o List.o
	$(CC) main.o PQueue.o List.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

List.o: List.cpp List.h
	$(CC) $(CFLAGS) List.cpp

PQueue.o: PQueue.cpp PQueue.h
	$(CC) $(CFLAGS) PQueue.cpp

.PHONY: clean

clean:
	rm -rf *o main