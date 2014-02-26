CC=g++-4.8
CFLAGS=-c -Wall

all: main

main: main.o List.o Wall.o WallPost.o User.o UserList.o
	$(CC) main.o Wall.o WallPost.o List.o User.o UserList.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Wall.o: Wall.cpp Wall.h
	$(CC) $(CFLAGS) Wall.cpp

WallPost.o: WallPost.cpp WallPost.h
	$(CC) $(CFLAGS) WallPost.cpp

List.o: List.cpp List.h
	$(CC) $(CFLAGS) List.cpp

User.o: User.cpp User.h
	$(CC) $(CFLAGS) User.cpp

UserList.o: UserList.cpp UserList.h
	$(CC) $(CFLAGS) UserList.cpp

.PHONY: clean

clean:
	rm -rf *o main