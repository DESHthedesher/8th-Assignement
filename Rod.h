//Headerfile for the Rod object

#include <cmath>

class Rod{
    typedef std::complex<double> complex;	


public:
    Rod(int, double, complex*, complex*);
    complex* getFunction();
    complex* getFTFunction();
    ~Rod();
};



//creates and evolves the density field

#include <iostream>
#include <cmath>
#include "constants.h"

class field {
private:
        // Simulation parameters from constants
        //extern const float x1;
        //extern const float x2;
        //extern const float D;
        //extern const int numPoints;
        //extern const int numSteps;
        //extern const int plotEvery;


        // Parameters of the initial density from contants
        //extern const float a0;
        //extern const float sigma0;
    
    
        // Data structures    
        float *x;
        // rho: previous timestep, current timestep
        float *rho_0, *rho_1;
        float *temp;
        float time;
        int step;
        float dt, dx;

public:
        field();
        void nextStep();
        float *getCurrentrho();
        float getCurrentTime();
        ~field();    
};

