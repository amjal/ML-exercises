#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<math.h>

int example_num = 0;
float sigma;
float u_min = 100;
float u_max = 0;

// {class label -> {attribute -> attribute values}}
std::map<std::string, std::map<std::string, std::vector<float>>> example_set;
std::map<std::string, int> class_num;

std::string classify(std::map <std::string, float> new_example){
	sigma = (u_max - u_min)/float(example_num);
	float max_p = 0;
	std::string label;
	//pci denotes P(Ci)
	float pci;
	//pxic denotes P(X | Ci)
	float pxci = 1;
	//obtain iterator for example set
	std::map<std::string, std::map<std::string, std::vector<float>>>:: iterator class_it;
	//Iterate through all different classes of examples
	for(class_it = example_set.begin() ; class_it != example_set.end(); class_it++){
		//For each class calculate the probability of that class
		pci = float(class_num[class_it->first])/ float(example_num);
		pxci = 1;
		//obtain iterator of example
		std::map<std::string, float>::iterator example_it;
		//Iterate through all attributes of the new example
		for(example_it = new_example.begin() ; example_it != example.end(); example_it ++){
			float pxi = 0;
			// Check if the current attribute exists in the class list
			if(class_it->second.count(example_it->first)){
				//Now calculate the superposition pdf of the current attribute
				for(int i =0; i < class_it->second[example_it->first].size(); i ++){
					pxi += exp(-(example_it->second - class_it->second[example_it->first][i])/2.0);
				}
			}
			//TODO define sigma
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
	printf("Please enter examples and their corresponding attributes in the following format:\n");
	printf("<example class label>\\n<attr name><space><attr value>\\n[<attr name><space><attr value>\\n...]\\n\n");
	printf("enter exit as example class label when finished\n\n");
	while(true){
		printf("Enter class label of the example:(enter done when you're done)\n");
		// cl denotes class label of each example that the user enters
		std::string cl;
		std::getline(std::cin, cl);
		if (cl == "exit") return 0;
		if (cl == "done") break;
		//cl contains the class this example is labeled with
		//Add the example to the corresponding class label. If class label doesn't exist add it.
		if (example_set.find(cl) == example_set.end()){//This means the class doesn't yet exist in our example set
			example_set[cl] = std::map<std::string, float*>();
			class_num[cl] = 0;
		}
		// number of examples will come handy in calculating P(Ci) and normalizing sigma
		example_num ++;
		class_num[cl] ++;
		printf("Now enter attribute values of this example:\n");
		while(true){
			std::string input;
			std::getline(std::cin, input);
			if(input.length() == 0) break;
			int space_loc = input.find(' ');
			std::string attr_name = input.substr(0, space_loc);
			std::string attr_value = std::stof(input.substr(space_loc+1 , input.length() - space_loc));
			//If this attribute name doesn't exist in attribute list then add it
			if(example_set[cl].find(attr_name) == example_set[cl].end())
				example_set[cl][attr_name] = std::vector<float>();
			// We need to calculate u_max - u_min for sigma
			if (attr_value > u_max){
				u_max = attr_value;
			}
			else if(attr_value < u_min){
				u_min = attr_value;
			}
		}
	}
	printf("Now enter the attribute set for the example you want to label:\n");
	std::map <std::string, float> new_example;
	while(true){
		std::string input;
		std::getline(std::cin, input);
		if(input.length() == 0) break;
		int space_loc = input.find(' ');
		std::string attr_name = input.substr(0, space_loc);
		std::string attr_value = std::stof(input.substr(space_loc +1, input.length() - space_loc));
		new_example[attr_name] = attr_value;
	}
	classify(new_example);
	return 0;
}
