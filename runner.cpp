#include <Rod.h>
#include <iostream>
#include <complex>
#include <cmath>
#include <fftw3.h>
typedef std::complex<double> complex;

int main() {
    int n = 16384;
    double len = 60, dx = len/n ;
    complex *f = new complex[n];
    complex *g = new complex[n];
    for(int i = 0; i < n; i++){
        double x = (i - n/2 +1.05e-5)*dx;
        f[i] = sin(x)/x ;
}

fftw_plan p = fftw_plan_dft_1d(n, (fftw_complex*)f, (fftw_complex*)g, FFTW_FORWARD, FFTW_ESTIMATE);
fftw_execute(p);
fftw_destroy_plan(p);

for(int i = 0; i < n; i++){
    std::cout << f[i] <<","<< g[i] << std::endl;
}

delete [] f;
delete [] g;
return 0;
}
