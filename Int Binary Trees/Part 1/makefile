#Created by Don Spickler  1/28/2022

PROG = main
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = main.o IntBinaryTree.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o : main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

IntBinaryTree.o : IntBinaryTree.cpp IntBinaryTree.h
	$(CC) $(CPPFLAGS) -c IntBinaryTree.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
