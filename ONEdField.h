

class ONEdField{
private:
    //the "main" field components. x values are basically just grispacing. 
    //Y values are the corresponding field values
    double *yvalues;
    double *xvalues;
    
    //associate arrays, because sometimes it's useful to have them
    double *firstassociate;
    double *secondassociate;
    
  
public:
    ONEdField(int, double);
    ~ONEdField();

};
