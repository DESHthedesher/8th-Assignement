#include <ONEdField.h>

ONEdField::ONEdField(int n, double dx, double length){

    xvalues = new double[n+2];
    yvalues = new double[n+2];
    firstassociate = new double[n+2]

    //specify initial x values (right now only works for an even numbered array)
    for(int i = 0; i < n+2 ; i++){
	double x = (i + 0.5)*dx;
	xvalues[i] = x;
    }
    
    //specify initial y values (right now this part needs to be programmed by the user for each scenario)
    for(int i = 0; i < n+2 ; i++){
	yvalues[i] = 0;
    }
    
    //populate firsthalfk and secondhalfk with appropriate values:
    for(int i = 0; i< (n+2)/2 ; i++){
        double k = (2*M_PI*i)/length;
        firstassociate[i] = k;
    }
    for(int i = (n+2)/2; i < n+2; i++){
        double k = (2*M_PI*i)/length;
        firstassociate[i] = k;
    }
    
 
}
    