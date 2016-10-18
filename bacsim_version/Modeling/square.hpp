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
		float substrate; // concentration of substrate per square
		int id; // square id
		int full; // equals 1 if the square is full of bacteria
		std::vector<Bacterium*> square_bacteria; // vector of pointers to the bacteria agents
		int last_stack_level_used; // last stack level used by a bacterium
		int row; // row of the square in the lattice
		int column; // column of the square in the lattice
		std::vector<int> neighbor_ids; // neighbor squares ids
		
	public:
		
		Square(int n,int r, int c); 
		~Square(); 

		// add a bacterium to the square 
		bool add_bacterium_to_square(std::vector<Bacterium*> &bacteria_list,int lat_length); 
		// delete the substrate from the square when bacteria uptakes nutriments
		void reduce_substrate(float,float); //delete the substrate from the square when bacteria uptakes glucose
		// get substrate
		float get_substrate();
		// returns 1 if the square is full
		int is_full();
		// delete bacterium at specific level from the square
		void delete_bacteria(int level);
		// the bacteria at level 0 from this square receives or not a plasmid
		bool give_plasmid_to_bacteria(int bacterium_level);
		// returns square id 
		int get_id();
		void check_vector(); // fonction test, a supprimer plus tard
		// set neighbourding squares ids
		void set_neighbor_square_ids();
		// returns neighbourding squares ids
		std::vector<int> get_neighbor_square_ids();
		// test function (shows neighbour squares ids )
		void show_neighbors();
};
#endif
