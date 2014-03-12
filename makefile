CPP = g++

cflags = -O0 -I. -Wall -c


Rod.o: Rod.cpp
	${CPP} ${cflags} Rod.cpp

clean:
	rm -rf Rod.o 
