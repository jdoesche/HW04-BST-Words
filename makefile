CC = g++
CFLAGS = -g -Wall -Wextra

default: BST

BST: BST.o main.o
	$(CC) $(CFLAGS) -o bst BST.o main.o

BST.o: BST.cpp BST.h
	$(CC) $(CFLAGS) -c BST.cpp

main.o: main.cpp BST.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	$(RM) bst *.o *~