#ifndef __CONSTANTS__
#define __CONSTANTS__

const int LENGTH= 300; 
const int HEIGHT= 300; 

const int MAX_STACK_NB = 4;

//const double k = 0.5; //probability of nutriments actually being absorbed by bacteria during uptake
const double k = 1; //probability of nutriments actually being absorbed by bacteria during uptake
const double p = 1; // mass density (masse volumique)
const double Y = 1; // metabolic efficiency (synthetized biomass per metabolized nutrients particles )
const float I = 0.0070; // prescribed number of nutrient particles per unit of biomass or surface or both to maintain a minimum state of the bacteria
const double tr = 41.9; // in minutes
const double dt = 4.19; // minutes

const double pmov = 0.5;

const double Umax_mean = 315; 
const double std_dev_Umax = 0.3;
const float Mr_mean = 15000;
const double std_dev_Mr = 0.4;

const double mr_min = 5000;


// dmax 
// Dmax


#endif
