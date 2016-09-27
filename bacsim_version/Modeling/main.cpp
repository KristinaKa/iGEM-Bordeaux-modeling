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

	// Fill the lattice with squares 
	lat1.fill_lattice();

	// Array containing the different bacteria
	std::vector<Bacterium*> bacteria_list;


	// Array containing the different timesteps for the plotting
	std::vector<float> t_values = arange(0,t,dt);

	// Array containing the different number of bacteria for the plotting
	std::vector<int> nb_of_bacteria;

	/** Initialization **/

	int nb_bacteria = INIT_BACT_NB;
	for(int i=0; i<nb_bacteria; i++)
		lat1.add_a_bacterium(bacteria_list);

	/** Simulation runs **/

	for (int j = 0; j < t_values.size(); j++){

		float dt = t_values[j];

		// a random number of bacteria are selected and their status is changed
		int nb_bact_checked = 0.6*bacteria_list.size(); 

		for (int i = 0; i < nb_bact_checked ; i++){

			if (bacteria_list.size()!=0){
				int bact_id = get_uniform(0 , bacteria_list.size() - 1) ;
				printf("ici la bacterie %d \n",bact_id);	
				bacteria_list[bact_id]->metabolism(dt, lat1);
				bacteria_list[bact_id]->update_volume();
				printf("taille %d \n",bacteria_list.size());

				if (bacteria_list[bact_id]->can_divide()==true){
					printf("Nous entrons dans la twilight zone de la division \n");		
					int new_square_id = bacteria_list[bact_id]->divide(lat1);		
					//printf("new square id pour division %d \n",new_square_id);
					if (new_square_id>0){
					
						lat1.add_bacterium_to_square_with_id(bacteria_list, new_square_id);

						printf("le nouveau square occupe, d'id  %d a %d bacterie \n",new_square_id,lat1[5].get_bacteria_list_length());		
						printf("taille de bacteria_list %d \n",bacteria_list.size());			
					}
				}
			
				if (bacteria_list[bact_id]->has_to_die()==true){
			
					int square_id = bacteria_list[bact_id]->get_square_id();
					printf("on va supprimer bacterie de  square_id %d \n",square_id);
					//lat1[square_id]->delete_bacteria();	
					printf("on a supprile la bacterie de son square \n");
					//bacteria_list.erase(bacteria_list.begin() + bact_id);			
					printf("on a supprime bacterie de bacteria_list \n");
				}

			}
		}

		// Adding the new bacteria number
		nb_of_bacteria.push_back(bacteria_list.size());
		//nb_of_bacteria.push_back(log1p(bacteria_list.size()-1));
	}

	printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

	/** Plotting **/
	// Vecteurs a plotter : t_values et nb_of_bacteria

	save("results.csv", t_values, nb_of_bacteria);

	return 1;

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
