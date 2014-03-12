#include <iostream>
#include <complex>
#include <cmath>
#include <fftw3.h>
#include <Constants.h>

//define abnormal types
typedef std::complex<double> complex;

//prototype functions in runner
void fftwf(int, complex*, complex*);
void fftwb(int, complex*, complex*);



int main(int argc, char *argv[] ) {

    //define the arrays which will be acted on by fftw
    complex *heat = new complex[n];
    complex *ftheat = new complex[n];
    
    //define complementary arrays
    double *rod = new double[n];
    complex *firstFTheat = new complex[n];
    double *firsthalfk = new double[n/2];
    double *secondhalfk = new double[n/2];
    
    
    //define other variables
    int time = 0;
    
    
    
    
    
    //populate the rod with space values
    for(int i = 0; i < n; i++){
        double x = (i + 0.5)*dx;
        rod[i] = x ;
    }
    
    
    //add a heat value of "1" in the middle of the rod, and 0 everywhere else
    for(int i = 0; i < n; i++){
        double y = 0;
        heat[i] = y;
    }
    heat[n/2] = 1.0;
    
    
    
    //call fftw to find the initial fourier tranformed temperature
    fftwf(n, heat, ftheat);
    firstFTheat = ftheat;
    
    
    //call fftw iteratively to solve the system
    for(int i = 0; i < sparktime; i++){
        fftwf(n, heat, ftheat);
        
        //modify the first half of the fourier transformed values
        for(int k = 0; k < n/2; k++){
            double Dkt = -1*diffusivity*pow(firsthalfk[k],2)*time;
            ftheat[k] = firstFTheat[k]*pow(2.7182818,Dkt);
        }
        
        //modify the second half of the fourier transformed values
    }
    
    
    
    //print out the final temperature profile of the rod
    for(int i = 0; i < n; i++){
        std::cout << heat[i] <<","<< ftheat[i] << std::endl;
    }

    
    //cleanup
    delete [] rod;
    delete [] heat;
    delete [] ftheat;
    return 0;
}


void fftwf(int n, complex *f, complex *g){
    
    fftw_plan p = fftw_plan_dft_1d(n, (fftw_complex*)f, (fftw_complex*)g, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
    
}

void fftwb(int n, complex *f, complex *g){
    
    fftw_plan p = fftw_plan_dft_1d(n, (fftw_complex*)f, (fftw_complex*)g, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
    
}