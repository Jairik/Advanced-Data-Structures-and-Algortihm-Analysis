PROG = prog
CC = g++
CPPFLAGS = -g -Wall
OBJS = SetDemo.o MultisetDemo.o 

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

MultisetDemo.o : MultisetDemo.cpp
	$(CC) $(CPPFLAGS) -c MultisetDemo.cpp

SetDemo.o : SetDemo.cpp
	$(CC) $(CPPFLAGS) -c SetDemo.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
