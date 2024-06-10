PROG = prog
CC = g++
CPPFLAGS = -g -Wall
OBJS = SetDemo.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

SetDemo.o : SetDemo.cpp
	$(CC) $(CPPFLAGS) -c SetDemo.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
