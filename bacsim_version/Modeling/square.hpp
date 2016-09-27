#ifndef __SQUARE_HPP__
#define __SQUARE_HPP__

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

class Bacteria;

class Square{

	private:
		float substrate; // substrate per square, fg/fl ? 
		int id;
		int full;
		int height;
		std::vector<Bacteria*> square_bacteria;
		int last_used_stack;


	public:
		Square(); //Constructor
		Square(int n,int i); //another constructor
		~Square(); //Destructor

		bool add_bacteria_to_square(std::vector<Bacteria*> &bacteria_list,int lat_length); //add one bacteria to the square_bacteria array
		void reduce_substrate(float, float); //delete the substrate from the square when bacteria uptakes glucose
		float get_rate_of_substrate_uptake();
		float get_substrate();
		int is_full();
	
		int get_bacteria_list_length();
		void delete_bacteria();

		// INDISIM

		void diminish_substrate(float U);
		int get_stack_level();
		void add_bacteria(Bacteria* ,int);
};
#endif
