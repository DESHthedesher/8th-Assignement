//writes everything to a data file
//
//headerfile for writer class. functions contained in writer.cpp
//
//
//

#include <fstream>
#include <iostream>

class Writer {
private:
    std::string dataFilename;
    std::ofstream dataFile;

public:
    Writer(double *, double, int);
    void metaWrite(int, int, double, double);
    void writeLine(double *, double, int);
    void printLine(double *, int);
    ~Writer();
    
};

