#Created by JJ McCauley

PROG = project1
CC = g++
CPPFLAGS = -g -Wall
OBJS = SortTimer.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

SortTimer.o : SortTimer.cpp
	$(CC) $(CPPFLAGS) -c SortTimer.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
