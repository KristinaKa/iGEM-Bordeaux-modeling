#include "lattice.hpp"
#include "square.hpp"
#include "bacteria.hpp"
#include "constants.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include <time.h>


std::default_random_engine generator(time(0));


// equivalent of arange method in python ( a ranger quelque part)
void save(std::string file_name, std::vector<float> x, std::vector<int> y);


std::vector<float> arange(float start, float stop, float step) ;

std::vector<float> arange(float start, float stop, float step) {
	std::vector<float> values;
	for (float value = start; value < stop; value += step)
		values.push_back(value);
	return values;
}

int main(int argc, char *argv[]){


    clock_t tStart = clock();

	// Create a lattice  

	Lattice lat1;

	// Fill the lattice with square 

	lat1.fill_lattice();

	std::vector<Bacteria*> bacteria_list;


	/** Time parameters **/

	float t = 300; // simulation time in hours

	std::vector<float> t_values = arange(0,t,dt); //an array containing the different timesteps for future plotting

	std::vector<int> nb_of_bacteria;

	/** Initialization **/

	int nb_bacteria = 100;
	for (int i=0; i <nb_bacteria; i++){
		lat1.add_bacteria(bacteria_list);
	}
	/** Simulation runs **/
	/* For now 5 */


  	for (int j = 0; j < t_values.size(); j++){
  
  		printf("\n tour number %d \n",j);
  
  		float dt = t_values[j];
  
  		/** a random number of bacteria are selected and their status is changed **/
  		int nb_bact_checked = bacteria_list.size();  // for now 10, later maybe : rand() % bacteria_list.size();
  
  		for (int i = 0; i < nb_bact_checked ; i++){
  
  			if (bacteria_list.size()!=0){
  				//int bact_id = get_uniform(0 , bacteria_list.size() - 1) ;
  				//printf("ici la bacterie %d \n",bact_id);	
  				bacteria_list[i]->uptake(lat1);
  				bacteria_list[i]->metabolism_indisim(lat1);
  				bacteria_list[i]->check_entering_division();
  
  				if (bacteria_list[i]->check_divide()==true){
  				
  					int new_square_id = bacteria_list[i]->divide_indisim(lat1);
  					if (new_square_id>=0){
  					
  						lat1.add_bacteria_to_square_with_id(bacteria_list, new_square_id);
  						bacteria_list[bacteria_list.size()-1]->set_dry_mass(bacteria_list[i]->get_dry_mass());
  					
  					}
  				}
  				bacteria_list[i]->update_time(dt);
  				int level_id = bacteria_list[i]->get_level_id();
  				printf("level id %d \n",level_id);
  				printf(" On regarde si un square est libre pour bouger \n");
  				int new_square = bacteria_list[i]->square_to_move_to(lat1);
  				if (new_square >=0){
  					
  					printf("on peut bouger \n");
  					
  					Bacteria* pbact = bacteria_list[i];
  					printf("on a recupere le pointeur vers bacterie \n");
  					// on change le pointeur qui pointe vers la bacterie dans square.square_bacteria
  					lat1.move_bacteria_to_square(pbact,new_square);
  					printf("on a bouge \n");
  						
  
  				}
  
  			}
  		}
  
  		/** Adding the new bacteria number **/
  		nb_of_bacteria.push_back(bacteria_list.size());
  		//nb_of_bacteria.push_back(log1p(bacteria_list.size()-1));
  
  	}
	printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

	/** Plotting **/
	// Vecteurs a plotter : t_values et nb_of_bacteria

	//save("results.csv", t_values, nb_of_bacteria);

	return 1;

}

void show_stats(std::vector<Bacteria*> bacteria_list, Lattice lattice){
	//prints the different stats on the console
	for(int i=0; i<bacteria_list.size(); i++){
		bacteria_list[i]->show_bacteria_console();
		//bacteria_list[i].show_bacteria_console();
		int id = bacteria_list[i]->get_square_id(); 
		//std::cout << lattice[id].get_substrate()<<"\n"; 
	}
}



void save(std::string file_name, std::vector<float> x, std::vector<int> y)
{

	printf("Saving...\n");

    std::ofstream file(file_name.c_str(), std::ios::out | std::ios::trunc);  // flux declaration and opening file

    if(file)
	{
    	for (int i = 0 ; i < x.size() ; i++)
    	    file << x[i] << ";" << y[i] << "\n" ;

        file.close();  
	}

    else 
            std::cerr << " Opening file error !" << std::endl;

}


const int get_uniform(int a, int b)
{
	std::uniform_int_distribution <int> ud{a, b}; // a number between a and b
	return ud(generator);
}
