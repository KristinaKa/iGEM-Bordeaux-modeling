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

#define DEBUG(x) std::cout << "DEBUG : " << x << "  - line : "<< __LINE__ << " - file : " << __FILE__ << std::endl;

int MAX_STACK_NB ;
float conjugation_rate;
int LENGTH ;
int HEIGHT;
float INIT_SUBSTRATE;

Square::Square(int n,int r, int c){
	id = n;
	row = r;
	column = c;
	substrate = INIT_SUBSTRATE; 
	full=0;
	last_stack_level_used=0; //no stack/level occupied by default
}

Square::~Square(){}
bool Square::add_bacterium_to_square(std::vector<Bacterium*> &bacteria_list, int lat_length){
	

	if (full){
		return false;
	}

  	//addition of the bacterium* in the square

  	Bacterium* pbact = new Bacterium(id, this, last_stack_level_used);
  	square_bacteria.push_back(pbact);

  	
  	// Addition of the bacterium* in the bacteria list

  	Bacterium* pbact_2 = pbact;
  	bacteria_list.push_back(pbact_2);
 
	// Changing stack level in the square

	last_stack_level_used+= 1;
	if (last_stack_level_used== MAX_STACK_NB - 1)
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


void Square::delete_bacteria(int level){

	// delete the pointer to the bacterium from square_bacteria

	square_bacteria.erase(square_bacteria.begin() + level);

	// stack level diminishes

	last_stack_level_used-= 1;

	// change the other bacteria level in the square 

  	if (square_bacteria.size()!=0){

  		for (int i = level; i < square_bacteria.size(); i++){

  			int new_stack_id = square_bacteria[i]->get_stack_id();
  			new_stack_id = new_stack_id - 1;
  			square_bacteria[i]->set_stack_id(new_stack_id);	

  		}
  	}

}


bool Square::give_plasmid_to_bacteria(int bacterium_level){


	if (square_bacteria.size()==0){

		return false;

	}

	if (bacterium_level > square_bacteria.size() -1){

		return false;

	}
	
	if ((square_bacteria[bacterium_level]->get_type())=="R"){
	
		float p = get_uniform(0.0,1.0);
	
		if (p <= conjugation_rate){

			square_bacteria[bacterium_level]->set_type("D");
			return true;
		}
		
		else{
			return false;
		}

	}	

	return false;
}

void Square::check_vector(){
	std::cout << " Square::check_vector() square_id " << id <<std::endl;
	std::cout << "Square::check_vector() " << std::endl;
	std::cout << "square_bacteria.size() " << square_bacteria.size() << std::endl;

}

int Square::get_id(){

	return id;

}

void Square::set_neighbor_square_ids(){

	// First step : get the number of the neighbording cases
	
	int down_left = id - LENGTH - 1;
	int down_right = id - LENGTH + 1;
	int left = id - 1;
	int right = id + 1;
	int down_middle = id - LENGTH;
	int up_middle = id + LENGTH;
	int up_left = id + LENGTH -1;
	int up_right = id + LENGTH +1;

	// Check if these ids exist and add them to neighbor_ids if they do
	
	// row corresponds to the height level to which the square is located 	

	//The square itself is added as a neighbor since it can contain neighbor Bacteria

	neighbor_ids.push_back(id);

	if (down_left >= ((row -1)*LENGTH)){
		if( down_left <= (row*LENGTH -1) && down_left >= 0)
			neighbor_ids.push_back(down_left);
	}

	if (down_right >= ((row -1)*LENGTH) && down_right <= (row*LENGTH -1) && down_right >=0){ 
		neighbor_ids.push_back(down_right);
	}
	if (down_middle >= ((row -1)*LENGTH) && down_middle <= (row*LENGTH -1) && down_middle >=0){ 
		neighbor_ids.push_back(down_middle);
	}

	if (left >= (row*LENGTH) && left <= (row*LENGTH +LENGTH -1)){ 
		neighbor_ids.push_back(left);
	}

	if (right >= (row*LENGTH) && right <= (row*LENGTH +LENGTH -1)){ 
		neighbor_ids.push_back(right);
	}

	if (up_left >= ((row +1)*LENGTH) && up_left <= ((row+1)*LENGTH +LENGTH -1)){
	      if (up_left < HEIGHT*LENGTH){	
			neighbor_ids.push_back(up_left);
	       }
	}

	if (up_right >= ((row +1)*LENGTH) && up_right <= ((row+1)*LENGTH +LENGTH -1)){
		if (up_right < HEIGHT*LENGTH){
			neighbor_ids.push_back(up_right);
		}
	}
	if (up_middle >= ((row +1)*LENGTH) && up_middle <= ((row+1)*LENGTH +LENGTH -1)){
		
		if (up_middle < HEIGHT*LENGTH){
			neighbor_ids.push_back(up_middle);
		}
	}
	
}

std::vector<int> Square::get_neighbor_square_ids(){

	return neighbor_ids; 

}

void Square::show_neighbors(){

	std::cout << " Square id : "<< id << std::endl;

	for (int i = 0; i < neighbor_ids.size(); i++){
	
		std::cout << " Neighbor id : " << neighbor_ids[i] <<std::endl;

	}	

}
