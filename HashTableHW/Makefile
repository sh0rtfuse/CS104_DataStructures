CC=g++-4.8
CFLAGS=-c -Wall -std=c++11

all: Q3 Q4 Q5 Q6

Q3: Q3.o HashTable.o
	$(CC) Q3.o HashTable.o -o Q3

Q4: Q4.o 
	$(CC) Q4.o -o Q4

Q5: Q5.o  
	$(CC) Q5.o -o Q5

Q6: Q6.o HashTable.o
	$(CC) Q6.o HashTable.o -o Q6

Q3.o: Q3.cpp
	$(CC) $(CFLAGS) Q3.cpp

Q4.o: Q4.cpp
	$(CC) $(CFLAGS) Q4.cpp

Q5.o: Q5.cpp
	$(CC) $(CFLAGS) Q5.cpp

Q6.o: Q6.cpp
	$(CC) $(CFLAGS) Q6.cpp

HashTable.o: HashTable.cpp HashTable.h
	$(CC) $(CFLAGS) HashTable.cpp

.PHONY: clean

clean:
	rm -rf *o Q3 Q4 Q5 Q6