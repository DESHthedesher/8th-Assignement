//contains constants intended for use with runner

//number of gripoints
const int n = 40;

//coefficient of diffusivity
const double D = 10.0;

//the length of the rod
const double length = 2.0;

//size of a gridpoint
const double dx = length/n;

//the point that is heated on the rod
const int hotGridpoint = floor(n/2);

//timestep size
const double dt = 0.0001;

//number of timesteps before the rod is heated
const int sparktime = 10;
