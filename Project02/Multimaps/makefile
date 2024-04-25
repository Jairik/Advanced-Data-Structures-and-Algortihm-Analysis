PROG = prog
CC = g++
CPPFLAGS = -g -Wall
OBJS = Miltimap.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

Miltimap.o : Miltimap.cpp
	$(CC) $(CPPFLAGS) -c Miltimap.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
