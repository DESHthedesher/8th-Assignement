//Headerfile for the Rod object
#include <complex>
#include <cmath>

class Rod{
    typedef std::complex<double> complex;	


public:
    Rod(int, double, complex*, complex*);
    complex* getFunction();
    complex* getFTFunction();
    ~Rod();
};

