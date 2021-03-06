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



int main(int argc, char *argv[] ) {
//n+2 data points used to ensure that boundary conditions are not along the "rod of interest"
    
    
////////////////////////////////////////////////////////////////////////
//////////This first section mainly consists of creating////////////////
//////////all the variables, and should be in it's own class////////////
//////////in the world where time grows on trees////////////////////////
////////////////////////////////////////////////////////////////////////    
    
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
 
/////////////////////////////////////////////////////////////////////////
/////////////end of the "class" initialization///////////////////////////
/////////////////////////////////////////////////////////////////////////   
    
    
    // Initialize Writer Class
    Writer W(heat, time, n);
    W.metaWrite( n, plotEvery, dx, dt );
   
    
    //inject heat at every "sparktime" number of steps
    for(int h = 0; h < totaltime/sparktime; h++){
        heat[(n+2)/2] += heatinject;
        double timesincespark = 0;
        fftwf(n+2, heat, ftheat);
        firstFTheat = ftheat;
        
        
        //evolve the system in fourier space
        for(int i = 0; i < sparktime; i++){
            step += 1;
            
            //take the fourier transform
            fftwf(n+2, heat, ftheat);
        
            //modify the fourier transformed values
            for(int k = 0; k < n+2; k++){
                Dkt = -1*diffusivity*pow(allk[k],2.0)*timesincespark;
                ftheat[k] = firstFTheat[k]*pow(euler,Dkt);
            }
          
            //reverse the fourier transform on the evolved values
            fftwb(n+2, ftheat, heat);
            
            //re-normalize
            for(int i = 0; i < n+2 ; i++){
                double normalValue = heat[i]/(n+2);
                heat[i] = normalValue;
            }
            
            //impose boundary conditions
            heat[0] = heat[n];
            heat[n+1] = heat[1];
            
            //increase the timestep and write to file
            time += dt;
            timesincespark += dt;
            if(step % plotEvery == 0){
                W.writeLine(heat, time, n);
            }
                
        }
        
        //print the current array
        W.printLine(heat, n+2);
        
        
        
    }
    
    //cleanup
    delete [] rod;
    delete [] heat;
    delete [] ftheat;
    delete [] allk;
    return 0;
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