#include<iostream>
#include<string>
#include "headers/problem.h"
#include "headers/local_search.h"
int process_command(std::string in){
	problem* p = new problem();
	std::string args[5];
	int c=0;
	for(int i=0; i < in.length(); i++){
		if(in.at(i) == ' '){
			args[c++] = in.substr(0,i);
			in.erase(0,i+1);
			i = -1;
		}
	}
	args[c] = in;
	if(args[0] == "exit")
		return 0;
	if(args[0] == "hill" && args[1] == "normal"){
		normal_hill_climbing engine(p);
		engine.search();
		std::cout<<"solution:\n";
		engine.p->print_colors();
		std::cout<<"value: "<<engine.evaluate(engine.p)<<'\n';
		std::cout<<"number of expanded: "<<engine.num_expanded<<'\n';
		std::cout<<"number of visited: "<<engine.num_visited<<"\n\n";
		return 1;
	}
	if(args[0] == "hill" && args[1] == "stochastic"){
		stochastic_hill_climbing engine(p);
		engine.search();
		std::cout<<"solution:\n";
		engine.p->print_colors();
		std::cout<<"value: "<<engine.evaluate(engine.p)<<'\n';
		std::cout<<"number of expanded: "<<engine.num_expanded<<'\n';
		std::cout<<"number of visited: "<<engine.num_visited<<"\n\n";
		return 1;
	}
	if(args[0] == "hill" && args[1] == "first-choice"){
		first_choice_hill_climbing engine(p);
		engine.search();
		std::cout<<"solution:\n";
		engine.p->print_colors();
		std::cout<<"value: "<<engine.evaluate(engine.p)<<'\n';
		std::cout<<"number of expanded: "<<engine.num_expanded<<'\n';
		std::cout<<"number of visited: "<<engine.num_visited<<"\n\n";
		return 1;
	}
	if(args[0] == "hill" && args[1] == "restart"){
		random_restart_hill_climbing engine(p);
		engine.search();
		std::cout<<"solution:\n";
		engine.p->print_colors();
		std::cout<<"value: "<<engine.evaluate(engine.p)<<'\n';
		std::cout<<"number of expanded: "<<engine.num_expanded<<'\n';
		std::cout<<"number of visited: "<<engine.num_visited<<"\n\n";
		return 1;
	}
	if(args[0] == "simulated" && args[1] == "annealing"){
		simulated_annealing engine(p, stof(args[2]), stof(args[3]));
		engine.search();
		std::cout<<"solution:\n";
		engine.p->print_colors();
		std::cout<<"value: "<<engine.evaluate(engine.p)<<'\n';
		std::cout<<"number of expanded: "<<engine.num_expanded<<'\n';
		std::cout<<"number of visited: "<<engine.num_visited<<"\n\n";
		return 1;
	}
	if(args[0] == "genetic"){
		genetic engine(p,stof(args[1]), stoi(args[2]), stoi(args[3]));
		engine.search();
		std::cout<<"solution:\n";
		engine.p->print_colors();
		std::cout<<"value: "<<engine.evaluate(engine.p)<<'\n';
		std::cout<<"generations: "<<engine.count<<"\n\n";
		return 1;
	}
	std::cout <<"invalid command\n";
	return -1;
}


int main(){
	std::string in;
	int process_code;
	do{
		getline(std::cin, in);
		process_code = process_command(in);
	}while(process_code);	
}
