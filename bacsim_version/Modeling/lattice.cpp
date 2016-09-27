#include "lattice.hpp"
#include "square.hpp"
#include "constants.hpp"

#include <unistd.h>
#include <fstream>

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <math.h> 
#include <random>
#include <time.h> 



Lattice::Lattice(){}

Lattice::~Lattice(){}
	

void Lattice::fill_lattice(){

	for (int i=0; i < HEIGHT; i++){
		for (int j=0; j< LENGTH; j++){
			int square_id = j+i*LENGTH; 	
			Square square(square_id,i); 
			lattice_squares.push_back(square);
		}
	}

}

void Lattice::add_bacteria(std::vector<Bacteria*> &bacteria_list){
	

    int square_id = get_uniform(0, lattice_squares.size() - 1);
 
	
	while (1){
			if (lattice_squares[square_id].add_bacteria_to_square(bacteria_list,LENGTH)==true){

				break;
			}
			else{

				square_id = get_uniform(0, lattice_squares.size() - 1);
			}
		}
	
	
}

void Lattice::add_bacteria_to_square_with_id(std::vector<Bacteria*> &bacteria_list,int new_square_id){
	
		
	lattice_squares[new_square_id].add_bacteria_to_square(bacteria_list, LENGTH);	
}

Square Lattice::operator [] (int id){
  return lattice_squares[id];
}

int Lattice::get_height(){
    return HEIGHT;
}

int Lattice::get_length(){
    return LENGTH;
}


int Lattice::get_lattice_squares_length(){

	return lattice_squares.size();
}

Square Lattice::get_square(int i)
{
	return lattice_squares[i];
}

// INDISIM 

void Lattice::move_bacteria_to_square(Bacteria* pbact,int new_square_id){

	printf("on veut bouger au square %d \n",new_square_id);
	int stack_level = lattice_squares[new_square_id].get_stack_level();

	printf("ce square a un stack level de %d \n", stack_level);
	
	pbact->test();
	//std::cout << std::typeof(pbact) << std::endl;
	printf("\n");
	lattice_squares[new_square_id].add_bacteria(pbact,stack_level);

	printf("bacteria has moved to square %d \n",new_square_id);

}

