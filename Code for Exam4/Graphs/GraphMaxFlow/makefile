PROG = prog
CC = g++
CPPFLAGS = -g -Wall
OBJS = GraphMaxFlow.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

GraphMaxFlow.o : GraphMaxFlow.cpp
	$(CC) $(CPPFLAGS) -c GraphMaxFlow.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
