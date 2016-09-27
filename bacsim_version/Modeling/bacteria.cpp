#include "bacteria.hpp"
#include "constants.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h> 
#include "lattice.hpp"
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

Bacteria::Bacteria(int id, Square* _pSquare, int last_used_stack){
	square_id = id ;
	pSquare = _pSquare;
	volume = 0.4; // value from Bacsim
	id_level = last_used_stack+1;

	dry_mass = 290; // value from Bacsim
	printf("on ajoute une bacterie au square %d  et au niveau %d \n", id, id_level);	
}


	
Bacteria::~Bacteria(){}

void Bacteria::metabolism(float &dt, Lattice lattice){
	
	float umax = 0.0205; 
	float Ymax = 0.4444; 
	float Vmax = umax/Ymax;
	float Km = 2.34*pow(10,3);
	float m = 6*pow(10,-4);

	float substrate = lattice[square_id].get_substrate();
	
	float uptake = dry_mass * Vmax * substrate/(Km+substrate);
	lattice[square_id].reduce_substrate(uptake, dt);
	float late_dry_mass = dry_mass;
	dry_mass = dry_mass + dt*uptake/Ymax - dt*dry_mass*m*Ymax;
	growth = (dry_mass - late_dry_mass)/dt;

}


void Bacteria::set_level_id(int n){
	
	id_level = n;
	
}

int Bacteria::get_level_id(){
	
	std::cout << id_level << std::endl;
	return id_level;
	std::cout << "fin de Bacteria::get_level_id() \n" << std::endl;
	
}

float Bacteria::get_dry_mass(){
	
	return dry_mass;
	
}

bool Bacteria::has_to_die(){
	
	if (volume <= MINIMAL_CELL_VOLUME){
		
		return(true);
	}
	
	return(false);
	
}

void Bacteria::update_volume(){
    /* Volume = Vu * 2^(µ/ln2)
    Where : Vu=median cell volume and µ=growth rate=(anabolism - maintenance)
	*/

    volume = MEDIAN_CELL_VOLUME * pow(2.0, growth/log1p(1));

    //std::cout<< "new volume "<<volume;
}

bool Bacteria::can_divide(){


    if (volume >= VOLUME_AT_DIVISION){


        volume = MEDIAN_CELL_VOLUME;
	return(true);

	}

	return(false);

}


int Bacteria::divide(Lattice &lat){

	std::vector<int> potential_sites_of_division_ids = neighbor_square_ids;
	
	/*for (int i = 0; i < potential_sites_of_division_ids.size(); i++){

		printf("site de division possible %d \n",neighbor_square_ids[i]);
	}*/
	printf("notre bacterie occupe le square %d \n",square_id);
	while (potential_sites_of_division_ids.size()!=0){
		
		int new_square_id_index = rand() % potential_sites_of_division_ids.size();
		
		if (lat[potential_sites_of_division_ids[new_square_id_index]].is_full()){
			
			//printf("pas de place dans le square %d \n",potential_sites_of_division_ids[new_square_id_index]);
			potential_sites_of_division_ids.erase(potential_sites_of_division_ids.begin()+new_square_id_index);
		
		}
		else{
			printf("Bacterie va se diviser dans le square %d \n", new_square_id_index);
			return(potential_sites_of_division_ids[new_square_id_index]);			
        	}

    	}
    	printf("Bacterie n'a pas pu se diviser :(\n");
		return -1;	
}

int Bacteria::get_square_id(){
  return square_id;
}

void Bacteria::set_neighbor_square_ids(int lat_length,int id_height){

	// First step : get the number of the neighbording cases
	
	if (neighbor_square_ids.size()!=0){

		neighbor_square_ids.clear();
	}

	int down_left = square_id - lat_length - 1;
	int down_right = square_id - lat_length + 1;
	int left = square_id - 1;
	int right = square_id + 1;
	int down_middle = square_id - lat_length;
	int up_middle = square_id + lat_length;
	int up_left = square_id + lat_length -1;
	int up_right = square_id + lat_length +1;

	// Check if these ids exist and add them to neighbor_square_ids if they do
	
	// id_height corresponds to the height level to which the square is located 	

	//The square itself is added as a neighbor since it can contain neighbor bacteria
	neighbor_square_ids.push_back(square_id);

	if (down_left >= ((id_height -1)*lat_length)){
		if( down_left <= (id_height*lat_length -1) && down_left >= 0){ //c'est bon
		neighbor_square_ids.push_back(down_left);
		}
	}

	if (down_right >= ((id_height -1)*lat_length) && down_right <= (id_height*lat_length -1) && down_right >=0){ //c'est bon
		neighbor_square_ids.push_back(down_right);
	}
	if (down_middle >= ((id_height -1)*lat_length) && down_middle <= (id_height*lat_length -1) && down_middle >=0){ //c'est bon
		neighbor_square_ids.push_back(down_middle);
	}

	if (left >= (id_height*lat_length) && left <= (id_height*lat_length +lat_length -1)){ //c'est bon
		neighbor_square_ids.push_back(left);
	}

	if (right >= (id_height*lat_length) && right <= (id_height*lat_length +lat_length -1)){ //c'est bon
		neighbor_square_ids.push_back(right);
	}


	if (up_left >= ((id_height +1)*lat_length) && up_left <= ((id_height+1)*lat_length +lat_length -1)){ //c'est bon
		neighbor_square_ids.push_back(up_left);

	}

	if (up_right >= ((id_height +1)*lat_length) && up_right <= ((id_height+1)*lat_length +lat_length -1)){ //c'est bon
		neighbor_square_ids.push_back(up_right);
	}
	if (up_middle >= ((id_height +1)*lat_length) && up_middle <= ((id_height+1)*lat_length +lat_length -1)){ //c'est bon
		neighbor_square_ids.push_back(up_middle);
	}
	
}



