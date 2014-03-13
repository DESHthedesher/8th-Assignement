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
Writer::Writer(double *y_value, double time, int numPoints){
    
    //make the file
    dataFilename = "data.dat";
    dataFile.open(dataFilename.c_str());
    
    //write initial rho and time
    dataFile << "Initial time: "<< time << "\n";
    dataFile << "Initial y values: "<<"\n";
    for(int i = 0; i < numPoints + 2; i++ ) 
        dataFile << y_value[i] << " ";
    dataFile << "\n";
}

//Writes "meta" data abou the output
void Writer::metaWrite(int numPoints, int plotEvery, double pointSpacing, double timeStepSize){
    dataFile << "Number of gridpoints: " << numPoints << std::endl;
    dataFile << "Spacing of gridpoints: " << pointSpacing << std::endl;
    dataFile << "Size of timestep: " << timeStepSize << std::endl;
    dataFile << "Dataout written every N steps, with N = "<<plotEvery<< std::endl;
}


//Writes a line when given an arry and a float
void Writer::writeLine(double *y_value, double time, int numPoints){
    
    
    //write time and rho
    dataFile << time << "\n";
    for(int i = 0; i < numPoints + 2; i++ ) 
        dataFile << y_value[i] << " ";
    dataFile << "\n";
   
    
}

//Prints all the values in an array *f of length n+2
void Writer::printLine(double*f, int n){

    for(int i=0; i<n+2; i++){
        std::cout<<f[i]<<std::endl;
    }

}
    
//Destructor for Writer
Writer::~Writer(){
    dataFile.close();
};
