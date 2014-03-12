CPP = g++

cflags = -O2 -I. -Wall

libraries = -lfftw3


all: Hotrod

example: example.cpp
	g++ -O2 -Wall -o example example.cpp -lfftw3

Hotrod: runner.o
	${CPP} ${cflags} -o Hotrod runner.o ${libraries} 

Rod.o: Rod.cpp
	${CPP} ${cflags} -c Rod.cpp

runner.o: runner.cpp
	${CPP} ${cflags} -c runner.cpp

clean:
	rm -rf Rod.o runner.o Hotrod example
