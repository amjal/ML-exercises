#include "headers/problem.h"
#include "headers/local_search.h"
#include<iostream>
#include<math.h>
int local_search:: evaluate(problem* arg){
	int result = 0;
	for(unsigned i=0 ; i < arg->relations.size(); i++)
		for (unsigned j=0; j <arg->relations.at(i).size() ; j ++)
			if(arg->relations.at(i).at(j)->color == arg->cells.at(i)->color)
				result ++;
	return result;
}
bool normal_hill_climbing:: choose_next_state(){
	problem* temp;
	problem* next_state = new problem(p);
	bool local_minimum = true;
	for(unsigned i = 0; i < p->cells.size() ; i ++){
		num_visited += 2;
		temp = new problem(p);
		cell_color initial_color =  temp->cells.at(i)->color;
		temp->cells.at(i)->color = static_cast<cell_color>((initial_color+1)%3); 
		if(evaluate(temp) < evaluate(next_state)){
			*next_state = *temp;
			local_minimum = false;
		}
		temp->cells.at(i)->color = static_cast<cell_color>((initial_color+2)%3);
		if(evaluate(temp) < evaluate(next_state)){
			*next_state = *temp;
			local_minimum = false;
		}
	}
	*p = *next_state;
	num_expanded++;
	return local_minimum;
}

void normal_hill_climbing:: search(){
	num_visited = 0;
	num_expanded = 0;
	while(!choose_next_state());
}
void stochastic_hill_climbing:: find_downhill_states(){
	problem* temp = new problem();
	downhill_states.resize(0);
	steepness_sum = 0;
	bool downhill_found = false;
	int current_value = evaluate(p);
	int steepness;
	for(unsigned i =0; i < p->cells.size() ; i++){
		temp = new problem(p);
		num_visited +=2;
		cell_color initial_color =  temp->cells.at(i)->color;
		temp->cells.at(i)->color = static_cast<cell_color>((initial_color+1)%3); 
		steepness = current_value - evaluate(temp);
		if(steepness > 0){
			downhill_states.push_back(temp);
			steepness_sum += steepness;
		}
		temp->cells.at(i)->color = static_cast<cell_color>((initial_color+2)%3);
		steepness = current_value - evaluate(temp);
		if(steepness > 0){
			downhill_states.push_back(temp);
			steepness_sum += steepness;
		}
	}
}

void stochastic_hill_climbing:: search(){
	num_visited = 0;
	num_expanded = 0;
	do{
		find_downhill_states();
		int steepness;
		int current_value = evaluate(p);
		for(unsigned i =0; i < downhill_states.size() ; i++){
			steepness = evaluate(p) - evaluate(downhill_states.at(i));
			next_state_probabilities.push_back((int)((float)(steepness)/(float)(steepness_sum)*100));
		}
		int r = rand()%100;
		int c=0;
		for(unsigned i =0; i < downhill_states.size() ; i++){
			if(r>=c && r<(c+next_state_probabilities.at(i))){// this is chosen
				p = new problem(downhill_states.at(i));
				num_expanded ++;
				break;
			}
			else c+= next_state_probabilities.at(i);
		}
	}while(downhill_states.size());
}
		
bool first_choice_hill_climbing:: find_first_downhill_state(){
	cells_left_indices.resize(0);
	for(unsigned i =0; i < p->cells.size() ; i++) cells_left_indices.push_back(i);
	int steepness;
	bool downhill_found = false;
	problem* temp;
	int current_value = evaluate(p);
	int next_cell_index;
	while(cells_left_indices.size()){
		int i = rand()%(cells_left_indices.size());
		next_cell_index = cells_left_indices.at(i);
		cells_left_indices.erase(cells_left_indices.begin()+i);
		temp = new problem(p);
		cell_color initial_color =  temp->cells.at(next_cell_index)->color;
		num_visited ++;
		temp->cells.at(next_cell_index)->color = static_cast<cell_color>((initial_color+1)%3); 
		steepness = current_value - evaluate(temp);
		if(steepness > 0){
			*p = *temp;
			num_expanded ++;
			return true;
		}
		temp->cells.at(next_cell_index)->color = static_cast<cell_color>((initial_color+2)%3);
		num_visited ++;
		steepness = current_value - evaluate(temp);
		if(steepness > 0){
			*p = *temp;
			num_expanded ++;
			return true;
		}
	}
	return false;
}
void first_choice_hill_climbing:: search(){
	num_visited = 0;
	num_expanded = 0;
	while(find_first_downhill_state());
}

