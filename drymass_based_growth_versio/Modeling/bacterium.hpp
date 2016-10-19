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

#include <stdbool.h>
class Lattice;
class Square;

class Bacterium{

	private:
		int stack_id; // indicates if the cell is in contact with the surface ( if id_level = 0 : cell in contact; if >=1 : not in contact )
		float dry_mass; // dry mass of the cell at u = 0 (phase stationnaire de la croissance ) in fg/fl
		int square_id; // id of the square where the bacteria is 
		Square* pSquare= NULL; //pointer to the square where the bacterium is
		std::vector <int> neighbor_square_ids;
		float U; // nutrients absorbed by the bacterium
		double mr; // random mass the bacterium has to reach to begin division
		float tbact; // time count during division for the bacterium
		bool dividing; // true if the bacterium is in its dividing state
		std::string type;
	public:
		Bacterium(int, Square*, int,double); //Constructor
		~Bacterium(); //Destructor
		
		/** Setters and getters **/

		void set_level_id(int n); 
		int get_level_id(); 
		void set_dry_mass(float m);
		float get_dry_mass(); 
		void set_square_id(int n);
		int get_square_id();		
		void set_stack_id(int n);
		int get_stack_id();
		
		void set_type(std::string t);
		std::string get_type();
		
		/** Growth methods **/	
		
		// returns square id or -1 if no square is available for division
		int divide(Lattice &lat);

		// check if the bacterium can enter its division state
		void check_entering_division();

		// check if the division state has ended, returns 1 if true
		int check_divide();

		// update tbact during the dividing state of the bacterium
		void update_time();
	
		// returns 1 if the bacterium has to die 
		bool has_to_die();

		// Bacterium uptakes nutrients
		void uptake(Lattice &lattice);

		// Bacterium metabolize the nutrients
		void metabolism(Lattice &lat);

		/** Plasmid transmission and loss **/


		// returns true if the bacterium has been able to do conjugation with another bacterium
		bool conjugation(Lattice &lat);

		// determines if the new bacterium receives or not a plasmid copy from its mother cell 
		void segregation_loss();
		
		
		/** Others **/

		// returns a square id if there is a square available for the bacterium to move to, else returns -1		
		int square_to_move_to(Lattice &lat);
};

#endif 
