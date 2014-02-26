CC=g++-4.8
CFLAGS=-c -Wall -std=c++11

all: main DatabaseGenerator

main: main.o Wallpost.o Wall.o User.o UserList.o WallpostComment.o Sorting.o HashTable.o md5.h
	$(CC) main.o Wallpost.o Wall.o User.o UserList.o WallpostComment.o Sorting.o HashTable.o -o main

DatabaseGenerator: DatabaseGenerator.o Wallpost.o Wall.o User.o UserList.o WallpostComment.o Sorting.o HashTable.o md5.h
	$(CC) DatabaseGenerator.o Wallpost.o Wall.o User.o UserList.o WallpostComment.o Sorting.o HashTable.o -o DatabaseGenerator

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

DatabaseGenerator.o: DatabaseGenerator.cpp
	$(CC) $(CFLAGS) DatabaseGenerator.cpp

Wallpost.o: Wallpost.cpp Wallpost.h
	$(CC) $(CFLAGS) Wallpost.cpp

Wall.o: Wall.cpp Wall.h
	$(CC) $(CFLAGS) Wall.cpp

User.o: User.cpp User.h
	$(CC) $(CFLAGS) User.cpp

UserList.o: UserList.cpp UserList.h
	$(CC) $(CFLAGS) UserList.cpp 

WallpostComment.o: WallpostComment.cpp WallpostComment.h
	$(CC) $(CFLAGS) WallpostComment.cpp

Sorting.o: Sorting.cpp Sorting.h
	$(CC) $(CFLAGS) Sorting.cpp

HashTable.o: HashTable.cpp HashTable.h
	$(CC) $(CFLAGS) HashTable.cpp

.PHONY: clean

clean:
	rm -rf *o main DatabaseGenerator