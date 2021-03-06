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

#define DEBUG(x) std::cout << "DEBUG : " << x << "  - line : "<< __LINE__ << " - file : " << __FILE__ << std::endl;


extern int LENGTH ;
extern int HEIGHT;


Lattice::Lattice(){}

Lattice::~Lattice(){}
	

void Lattice::fill_lattice(){

	for (int row=0; row < HEIGHT; row++){
		for (int column = 0; column < LENGTH; column++){
		
			int square_id = column+row*LENGTH; 	
			Square square(square_id,row,column); 
			lattice_squares.push_back(square);
			lattice_squares[lattice_squares.size()-1].set_neighbor_square_ids();
		}
	}

}

void Lattice::add_a_bacterium(std::vector<Bacterium*> &bacteria_list){
	
    	int square_id = get_uniform(0, lattice_squares.size() - 1);
		
	while (1){
		if (lattice_squares[square_id].add_bacterium_to_square(bacteria_list,LENGTH)==true){
			break;
		}
		square_id = get_uniform(0, lattice_squares.size() - 1);
	}

}

void Lattice::add_bacterium_to_square_with_id(std::vector<Bacterium*> &bacteria_list,int new_square_id){
	
	lattice_squares[new_square_id].add_bacterium_to_square(bacteria_list, LENGTH);	

}

Square Lattice::operator [] (int id){
  return lattice_squares[id];
}


void Lattice::delete_lat_bacteria(int square_id, int level){

	lattice_squares[square_id].delete_bacteria(level);

}