void Bacteria::show_bacteria_console(){
  //qDebug() << "Bacteria with square id "<<square_id<<" volume "<< volume <<" id_level "<<id_level;
}

float Bacteria::get_growth_rate(){
    return growth;
}

// INDISIM COMMENCE ICI 

Bacteria::Bacteria(int id, Square* _pSquare, int last_used_stack, double mass_at_division){
	square_id = id ;
	pSquare = _pSquare;
	volume = 0.4; // value from Bacsim
	id_level = last_used_stack+1;
	dry_mass = 2663.4; 
	mr = mass_at_division;
	printf("mr %f \n",mr);
	U = 0;
	tbact = 0;
	dividing = false;
	printf("on ajoute une bacterie au square %d  et au niveau %d \n", id, id_level);	
}



void Bacteria::uptake(Lattice &lattice){

	//float U; // number of nutrients per timestep that is going to be consummed
	double Z; // a random value centered around mean Umax and std deviantion std_u
	float S; // surface : contact from where the nutriments are going to be absorbed 
	float c; // a normalization constant	
	
	c = pow(((36*M_PI)/pow(p,2)),1/3);
	
	S = c * pow(dry_mass,2/3);


  	boost::mt19937 rng; 

  	boost::normal_distribution<> nd(Umax_mean, std_dev_Umax);

  	boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > var_nor(rng, nd);

	Z = var_nor();

	U = Z * S;

	// PENSER A PRENDRE DU SUBSTRAT SUR PLUSIEURS CASES SUR PLUSIEURS CASES

	float substrate = lattice[square_id].get_substrate();

	float substrate_consummed = k * substrate;

	if (U>=substrate_consummed){
		
		U = substrate_consummed;
		lattice[square_id].diminish_substrate(U);

	}	
	
	else{

		lattice[square_id].diminish_substrate(U);
	}

	//printf("substrat consomme %f \n",U);

}

void Bacteria::metabolism_indisim(Lattice &lat){

	float E = dry_mass * I; // maintenance energy

	if (U >= E){


		float B = ( U - dry_mass*I)*Y;
		dry_mass = dry_mass + B;

	}
	else{

		// A COMPLETER 

	}

}

void Bacteria::check_entering_division(){

	if ( dry_mass > mr ){
		dividing=true;

	}
}

bool Bacteria::check_divide(){

	if (tbact > tr){
		
		dividing = false;
			
		return true;
	}

	return false;
}

void Bacteria::update_time(float dt){

	if (dividing==true){
		tbact += dt;
	}
	else{
		}

}

int Bacteria::divide_indisim(Lattice &lat){

	std::vector<int> potential_sites_of_division_ids = neighbor_square_ids;
	

	while (potential_sites_of_division_ids.size()!=0){
		
		int new_square_id_index = rand() % potential_sites_of_division_ids.size();
		
		if (lat[potential_sites_of_division_ids[new_square_id_index]].is_full()){
			
			//printf("pas de place dans le square %d \n",potential_sites_of_division_ids[new_square_id_index]);
			potential_sites_of_division_ids.erase(potential_sites_of_division_ids.begin()+new_square_id_index);
		
		}
		else{
				dry_mass = dry_mass /2;
			return(potential_sites_of_division_ids[new_square_id_index]);			
        	}

    	}
		return -1;	
}

void Bacteria::set_dry_mass(float m){
	
	dry_mass = m;

}

int Bacteria::square_to_move_to(Lattice &lat){

	float probability = get_uniform(0,1);
	if (probability < pmov){
	
	for (int i = 0; i < neighbor_square_ids.size();i++){
		if (lat[neighbor_square_ids[i]].is_full()){
				}
		else{
			return neighbor_square_ids[i];	
		}
		
	}

	}
	return -1; // return -1 if the probability doesn't make the bacteria move or if there is no free square 
}

void Bacteria::change_stack_level(int stack_level){
	printf("dans la fonction change_stack_level de bacterie \n");
	printf("stack level : %d \n",stack_level);

	int a = id_level;
	//id_level = stack_level;

}	
void Bacteria::test(){

	std::cout << "hello \n" << std::endl;
}
