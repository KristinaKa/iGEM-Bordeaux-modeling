#include "lattice.hpp"
#include "square.hpp"
#include "bacterium.hpp"
#include "constants.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include <time.h>

#include <typeinfo>

#define DEBUG(x) std::cout << "DEBUG : " << x << "  - line : "<< __LINE__ << " - file : " << __FILE__ << std::endl;


float t;
extern float dt;
int INIT_BACT_NB;
double PERCENT_OF_DONORS;
extern float conjugation_rate;
extern float p_seg_loss;
extern int MAX_STACK_NB ;
extern int LENGTH ;
extern int HEIGHT;
extern float INIT_SUBSTRATE; 
extern float plasmid_cost;

/* Protoypes */
const int get_uniform(int a, int b);
/* returns  a float vector by creating intervals between start and stop from step lenght */
std::vector<float> arange(float start, float stop, float step) ;
/* saves results */
void save(std::string file_name, std::vector<float> x, std::vector<int> y,std::vector<int> ybis);


int main(int argc, char *argv[]){

  // Get parameters values from graphical interface
  t = std::stof(argv[1]);
  dt = std::stof(argv[2]);
  INIT_BACT_NB = std::stoi(argv[3]);
  PERCENT_OF_DONORS = std::stof(argv[4]);
  LENGTH = std::stoi(argv[5]);
  HEIGHT = std::stoi(argv[6]);
  MAX_STACK_NB = std::stof(argv[7]);
  INIT_SUBSTRATE = std::stof(argv[8]);
  conjugation_rate = std::stof(argv[9]);
  p_seg_loss = std::stof(argv[10]);
  plasmid_cost = std::stof(argv[11]);

	clock_t tStart = clock();

	// Create a lattice  
	Lattice lat1;

	// Fill the lattice with squares 
	lat1.fill_lattice();

	// Array containing the different bacteria
	std::vector<Bacterium*> bacteria_list;


	// Array containing the different timesteps for the plotting
	std::vector<float> t_values = arange(0,t,dt);
  std::cout << "tttt " << t_values.size() << std::endl;

	// Array containing the different number of bacteria for the plotting
	std::vector<int> nb_of_bacteria;

	/** Initialization **/
  
	for(int i=0; i< INIT_BACT_NB; i++){
			lat1.add_a_bacterium(bacteria_list);
	}
  /** Define the Donor Bacteria **/
  
  int nb_of_donors = PERCENT_OF_DONORS* (INIT_BACT_NB); 
  std::vector<int> nb_of_donor_bacteria;
  for (int i=0; i< nb_of_donors; i++){
  
  	bacteria_list[i]->set_type("D");
  }

  /** Simulation runs **/
  
  for (int j = 0; j < t_values.size(); j++){
  
  	// Adding the new bacteria number
  	nb_of_bacteria.push_back(bacteria_list.size());
  	nb_of_donor_bacteria.push_back(nb_of_donors);
  
 
  	int nb_bact_checked = bacteria_list.size();
  	DEBUG("RUNNING...");
  	for (int i = 0; i < nb_bact_checked; i++){
  
  		if (bacteria_list.size()!=0){
  				
 				int bact_id = get_uniform(0, bacteria_list.size() - 1);
  				
  			int square_id = bacteria_list[bact_id]->get_square_id();
  
  			bacteria_list[bact_id]->metabolism(lat1);
  			bacteria_list[bact_id]->update_volume();
  
  			if (bacteria_list[bact_id]->can_divide()==true){
  				int new_square_id = bacteria_list[bact_id]->get_free_neighbour_square(lat1);
  				if (new_square_id>=0){
  
  					lat1.add_bacterium_to_square_with_id(bacteria_list, new_square_id);
  					if (bacteria_list[bact_id]->get_type()=="D"){

  						bacteria_list[bacteria_list.size()-1]->segregation_loss();
  					}			
  				}
  			}
  
  			if (bacteria_list[bact_id]->get_type()=="D"){
  
    			if ((bacteria_list[bact_id]->conjugation(lat1))==true){
    
    				nb_of_donors+=1;
    			}

  			}
  
				if (bacteria_list[bact_id]->has_to_die()==true){

					int square_id_bis = bacteria_list[bact_id]->get_square_id_via_pointer();

					int level = bacteria_list[bact_id]->get_stack_id();

					lat1.delete_lat_bacteria(square_id,level); //the pointer to bacteria is deleted
					delete bacteria_list[bact_id]; // the bacteria is deleted 

					bacteria_list.erase(bacteria_list.begin() + bact_id);			
				}
  		}
  	}
  }
  
  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  
  /** Plotting **/
  
  save("results.csv", t_values, nb_of_bacteria, nb_of_donor_bacteria);

	return 1;

}


// returns a random number generated from an uniform distribution
std::default_random_engine generator(time(0));

const int get_uniform(int a, int b)
{
	std::uniform_int_distribution <int> ud{a, b}; // a number between a and b
	return ud(generator);
}

// returns  a float vector by creating intervals between start and stop from step lenght
std::vector<float> arange(float start, float stop, float step) {
	std::vector<float> values;
	for (float value = start; value < stop; value += step)
		values.push_back(value);
	return values;
}


// saves results
void save(std::string file_name, std::vector<float> x, std::vector<int> y,std::vector<int> ybis)
{

	printf("Saving...\n");

	std::ofstream file(file_name.c_str(), std::ios::out | std::ios::trunc);  // flux declaration and opening file

	if(file)
	{
		for (int i = 0 ; i < x.size() ; i++)
			file << x[i] << ";" << y[i] << ";" << ybis[i] <<"\n" ;

		file.close();  
	}

	else 
		std::cerr << " Opening file error !" << std::endl;

}
