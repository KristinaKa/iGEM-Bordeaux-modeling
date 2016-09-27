#ifndef __COSTANTS__
#define __COSTANTS__

/** General model constants **/

const float t = 3; // simulation time in hours
const float dt = 0.1;
const int INIT_BACT_NB= 50;

/** Lattice **/

const int LENGTH= 100; 
const int HEIGHT= 100;

/** Square **/

const float INIT_SUBSTRATE= 10000.0; //random number
const int MAX_STACK_NB= 4;

/** Bacteria **/

const float MEDIAN_CELL_VOLUME= 0.4; //median cell volume at growth rate = 0, Bacsim reference
const float MINIMAL_CELL_VOLUME= 0.1; //Bacsim reference
const float VOLUME_AT_DIVISION= 0.5; //Bacsim reference (5 times the minimal cell volume)
const float INIT_DRY_MASS= 290; //Bacsim
const float INIT_VOLUME= 0.4; //Bacsim
const float umax = 0.0205; 
const float Ymax = 0.4444; 
const float Vmax = umax/Ymax;
const float Km = 2.34*pow(10,3);
const float m = 6*pow(10,-4);


#endif