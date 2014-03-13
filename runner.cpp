#include <iostream>
#include <complex>
#include <cmath>
#include <fftw3.h>
#include <Constants.h>
#include <Writer.h>

//define abnormal types
typedef std::complex<double> complex;

//prototype functions in runner
void fftwf(int, double*, complex*);
void fftwb(int, complex*, double*);
void printComplexArray(complex*, int);
void printRealArray(double*,int);
complex* ComplexBoundaries(complex*, int);
double* Boundaries(double, int);


int main(int argc, char *argv[] ) {
//n+2 data points used to ensure that boundary conditions are not along the "rod of interest"
    
    
    //define the arrays which will be acted on by fftw
    double *heat = new double[n+2];
    complex *ftheat = new complex[n+2];
    
    //define complementary arrays
    double *rod = new double[n+2];
    complex *firstFTheat = new complex[n+2];
    double *allk = new double[n+2];
    
    
    //define other variables
    int step = 0;
    double time = 0;
    complex Dkt;
    double euler = 2.71828182845904523536028747135266249775;
    
    //populate firsthalfk and secondhalfk with appropriate values:
    for(int i = 0; i< (n+2)/2 ; i++){
        double k = (2*M_PI*i)/length;
        allk[i] = k;
    }
    for(int i = (n+2)/2; i < n+2; i++){
        double k = (2*M_PI*i)/length;
        allk[i] = k;
    }
    
    
    
    //populate the rod with space values
    for(int i = 0; i < n+2; i++){
        double x = (i + 0.5)*dx;
        rod[i] = x ;
    }
    
    
    //make heat 0 everywwhere in the rod except for halfway down the rod
    for(int i = 0; i < n+2; i++){
        double y = 0;
        heat[i] = y;
    }
    
    
    
    //inject heat every "sparktime" number of steps
    for(int h = 0; h < totaltime/sparktime; h++){
        time = 0;
        heat[(n+2)/2] += 1.0;
        fftwf(n+2, heat, ftheat);
        firstFTheat = ftheat;
        
        
        //evolve the system in fourier space
        for(int i = 0; i < sparktime; i++){
            step += 1;
        
            //modify the fourier transformed values
            for(int k = 0; k < n+2; k++){
                Dkt = -1*diffusivity*pow(allk[k],2.0)*time;
                ftheat[k] = firstFTheat[k]*pow(euler,Dkt);
            }
          
            //reverse the fourier tranform on the evolved values
            fftwb(n+2, ftheat, heat);
            
            //re-normalize
            for(int i = 0; i < n+2 ; i++){
                double normalValue = heat[i]/(n+2);
                heat[i] = normalValue;
            }
            
            //impose boundary conditions
            //heat = Boundaries(heat, n);
            heat[0] = heat[n];
            heat[n+1] = heat[1];
            
            //re-take the fourier transform
            fftwf(n+2, heat, ftheat);
            
            //increase the timestep
            time += dt;
    
        }
        
        //print the step, time, and T
        printRealArray(heat, n+2);
        std::cout<<"time: "<<time<<std::endl;
        std::cout <<"step"<<step<<"\n\n\n\n"<<std::endl;
        
        
    
    }
    
    //cleanup
    delete [] rod;
    delete [] heat;
    delete [] ftheat;
    return 0;
}


//simple boundary conditions for real arrays
double* Boundaries(double *f, int n){

    f[0] = f[n];
    f[n+1] = f[1];
    return f;
}

//simple boundary conditions for complex arrays
complex* ComplexBoundaries(complex *f, int n){

    f[0] = f[n];
    f[n+1] = f[1];
    return f;
}

//prints the temperature along the rod in real space
void printRealArray(double *f, int n){
    for(int i=0; i<n+2 ; i++){
        std::cout<<f[i]<<std::endl;
    }
    
}

//prints the temperature along the rod in fake space
void printComplexArray(complex *f, int n){
    
    for(int i=0; i < n+2; i++)
        std::cout << f[i] << std::endl;
        
}

//"forward" fourier transforms real array into complex array
void fftwf(int n, double*in, complex*out){
    
    fftw_plan p = fftw_plan_dft_r2c_1d(n, in, (fftw_complex*)out, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
    
}

//"reverse" fourier transforms complex array into real array
void fftwb(int n, complex *in, double *out){
    
    fftw_plan p = fftw_plan_dft_c2r_1d(n, (fftw_complex*)in, out, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
    
}