#ifndef __BACTERIA_HPP__
#define __BACTERIA_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <math.h> 
#include "lattice.hpp"
#include "constants.hpp"

#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

class Lattice;
class Square;

class Bacteria{

	private:
		float volume; // volume 
		int id_level; // indicates if the cell is in contact with the surface ( if id_level = 0 : cell in contact; if >=1 : not in contact )
		float dry_mass; // dry mass of the cell at u = 0 (phase stationnaire de la croissance ) in fg/fl
		int square_id; // id of the square where the bacteria is 
		Square* pSquare= NULL; //pointer to the square where the bacterium is
		float growth; //growth rate = dt*uptake/Ymax, used to calculate the volume
		float MEDIAN_CELL_VOLUME= 0.4; //median cell volume at growth rate = 0, Bacsim reference
		float MINIMAL_CELL_VOLUME= 0.1; //Bacsim reference
		float VOLUME_AT_DIVISION= 0.5; //Bacsim reference (5 times the minimal cell volume)
		std::vector <int> neighbor_square_ids;

		//INDISIM 

		float U;
		double mr;
		float tbact;
		bool dividing;

	public:
		Bacteria(int, Square*, int); //Constructor
		~Bacteria(); //Destructor
		void metabolism(float &dt, Lattice lattice);
		void set_level_id(int n); //set the id_level of the bacteria
		int get_level_id(); // returns the id_level of the bacteria
		float get_dry_mass(); // returns the dry mass of the bacteria
		int get_square_id(); //returns the square id
		void show_bacteria_console(); //shows the bacteria on the console, used for debugging
		void update_volume();
		int divide(Lattice &lat);

		float get_growth_rate();

		bool can_divide();
		void set_neighbor_square_ids(int lat_length, int id_height);
		bool has_to_die();

		// INDISIM 
		Bacteria(int, Square*, int,double); //Constructor
		void uptake(Lattice &lattice);
		void metabolism_indisim(Lattice &lat);
		void check_entering_division();
		bool check_divide();
		void update_time(float dt);
		int divide_indisim(Lattice &lat);
		void set_dry_mass(float m);


		void change_stack_level(int stack_level);
		int square_to_move_to(Lattice &lat);
		void test();
};

#endif 
