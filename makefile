CPP = g++

cflags = -O2 -I. -Wall

libraries = -lfftw3


all: Hotrod

example: example.cpp
	g++ -O2 -Wall -o example example.cpp -lfftw3

Hotrod: runner.o Writer.o 
	${CPP} ${cflags} -o Hotrod runner.o Writer.o ${libraries} 

Writer.o: Writer.cpp
	${CPP} ${cflags} -c Writer.cpp

runner.o: runner.cpp
	${CPP} ${cflags} -c runner.cpp

clean:
	rm -rf runner.o Writer.o data.dat Hotrod example
