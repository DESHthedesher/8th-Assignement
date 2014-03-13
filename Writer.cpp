//
//Writer.cpp
//
//belongs to the class Writer (Writer.h)
//
//constructs a datafile and writes to it. Designed for use with general time 
//evolution problems involving an array of "y" values
//
//


#include "Writer.h"

//Constructor. Writes first line
Writer::Writer(float *y_value, float time, int numPoints){
    
    //make the file
    dataFilename = "data.dat";
    dataFile.open(dataFilename.c_str());
    
    //write initial rho and time
    dataFile << time << "\n";
    for(int i = 0; i < numPoints + 2; i++ ) 
        dataFile << y_value[i] << " ";
    dataFile << "\n";
}

//Writes "meta" data abou the output
void Writer::metaWrite(int numPoints, int plotEvery, double pointSpacing, double timeStepSize){
    dataFile << "Number of gridpoints: " << numPoints << "";
    dataFile << "Spacing of gridpoints: " << pointSpacing << "";
    dataFile << "Size of timestep: " << timeStepSize << "";
    dataFile << "Dataout written every N steps, with N = "<<plotEvery<< "";
}


//Writes a line when given an arry and a float
void Writer::writeLine(float *y_value, float time, int numPoints){
    
    
    //write time and rho
    dataFile << time << "\n";
    for(int i = 0; i < numPoints + 2; i++ ) 
        dataFile << y_value[i] << " ";
    dataFile << "\n";
   
    
}
    
//Destructor for Writer
Writer::~Writer(){
    dataFile.close();
};