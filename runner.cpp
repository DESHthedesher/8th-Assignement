#include <iostream>
#include <complex>
#include <cmath>
#include <fftw3.h>
#include <Constants.h>

//define abnormal types
typedef std::complex<double> complex;

//prototype functions in runner
void fftw(int, complex*, complex*);



int main(int argc, char *argv[] ) {

    //define the arrays which will be acted on by fftw
    complex *function = new complex[n];
    complex *ftfunction = new complex[n];
    
    
    //populate the real space array with valuses derived from constants
    for(int i = 0; i < n; i++){
        double x = (i + 0.5)*dx;
        function[i] = x ;
    };
    
    //call fftw as many time as I say
    for(int i = 0; i < sparktime; i++){
        fftw(n, function, ftfunction);
    }
        
    for(int i = 0; i < n; i++){
        std::cout << function[i] <<","<< ftfunction[i] << std::endl;
    }

    
    
    
    
    delete [] function;
    delete [] ftfunction;
    return 0;
}


void fftw(int n, complex *f, complex *g){
    
    fftw_plan p = fftw_plan_dft_1d(n, (fftw_complex*)f, (fftw_complex*)g, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
    
}
