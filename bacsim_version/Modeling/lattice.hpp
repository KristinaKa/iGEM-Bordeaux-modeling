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
		std::vector<Square> lattice_squares;
	
    public:
		Lattice(); //Constructor
		~Lattice(); //Destructor
		

		void fill_lattice();
		void add_a_bacterium(std::vector<Bacterium*> &bacteria_list);
		Square operator [](int id);
		int get_length();
		int get_height();

		int get_lattice_squares_length();
		void add_bacterium_to_square_with_id(std::vector<Bacterium*> &bacteria_list,int new_square_id);
		Square get_square(int i);
};


const int get_uniform(int a, int b);



#endif
