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


Bacterium::Bacterium(int id, Square* _pSquare, int last_stack_level_used){
	square_id = id ;
	pSquare = _pSquare;
	volume = INIT_VOLUME;
	stack_id = last_stack_level_used+1;
	dry_mass = INIT_DRY_MASS;
	printf("on ajoute une bacterie au square %d  et au niveau %d \n", id, stack_id);	
}


	
Bacterium::~Bacterium(){}

void Bacterium::metabolism(float &dt, Lattice lattice){

	float substrate = lattice[square_id].get_substrate();
	
	float uptake = dry_mass * Vmax * substrate/(Km+substrate);
	lattice[square_id].reduce_substrate(uptake, dt);
	float late_dry_mass = dry_mass;
	dry_mass = dry_mass + dt*uptake/Ymax - dt*dry_mass*m*Ymax;
	growth = (dry_mass - late_dry_mass)/dt;

}


void Bacterium::set_stack_id(int n){
	
	stack_id = n;
	
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
	
	return(false);
	
}

void Bacterium::update_volume(){
    /* Volume = Vu * 2^(µ/ln2)
    Where : Vu=median cell volume and µ=growth rate=(anabolism - maintenance)
	*/

    volume = MEDIAN_CELL_VOLUME * pow(2.0, growth/log1p(1));

    //std::cout<< "new volume "<<volume;
}

bool Bacterium::can_divide(){


    if (volume >= VOLUME_AT_DIVISION){


        volume = MEDIAN_CELL_VOLUME;
	return(true);

	}

	return(false);

}


int Bacterium::divide(Lattice &lat){

	std::vector<int> potential_sites_of_division_ids = neighbor_square_ids;
	
	printf("notre bacterie occupe le square %d \n",square_id);
	while (potential_sites_of_division_ids.size()!=0){
		
		int new_square_id_index = rand() % potential_sites_of_division_ids.size();
		
		if (lat[potential_sites_of_division_ids[new_square_id_index]].is_full()){
			
			//printf("pas de place dans le square %d \n",potential_sites_of_division_ids[new_square_id_index]);
			potential_sites_of_division_ids.erase(potential_sites_of_division_ids.begin()+new_square_id_index);
		
		}
		else{
			printf("Bacterie va se diviser dans le square %d \n", new_square_id_index);
			return(potential_sites_of_division_ids[new_square_id_index]);			
        	}

    	}
    	printf("Bacterie n'a pas pu se diviser :(\n");
		return -1;	
}

int Bacterium::get_square_id(){
  return square_id;
}

void Bacterium::set_neighbor_square_ids(int lat_length,int id_height){

	// First step : get the number of the neighbording cases
	
	int down_left = square_id - lat_length - 1;
	int down_right = square_id - lat_length + 1;
	int left = square_id - 1;
	int right = square_id + 1;
	int down_middle = square_id - lat_length;
	int up_middle = square_id + lat_length;
	int up_left = square_id + lat_length -1;
	int up_right = square_id + lat_length +1;

	// Check if these ids exist and add them to neighbor_square_ids if they do
	
	// id_height corresponds to the height level to which the square is located 	

	//The square itself is added as a neighbor since it can contain neighbor Bacterium
	neighbor_square_ids.push_back(square_id);

	if (down_left >= ((id_height -1)*lat_length)){
		if( down_left <= (id_height*lat_length -1) && down_left >= 0)
			neighbor_square_ids.push_back(down_left);
	}

	if (down_right >= ((id_height -1)*lat_length) && down_right <= (id_height*lat_length -1) && down_right >=0){ 
		neighbor_square_ids.push_back(down_right);
	}
	if (down_middle >= ((id_height -1)*lat_length) && down_middle <= (id_height*lat_length -1) && down_middle >=0){ 
		neighbor_square_ids.push_back(down_middle);
	}

	if (left >= (id_height*lat_length) && left <= (id_height*lat_length +lat_length -1)){ 
		neighbor_square_ids.push_back(left);
	}

	if (right >= (id_height*lat_length) && right <= (id_height*lat_length +lat_length -1)){ 
		neighbor_square_ids.push_back(right);
	}

	if (up_left >= ((id_height +1)*lat_length) && up_left <= ((id_height+1)*lat_length +lat_length -1)){ 
		neighbor_square_ids.push_back(up_left);
	}

	if (up_right >= ((id_height +1)*lat_length) && up_right <= ((id_height+1)*lat_length +lat_length -1)){
		neighbor_square_ids.push_back(up_right);
	}
	if (up_middle >= ((id_height +1)*lat_length) && up_middle <= ((id_height+1)*lat_length +lat_length -1)){
		neighbor_square_ids.push_back(up_middle);
	}
	
}


float Bacterium::get_growth_rate(){
    return growth;
}
