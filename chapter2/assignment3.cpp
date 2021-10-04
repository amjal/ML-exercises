#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<cmath>
#include<DataManager.hpp>

int example_num = 0;
float sigma;
float u_min = 100;
float u_max = 0;

// {class label -> {attribute -> attribute values}}
//std::map<std::string, std::map<std::string, std::vector<float>>> example_set;
// The number of examples for each class is held in a separate map
//std::map<std::string, int> class_num;

std::string classify(example* ex, size_t examples_num, const std::map<std::string, std::vector<example*>> & grouped_examples){
	sigma = (u_max - u_min)/float(example_num);
	float max_p = 0;
	std::string label;
	//pci denotes P(Ci)
	float pci;
	//pxic denotes P(X | Ci)
	float pxci = 1;
	//obtain iterator for example set
	std::map<std::string, std::map<std::string, std::vector<float>>>::iterator class_it;
	//Iterate through all different classes of examples
	for(class_it = example_set.begin(); class_it != example_set.end(); class_it++){
		//For each class calculate the probability of that class
		pci = float(class_num[class_it->first])/ float(example_num);
		pxci = 1;
		//obtain iterator of example
		std::map<std::string, float>::iterator example_it;
		//Iterate through all attributes of the new example
		for(example_it = new_example.begin() ; example_it != new_example.end(); example_it ++){
			float pxi = 0;
			// Check if the current attribute exists in the class list
			if(class_it->second.count(example_it->first)){
				//Now calculate the superposition pdf of the current attribute
				for(int i =0; i < class_it->second[example_it->first].size(); i ++){
					pxi += exp(-(example_it->second - class_it->second[example_it->first][i])/2.0);
				}
			}
			pxi /= example_num*sigma*sqrt(2*M_PI);
			// This is the naive Bayesian assumption
			pxci *= pxi;
		}
		pxci *= pci;
		std::cout<<class_it->first<<": "<<pxci<<std::endl;
		//Find which class maximaizes P(X|Ci)*P(Ci)
		if(pxci > max_p){
			max_p = pxci;
			label = class_it -> first;
		}
	}
	return label;
}
		
int main(){
    DataManager dm("../chapter2/datasets/", true);
    std::vector<example*> example_list = dm.getListExamples();
    std::map<std::string, std::vector<example*>> grouped_examples = dm.getGroupedExamples();

    /*
	printf("Now enter the attribute set for the example you want to label:\n");
	std::map <std::string, float> new_example;
	while(true){
		std::string input;
		std::getline(std::cin, input);
		if(input.length() == 0) break;
		int space_loc = input.find(' ');
		std::string attr_name = input.substr(0, space_loc);
		float attr_value = std::stof(input.substr(space_loc +1, input.length() - space_loc));
		new_example[attr_name] = attr_value;
	}
     */
	std::cout<<classify(new_example)<<std::endl;
	return 0;
}
