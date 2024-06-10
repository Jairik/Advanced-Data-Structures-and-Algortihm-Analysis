PROG = prog
CC = g++
CPPFLAGS = -g -Wall
OBJS = MultisetDemo.o 

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

MultisetDemo.o : MultisetDemo.cpp
	$(CC) $(CPPFLAGS) -c MultisetDemo.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
