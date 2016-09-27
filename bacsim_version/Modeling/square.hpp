#ifndef __SQUARE_HPP__
#define __SQUARE_HPP__

#include "bacterium.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <math.h> 


#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <cstdlib>


#include <stdlib.h>

class Bacterium;

class Square{

	private:
		float substrate; // substrate per square, fg/fl ? 
		int id;
		int full;
		int height;
		std::vector<Bacterium*> square_bacteria;
		int last_stack_level_used;


	public:
		Square(); //Constructor
		Square(int n,int i); //another constructor
		~Square(); //Destructor

		bool add_bacterium_to_square(std::vector<Bacterium*> &bacteria_list,int lat_length); //add one bacteria to the square_bacteria array
		void reduce_substrate(float, float); //delete the substrate from the square when bacteria uptakes glucose
		float get_rate_of_substrate_uptake();
		float get_substrate();
		int is_full();
	
		int get_bacteria_list_length();
		void delete_bacteria();
};
#endif
