CC=g++-4.8
CFLAGS=-c -Wall -std=c++11

all: Q3 Q4 Q5

Q3: Q3.o 
	$(CC) Q3.o -o Q3

Q4: Q4.o 
	$(CC) Q4.o -o Q4

Q5: Q5.o 23tree.o 
	$(CC) Q5.o 23tree.o -o Q5

Q3.o: Q3.cpp
	$(CC) $(CFLAGS) Q3.cpp

Q4.o: Q4.cpp
	$(CC) $(CFLAGS) Q4.cpp

Q5.o: Q5.cpp
	$(CC) $(CFLAGS) Q5.cpp

23tree.o: 23tree.cpp 23tree.h
	$(CC) $(CFLAGS) 23tree.cpp

.PHONY: clean

clean:
	rm -rf *o Q3 Q4 Q5