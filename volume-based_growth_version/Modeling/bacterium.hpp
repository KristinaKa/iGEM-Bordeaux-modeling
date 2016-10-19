#ifndef __BACTERIUM_HPP__
#define __BACTERIUM_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <math.h> 
#include "lattice.hpp"

class Lattice;
class Square;

class Bacterium{

	private:
		float volume; // volume 
		int stack_id; // indicates if the cell is in contact with the surface ( if stack_id = 0 : cell in contact; if >=1 : not in contact )
		float dry_mass; // dry mass of the cell in fg/fl
		int square_id; // id of the square where the bacterium is 
		Square* pSquare= NULL; //pointer to the square where the bacterium is
		float growth; //growth rate = dt*uptake/Ymax, used to calculate the volume
		std::string type; // type of the bacterium: donor or recipient

	public:
		Bacterium(int, Square*, int); //Constructor
		~Bacterium(); //Destructor
		
		/** Life and death of the bacterium functions **/

		void metabolism(Lattice lattice); //metablolism & maintenance of the bacterial cell
		void update_volume(); // volume update
		bool can_divide(); // returns true if the bacterium volume has reached the division volume
		int get_free_neighbour_square(Lattice &lat); // checks if there are available squares for division, if yes, sets volume to median volume and returns one of those squares
		bool has_to_die(); // returns true if cell volume has fallen under minimal volume and cell has to die
		float get_growth_rate(); // returns growth

		/** Plasmid loss and transmission **/


		bool conjugation(Lattice &lat);	
		void segregation_loss();

		/** Getters and setters **/

		void set_type(std::string); // set type donor or recipient for bacterium
		std::string get_type(); // returns type
		void set_stack_id(int n); //set the id_level of the bacterium
		int get_stack_id(); // returns the id_level of the bacterium
		float get_dry_mass(); // returns the dry mass of the bacterium
		int get_square_id(); //returns the square id
		int get_square_id_via_pointer();
	
};

#endif 
