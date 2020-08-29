#include "headers/problem.h"
#include<iostream>
void problem::make_relations(){
	std::vector<cell*> temp;
	for(unsigned i =0; i < 11 ; i++){//set relations
		temp.resize(0);
		switch(i){
			case 0:
				temp.push_back(cells.at(2));
				temp.push_back(cells.at(3));
				temp.push_back(cells.at(8));
				temp.push_back(cells.at(10));
				break;
			case 1:
				temp.push_back(cells.at(2));
				temp.push_back(cells.at(4));
				temp.push_back(cells.at(5));
				temp.push_back(cells.at(10));
				break;
			case 2:
				temp.push_back(cells.at(0));
				temp.push_back(cells.at(1));
				temp.push_back(cells.at(6));
				break;
			case 3:
				temp.push_back(cells.at(0));
				temp.push_back(cells.at(4));
				temp.push_back(cells.at(6));
				break;
			case 4:
				temp.push_back(cells.at(1));
				temp.push_back(cells.at(3));
				temp.push_back(cells.at(7));
				temp.push_back(cells.at(8));
				break;
			case 5:
				temp.push_back(cells.at(1));
				temp.push_back(cells.at(6));
				temp.push_back(cells.at(8));
				break;
			case 6:
				temp.push_back(cells.at(2));
				temp.push_back(cells.at(3));
				temp.push_back(cells.at(5));
				temp.push_back(cells.at(7));
				temp.push_back(cells.at(9));
				break;
			case 7:
				temp.push_back(cells.at(4));
				temp.push_back(cells.at(6));
				temp.push_back(cells.at(10));
				break;
			case 8:
				temp.push_back(cells.at(0));
				temp.push_back(cells.at(4));
				temp.push_back(cells.at(5));
				temp.push_back(cells.at(9));
				break;
			case 9:
				temp.push_back(cells.at(6));
				temp.push_back(cells.at(8));
				temp.push_back(cells.at(10));
				break;
			case 10:
				temp.push_back(cells.at(0));
				temp.push_back(cells.at(1));
				temp.push_back(cells.at(7));
				temp.push_back(cells.at(9));
				break;	
		}
		relations.push_back(temp);
	}
}

problem::problem(problem* p){
	for(unsigned i =0 ; i< p->cells.size() ; i++){
		cell* c = new cell(i);
		c->color = p->cells.at(i)->color;
		cells.push_back(c);
	}
	make_relations();
}

problem::problem(){
	for( unsigned i =0 ; i < 11 ; i ++){//make cells
		cell* temp = new cell(i);
		cells.push_back(temp);
	}
	make_relations();
}	
void problem:: print_colors(){
	std::cout <<"   "<<cells.at(0)->color<<"   \n";
	std::cout <<cells.at(1)->color<<' '<<cells.at(2)->color<<' ';
	std::cout <<cells.at(3)->color<<' '<<cells.at(4)->color<<'\n';
	std::cout <<' '<<cells.at(5)->color<<' '<<cells.at(6)->color;
	std::cout <<' '<<cells.at(7)->color<<" \n";
	std::cout <<' '<<cells.at(8)->color<<' '<<cells.at(9)->color;
	std::cout <<' '<<cells.at(10)->color<<" \n";
}
void problem:: assign_random_colors(){
	for(unsigned i =0; i < cells.size() ; i ++)
		cells.at(i)->color = static_cast<cell_color>(rand()%3);
}
