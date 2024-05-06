PROG = prog
CC = g++
CPPFLAGS = -g -Wall
OBJS = GraphTiming.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

GraphTiming.o : GraphTiming.cpp WGraph.h
	$(CC) $(CPPFLAGS) -c GraphTiming.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
