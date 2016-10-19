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


#define DEBUG(x) std::cout << "DEBUG : " << x << "  - line : "<< __LINE__ << " - file : " << __FILE__ << std::endl;

float dt;
float p_seg_loss;
float plasmid_cost;

Bacterium::Bacterium(int id, Square* _pSquare, int last_stack_level_used){
	square_id = id ;
	pSquare = _pSquare;
	volume = INIT_VOLUME;
	stack_id = last_stack_level_used;
	dry_mass = INIT_DRY_MASS;
	type="R"; // by default, bacteria are recipients
}


	
Bacterium::~Bacterium(){}

void Bacterium::metabolism( Lattice lattice){

	float substrate = lattice[square_id].get_substrate();
	
	float uptake = dry_mass * Vmax * substrate/(Km+substrate);
	lattice[square_id].reduce_substrate(uptake, dt);
	float late_dry_mass = dry_mass;
	dry_mass = dry_mass + dt*uptake/Ymax - dt*dry_mass*m*Ymax;
	growth = ((dry_mass - late_dry_mass)/dt);

}


void Bacterium::set_stack_id(int n){
	
	stack_id = n;
	
}


void Bacterium::set_type(std::string t){

	type=t;

}

std::string Bacterium::get_type(){
	return type;

}

int Bacterium::get_stack_id(){
	
	return stack_id;
	
}

float Bacterium::get_dry_mass(){
	
	return dry_mass;
	
}

bool Bacterium::has_to_die(){
	
	if (volume <= MINIMAL_CELL_VOLUME){
		
		return(true);
	}

	float p = get_uniform(0.0,1.0);
	if (type== "D" && p >= plasmid_cost){

		return(true);
	}
	
	return(false);
	
}

void Bacterium::update_volume(){
 
    float late_volume = volume;
    volume = MEDIAN_CELL_VOLUME * pow(2.0, growth/log1p(1));
    


}

bool Bacterium::can_divide(){

    if (volume >= VOLUME_AT_DIVISION)
	return(true);

    return(false);

}


int Bacterium::get_free_neighbour_square(Lattice &lat){

	std::vector<int> potential_sites_of_division_ids = lat[square_id].get_neighbor_square_ids();
	
	while (potential_sites_of_division_ids.size()!=0){
		
	  int new_square_id_index = get_uniform(0, potential_sites_of_division_ids.size()-1);
		
		if (lat[potential_sites_of_division_ids[new_square_id_index]].is_full()){
			
				potential_sites_of_division_ids.erase(potential_sites_of_division_ids.begin()+new_square_id_index);
		
		}
		else{
			// division is possible 

			volume = MEDIAN_CELL_VOLUME;
			return(potential_sites_of_division_ids[new_square_id_index]);			
        	}

    	}
		return -1;	
}

int Bacterium::get_square_id(){
  return square_id;
}



float Bacterium::get_growth_rate(){
    return growth;
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

	float p = get_uniform(0.0,1.0);
	if (p <= p_seg_loss){

		type="R";	

	}
	else{
		
		type="D";
	} 
		
}

int Bacterium::get_square_id_via_pointer(){

	int p_id_square = pSquare->get_id();
	return p_id_square;	

}
