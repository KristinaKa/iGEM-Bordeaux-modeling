#ifndef __CONSTANTS__
#define __CONSTANTS__


/** General model constants **/


const double k = 1; //probability of nutrients actually being absorbed by bacteria during uptake
const double p = 1; // mass density
const double Y = 1; // metabolic efficiency (synthetized biomass per metabolized nutrients particles )
const float I = 0.0070; // prescribed number of nutrient particles per unit of biomass or surface or both to maintain a minimum state of the bacteria
const double tr = 20; // time of division

const double Umax_mean = 315; // mean value to determine Umax via a gaussian distribution 
const double std_dev_Umax = 0.3; 

const float Mr_mean = 15000; // mean value to determine mr via a gaussian distribution
const double std_dev_Mr = 0.4; 

const double mr_min = 5000; // the random mr determined cannot be lower than mr_min

const double INIT_DRY_MASS = 2663.4;
const double MINIMAL_DRY_MASS = 266; // valeur au pif ( j'ai mis 10 % de la masse initiale 

/** Others **/

const float p_move = 1;

#endif
