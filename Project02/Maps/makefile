PROG = prog
CC = g++
CPPFLAGS = -g -Wall
OBJS = MapDemo.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

MapDemo.o : MapDemo.cpp
	$(CC) $(CPPFLAGS) -c MapDemo.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
