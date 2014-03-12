//Class containing the "rod" object. Consists of a 1D array of values representing (usually) temperature.
#include <Rod.h>

Rod::Rod(int n, double dx, complex* function, complex* ftfunction){
 
    function = new complex[n];
    ftfunction = new complex[n];

    //populate array "function" with x values equal to dx*(the midpoint between n-1 and n)
    for(int i = 0; i < n; i++){
	double x = (i+0.5)*dx;
        function[i] = x; 
    }
};

Rod::~Rod(){
    //delete function;
    //delete ftfunction;
};

std::complex* Rod::getFunction(){
    return function;
};

std::complex* Rod::getFTFunction(){
    return FTfunction;
};


