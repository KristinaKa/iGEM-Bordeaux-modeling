#ifndef __LATTICE_HPP__
#define __LATTICE_HPP__

#include "square.hpp"
#include "constants.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> 
#include <math.h> 

class Square;
class Bacteria;

class Lattice{

	private:
		std::vector<Square> lattice_squares;
		float substrate;

	
    public:
		Lattice(); //Constructor
		~Lattice(); //Destructor
		

		void fill_lattice();
		void add_bacteria(std::vector<Bacteria*> &bacteria_list);
		Square operator [](int id);
		int get_length();
		int get_height();

		int get_lattice_squares_length();
		void add_bacteria_to_square_with_id(std::vector<Bacteria*> &bacteria_list,int new_square_id);
		Square get_square(int i);

		// INDISM 

		
		void move_bacteria_to_square(Bacteria* pbact,int new_square_id);
};


const int get_uniform(int a, int b);



#endif
