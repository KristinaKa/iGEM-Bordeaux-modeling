#include "bacterium.hpp"
#include "constants.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h> 
#include "lattice.hpp"
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <stdbool.h>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

#define DEBUG(x) std::cout << "DEBUG : " << x << "  - line : "<< __LINE__ << " - file : " << __FILE__ << std::endl;

float dt;
float p_seg_loss;
float plasmid_cost;

Bacterium::Bacterium(int id, Square* _pSquare, int last_used_stack, double mass_at_division){
	square_id = id ;
	pSquare = _pSquare;
	stack_id = last_used_stack;
	dry_mass = INIT_DRY_MASS; 
	mr = mass_at_division;
	U = 0;
	tbact = 0;
	dividing = false;
}
	
Bacterium::~Bacterium(){}



void Bacterium::set_level_id(int n){
	
	stack_id = n;
	
}

int Bacterium::get_level_id(){
	
	return stack_id;
	
}

float Bacterium::get_dry_mass(){
	
	return dry_mass;
	
}

bool Bacterium::has_to_die(){
	
	if (dry_mass <= MINIMAL_DRY_MASS){
		
		return(true);
	}
	
	return(false);
	
}



int Bacterium::divide(Lattice &lat){

	std::vector<int> potential_sites_of_division_ids = lat[square_id].get_neighbor_square_ids();

	while (potential_sites_of_division_ids.size()!=0){

		int new_square_id_index = rand() % potential_sites_of_division_ids.size();

		if (lat[potential_sites_of_division_ids[new_square_id_index]].is_full()){

			potential_sites_of_division_ids.erase(potential_sites_of_division_ids.begin()+new_square_id_index);

		}
		else{
			// division is possible 

			return(potential_sites_of_division_ids[new_square_id_index]);			
		}

	}
	return -1;	
}


int Bacterium::get_square_id(){
  
  return square_id;
}




void Bacterium::uptake(Lattice &lattice){

	//float U; // number of nutrients per timestep that is going to be consummed
	double Z; // a random value centered around mean Umax and std deviantion std_u
	float S; // surface : contact from where the nutriments are going to be absorbed 
	float c; // a normalization constant	
	
	c = pow(((36*M_PI)/pow(p,2)),1/3);
	
	S = c * pow(dry_mass,2/3);


  	boost::mt19937 rng; 

  	boost::normal_distribution<> nd(Umax_mean, std_dev_Umax);

  	boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > var_nor(rng, nd);

	Z = var_nor();

	U = Z * S;


	float substrate = lattice[square_id].get_substrate();

	float substrate_consummed = k * substrate;
	
	
	if (U>=substrate_consummed){
		
		U = substrate_consummed;
		lattice[square_id].diminish_substrate(U);

	}	
	
	else{

		lattice[square_id].diminish_substrate(U);
	}


}

void Bacterium::metabolism(Lattice &lat){

	float E = dry_mass * I; // maintenance energy

	if (U >= E){


		float B = ( U - dry_mass*I)*Y;
		dry_mass = dry_mass + B;

	}

}

void Bacterium::check_entering_division(){

	if ( dry_mass > mr ){
		dividing = true;

	}
}

int Bacterium::check_divide(){
	
	if (tbact > tr){
		dividing = false;
		return 1;
	}

	return 0;
}

void Bacterium::update_time(){

	if (dividing==true){
		tbact = tbact + dt;
	}

}


void Bacterium::set_dry_mass(float m){
	
	dry_mass = m;

}

int Bacterium::square_to_move_to(Lattice &lat){

	for (int i = 0; i < neighbor_square_ids.size();i++){
		if (lat[neighbor_square_ids[i]].is_full()){
		}
		else{
			return neighbor_square_ids[i];	
		}

	}


	return -1; // return -1 if there is no free square 
}


void Bacterium::set_type(std::string t){

		type=t;

}

std::string Bacterium::get_type(){
		return type;

}
void Bacterium::set_stack_id(int n){
		
		stack_id = n;
			
}

int Bacterium::get_stack_id(){
		
		return stack_id;
			
}

bool Bacterium::conjugation(Lattice &lat){

	std::vector<int> neighbor_square_ids = lat[square_id].get_neighbor_square_ids();

	for (int i=0; i<neighbor_square_ids.size(); i++){

		int square_id = neighbor_square_ids[i];

		if (lat[square_id].give_plasmid_to_bacteria(stack_id)==true){
		
			return true;
		}	

	}

	return false;
}

void Bacterium::segregation_loss(){

	float p = get_uniform_double(0.0,1.0);
	if (p <= p_seg_loss){

		type="R";	

	}
	else{
		
		type="D";
	} 
		
}

void Bacterium::set_square_id(int n){

	square_id = n;

}
