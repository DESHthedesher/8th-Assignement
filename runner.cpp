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
void printRodT(complex*, int);



int main(int argc, char *argv[] ) {

    //define the arrays which will be acted on by fftw
    complex *heat = new complex[n];
    complex *ftheat = new complex[n];
    
    //define complementary arrays
    double *rod = new double[n];
    complex *firstFTheat = new complex[n];
    double *allk = new double[n];
    
    
    //define other variables
    int step = 0;
    double time = 0;
    
    
    //populate firsthalfk and secondhalfk with appropriate values:
    for(int i = 0; i< n/2 ; i++){
        double k = (2*M_PI*i)/length;
        allk[i] = k;
    }
    
    for(int i = n/2; i < n; i++){
        double k = (2*M_PI*i)/length;
        allk[i] = k;
    }
    
    
    
    //populate the rod with space values
    for(int i = 0; i < n; i++){
        double x = (i + 0.5)*dx;
        rod[i] = x ;
    }
    
    
    //make heat 0 everywwhere in the rod except for halfway down the rod
    for(int i = 0; i < n; i++){
        double y = 0;
        heat[i] = y;
    }
    
    
    
    //call fftw to find the initial fourier tranformed temperature
    
    //inject heat every sparktime steps
    for(int h = 0; h < totaltime/sparktime; h++){
        time = 0;
        heat[n/2] += 1.0;
        fftwf(n, heat, ftheat);
        firstFTheat = ftheat;
        
        
        //call fftw iteratively to solve the system
        for(int i = 0; i < sparktime; i++){
            step += 1;
        
            //modify the first half of the fourier transformed values
            for(int k = 0; k < n; k++){
                double Dkt = -1*diffusivity*pow(allk[k],2.0)*time;
                ftheat[k] = firstFTheat[k]*pow(2.71828182845904523536028747135266249775724709369995,Dkt);
            }

            //reverse the fourier tranform on the evolved values
            fftwb(n, ftheat, heat);
            
            //write out the evolved heat and increase the timestep
            time += dt;
    
        }
        
        
        
        //print the step, time, and T
        printRodT(heat, n);
        std::cout<<"time: "<<time<<std::endl;
        std::cout <<"step"<<step<<"\n\n\n\n"<<std::endl;
    
    }
    
    //cleanup
    delete [] rod;
    delete [] heat;
    delete [] ftheat;
    return 0;
}

void printRodT(complex *f, int n){
    
    for(int i; i < n; i++)
        std::cout << f[i] << std::endl;
        
        
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