void random_restart_hill_climbing:: search(){
	num_visited = 0;
	num_expanded = 0;
	problem* best_answer_found = new problem(p);
	for(int i =0; i < 100 && evaluate(p) ; i++){//the number of restarts is 100
		p->assign_random_colors();
		normal_hill_climbing helper(p);
		helper.search();
		num_visited += helper.num_visited;
		num_expanded += helper.num_expanded;
		if(evaluate(p) < evaluate(best_answer_found))
			best_answer_found = new problem(p);
	}
}
void simulated_annealing::choose_next_state(){
	cells_left_indices.resize(0);
	for(unsigned i =0; i < p->cells.size() ; i++) cells_left_indices.push_back(i);
	int steepness;
	problem* temp;
	int current_value = evaluate(p);
	int next_cell_index;
	while(cells_left_indices.size()){
		int i = rand()%(cells_left_indices.size());
		next_cell_index = cells_left_indices.at(i);
		cells_left_indices.erase(cells_left_indices.begin()+i);
		temp = new problem(p);
		cell_color initial_color =  temp->cells.at(next_cell_index)->color;
		num_visited ++;
		temp->cells.at(next_cell_index)->color = static_cast<cell_color>((initial_color+1)%3); 
		steepness = current_value - evaluate(temp);
		if(steepness > 0){
			*p = *temp;
			num_expanded ++;
			return;
		}
		else {
			float time_ms = (float)(clock() - start)/(float)(CLOCKS_PER_SEC/1000);
			float temperature = scheduling_arg/time_ms;
			int probability_percentage = (int)(100*exp((double)(steepness/temperature)));
			std::cout<<temperature<<"  "<<steepness<<"  "<< probability_percentage<<std::endl;
			int r = rand()%100;
			if(r < probability_percentage){
				*p = *temp;
				num_expanded ++;
				return;
			}
		}
		temp->cells.at(next_cell_index)->color = static_cast<cell_color>((initial_color+2)%3);
		num_visited ++;
		steepness = current_value - evaluate(temp);
		if(steepness > 0){
			*p = *temp;
			num_expanded ++;
		}
		else{
			float time_ms = (float)(clock() - start)/(float)(CLOCKS_PER_SEC/1000);
			float temperature = scheduling_arg/time_ms;
			int probability_percentage = (int)(100*exp((double)(steepness/temperature)));
			std::cout<<temperature<<"  "<<steepness<<"  "<< probability_percentage<<std::endl;
			int r = rand()%100;
			if(r < probability_percentage){
				*p = *temp;
				num_expanded ++;
				return;
			}
		}
	}
}
void simulated_annealing:: search(){
	num_visited = 0;
	num_expanded = 0;
	while(evaluate(p) && ((float)(clock() - start)/(float)(CLOCKS_PER_SEC/1000) < time_limit_ms))
		choose_next_state();
}

void genetic:: population_init(){
	problem* temp;
	for(unsigned i =0 ; i < population_size ; i ++){// the population size is 1000
		temp = new problem();
		temp->assign_random_colors();
		population.push_back(temp);
	}
}

problem* genetic:: pick_parent(){
	int r = rand()%1000000;
	int c= 0;
	for(unsigned i =0; i < population.size() ; i++){
		if(r>=c && r<(c+next_state_probabilities.at(i))){// this is chosen
			return population.at(i);	
		}
		else c+= next_state_probabilities.at(i);
	}
	return population.at(0);
}

problem* genetic::reproduce(problem* parent1, problem* parent2){
	problem* child = new problem();
	unsigned i=0;
	for( ; i < child->cells.size()/2; i ++)
		child->cells.at(i)->color = parent1->cells.at(i)->color;
	for( ; i < child->cells.size(); i ++)
		child->cells.at(i)->color = parent2->cells.at(i)->color;
	return child;
}
	
void genetic::mutate(problem* arg){
	int r = rand() % arg->cells.size();
	arg->cells.at(r)->color = static_cast<cell_color>(rand()%3);
}
void genetic::evolve(){
	std::vector<problem*> new_population;
	int fitness_sum = 0;
	for(unsigned i =0 ; i < population.size() ; i ++)
		fitness_sum += (41 - evaluate(population.at(i)));
	for(unsigned i =0 ; i < population.size() ; i ++)
		next_state_probabilities.push_back(1000000*((float)(41 -evaluate(population.at(i)))/(float)fitness_sum));
	for(unsigned i =0; i < population.size() ; i++){
		problem* p1 = pick_parent();
		problem* p2 = pick_parent();
		problem* child = reproduce(p1, p2);
		int r = rand()%100;
		if(r<mutation_probability)
			mutate(child);
		new_population.push_back(child);
	}
	population.swap(new_population);
	problem* fittest = population.at(0);
	problem* least_fit = population.at(0);
	for(unsigned i =0 ; i < population.size() ; i ++){
		if(evaluate(population.at(i))<evaluate(fittest))
			fittest = population.at(i);
		if(evaluate(population.at(i))>evaluate(least_fit))
			least_fit = population.at(i);
	}
	std::cout<<(41 - evaluate(least_fit))<<" " <<(41 - evaluate(fittest))<<" "<<
			(float)fitness_sum/population.size()<<std::endl;
	p = new problem(fittest);
	count ++;
}	

void genetic:: search(){
	population_init();
	while(evaluate(p) && ((float)(clock() - start)/(float)(CLOCKS_PER_SEC/1000))<time_limit_ms) evolve();
}
