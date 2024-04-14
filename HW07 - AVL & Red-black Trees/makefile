PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = TreeTimer.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

TreeTimer.o : TreeTimer.cpp
	$(CC) $(CPPFLAGS) -c TreeTimer.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
