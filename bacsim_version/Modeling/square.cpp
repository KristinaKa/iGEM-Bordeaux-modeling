#include "square.hpp"
#include "bacterium.hpp"
#include "constants.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <math.h> 

#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <cstdlib>

#include <stdlib.h>

Square::Square(){}
Square::~Square(){}

Square::Square(int n,int i){
	id = n;
	height=i;
	substrate = INIT_SUBSTRATE; 
    full=0;
    last_stack_level_used=-1; //no stack/level occupied by default
}

bool Square::add_bacterium_to_square(std::vector<Bacterium*> &bacteria_list, int lat_length){
	

	if (full){
		return false;
	}

	//addition of the bacterium* in the square
	Bacterium* pbact = new Bacterium(id, this, last_stack_level_used);
	pbact->set_neighbor_square_ids(lat_length,height);
	square_bacteria.push_back(pbact);
	//printf("square_bacteria a pour taille %d \n",square_bacteria.size());
	
	//Addition of the bacterium* in the bacteria list
	Bacterium* pbact_2 = pbact;
	bacteria_list.push_back(pbact_2);

	//printf("square_bacteria a pour taille %d \n",square_bacteria.size());
	//printf("Dans bacteria_list, le nouveau bebe cree a pour numero %d \n", bacteria_list.size());

	last_stack_level_used+= 1;
	if (last_stack_level_used== MAX_STACK_NB)
		full=1;

	return true;
}




void Square::reduce_substrate(float bacterial_uptake, float dt){
  substrate = substrate - dt*bacterial_uptake;
  	
}

float Square::get_substrate(){
  return substrate;
}
	
int Square::is_full(){
    return full;
}


void Square::delete_bacteria(){

	printf("on rentre dans la fonction delete_bacteria de square \n");
	printf("square_bacteria size : %d \n",square_bacteria.size());
	square_bacteria.erase(square_bacteria.begin() + 0);

}

int Square::get_bacteria_list_length(){

	return square_bacteria.size();
} 	
	

