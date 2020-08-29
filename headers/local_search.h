#include<vector>
#include<stdlib.h>
#include<time.h>
class problem;
class local_search{
	public:
		problem* p;
		int num_visited;
		int num_expanded;
		inline local_search(problem* p):p(p){srand(time(0));}
		int evaluate(problem* arg);
};
class normal_hill_climbing: public local_search{
	public:
		inline normal_hill_climbing(problem* p):local_search(p){}
		bool choose_next_state();
		void search();
};
class stochastic_hill_climbing:public local_search{
	public:
		int steepness_sum;
		std::vector<problem*> downhill_states;	
		std::vector<int> next_state_probabilities;
		inline stochastic_hill_climbing(problem* p):local_search(p){}
		void find_downhill_states();
		void search();
};
class first_choice_hill_climbing: public local_search{
	public:
		std::vector<int> cells_left_indices;
		inline first_choice_hill_climbing(problem* p):local_search(p){}
		bool find_first_downhill_state();
		void search();
};
	
class random_restart_hill_climbing: public local_search{
	public:
		inline random_restart_hill_climbing(problem* p):local_search(p){}
		void search();
};

class simulated_annealing: public local_search{
	public:
		std::vector<int> cells_left_indices;
		clock_t start;
		float scheduling_arg;
		float time_limit_ms;
		inline simulated_annealing(problem* p,float arg1, float arg2):local_search(p), scheduling_arg(arg1), time_limit_ms(arg2){start = clock();}
		void search();
		void choose_next_state();
};
class genetic: public local_search{
	public: 
		clock_t start; 
		float time_limit_ms;
		int mutation_probability;
		int population_size;
		int count = 0;
		std::vector<problem*> population;
		std::vector<int>next_state_probabilities;
		inline genetic(problem* p, float arg1, int arg2, int arg3):local_search(p), time_limit_ms(arg1), mutation_probability(arg2), population_size(arg3){start = clock();}
		void population_init();
		void search();
		void mutate(problem* arg);
		problem* pick_parent();
		void evolve();	
		problem* reproduce(problem* parent1 , problem* parent2);
};
