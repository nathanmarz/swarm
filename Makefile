CC = /usr/bin/g++
CPPFLAGS = -D_REENTRANT -Wno-deprecated $(PATHI)


OBJS = swarm.o swarmroutes.o

MYTEST_OBJS = mytest.o 

all: $(OBJS)
	$(CC) $(FRAMEWORK) $^ -o swarm -lcurses

clean:
	rm -f *.o swarm
