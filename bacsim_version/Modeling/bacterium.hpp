#ifndef __BACTERIUM_HPP__
#define __BACTERIUM_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <math.h> 
#include "lattice.hpp"
;
class Lattice;
class Square;

class Bacterium{

	private:
		float volume; // volume 
		int stack_id; // indicates if the cell is in contact with the surface ( if stack_id = 0 : cell in contact; if >=1 : not in contact )
		float dry_mass; // dry mass of the cell at u = 0 (phase stationnaire de la croissance ) in fg/fl
		int square_id; // id of the square where the bacterium is 
		Square* pSquare= NULL; //pointer to the square where the bacterium is
		float growth; //growth rate = dt*uptake/Ymax, used to calculate the volume
		std::vector <int> neighbor_square_ids;

	public:
		Bacterium(int, Square*, int); //Constructor
		~Bacterium(); //Destructor
		void metabolism(float &dt, Lattice lattice); //metablolism & maintenance of the bacterial cell
		void set_stack_id(int n); //set the id_level of the bacterium
		int get_stack_id(); // returns the id_level of the bacterium
		float get_dry_mass(); // returns the dry mass of the bacterium
		int get_square_id(); //returns the square id
		void update_volume();
		int divide(Lattice &lat);

		float get_growth_rate();

		bool can_divide();
		void set_neighbor_square_ids(int lat_length, int id_height);
		bool has_to_die();
};

#endif 
