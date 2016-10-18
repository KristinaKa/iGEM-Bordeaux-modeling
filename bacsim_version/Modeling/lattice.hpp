#ifndef __LATTICE_HPP__
#define __LATTICE_HPP__

#include "square.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> 
#include <math.h> 

class Square;
class Bacterium;

class Lattice{

	private:
		// contains square objects
		std::vector<Square> lattice_squares;
	
    public:
		Lattice(); //Constructor
		~Lattice(); //Destructor
		
		// fills lattice_squares with Square objects
		void fill_lattice();
		// adds a bacterium at the initialization 
		void add_a_bacterium(std::vector<Bacterium*> &bacteria_list);
		// returns lattice_squares[id]
		Square operator [](int id);
		// add a bacterium to a specific square of id new_square_id
		void add_bacterium_to_square_with_id(std::vector<Bacterium*> &bacteria_list,int new_square_id);
		// delete the bacteria from its square
		void delete_lat_bacteria(int, int);
};


const int get_uniform(int a, int b);

#endif
