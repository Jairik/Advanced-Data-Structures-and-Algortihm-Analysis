PROG = prog
CC = g++
CPPFLAGS = -g -Wall
OBJS = TreeTiming.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

TreeTiming.o : TreeTiming.cpp
	$(CC) $(CPPFLAGS) -c TreeTiming.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
