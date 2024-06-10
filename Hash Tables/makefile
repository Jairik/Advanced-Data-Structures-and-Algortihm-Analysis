PROG = prog
CC = g++
CPPFLAGS = -g -Wall
OBJS = HashTableExample.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

HashTableExample.o : HashTableExample.cpp ListOfLists.h HashTable.h
	$(CC) $(CPPFLAGS) -c HashTableExample.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
