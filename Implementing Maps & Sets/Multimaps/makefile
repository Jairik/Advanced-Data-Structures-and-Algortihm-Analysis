PROG = prog
CC = g++
CPPFLAGS = -g -Wall
OBJS = MiltimapDemo.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

MiltimapDemo.o : MiltimapDemo.cpp
	$(CC) $(CPPFLAGS) -c MiltimapDemo.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
