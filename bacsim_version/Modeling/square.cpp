#include "square.hpp"
#include "bacteria.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <math.h> 

#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <cstdlib>

#include <stdlib.h>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>


Square::Square(){}
Square::~Square(){}

Square::Square(int n,int i){
	id = n;
	height=i;
	substrate = 145000;
    	full=0;
    	last_used_stack=-1; //no stack/level occupied by default
}

bool Square::add_bacteria_to_square(std::vector<Bacteria*> &bacteria_list, int lat_length){
	
	printf("Ici la bacterie num %d au square num %d \n",bacteria_list.size(),id);

	if (full){
		return false;
	}

	double mass_at_division;
	//addition of the bacterium* in the square
	while(true){

		boost::mt19937 rng; 

  		boost::normal_distribution<> nd(Mr_mean, std_dev_Mr);

  		boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > var_nor(rng, nd);
		mass_at_division = var_nor();

		if (mass_at_division > mr_min){

			break;
			}
		}

	Bacteria* pbact = new Bacteria(id, this, last_used_stack, mass_at_division);
	pbact->set_neighbor_square_ids(lat_length,height);
	square_bacteria.push_back(pbact);
	//printf("square_bacteria a pour taille %d \n",square_bacteria.size());
	
	//Addition of the bacterium* in the bacteria list
	Bacteria* pbact_2 = pbact;
	bacteria_list.push_back(pbact_2);

	//printf("square_bacteria a pour taille %d \n",square_bacteria.size());
	//printf("Dans bacteria_list, le nouveau bebe cree a pour numero %d \n", bacteria_list.size());

	last_used_stack+= 1;
	if (last_used_stack== MAX_STACK_NB){
		full=1;}
	pbact->get_level_id();
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

// INDISIM 

void Square::diminish_substrate(float U){

	substrate = substrate - U;

}


int Square::get_stack_level(){

	return last_used_stack;	
}

void Square::add_bacteria(Bacteria* pbact ,int stack_level){

	printf("fonction add_bacteria de square \n");
	square_bacteria.push_back(pbact);
	printf("on vient de pusher pointeur dans square_bacteria de square \n");
	square_bacteria[square_bacteria.size()]->change_stack_level(stack_level);
	printf("on vient de changer le niveau de la bacterie pour qu'elle prenne le dernier niveau du square \n");
	square_bacteria[square_bacteria.size()]->set_neighbor_square_ids(LENGTH,height);
	printf("on a fait set sur ses voisins \n");
}
