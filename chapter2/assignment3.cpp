#include<iostream>
#include<string>
#include<map>
#include<vector>

int example_num = 0;

std::map<std::string, std::map<std::string, float[2]>> example_set;

example classify(example ex){
	float max_p = 0;
	//pci denotes P(Ci)
	float pci;
	//pxic denotes P(X | Ci)
	float pxci = 1;
	//Iterate through all different classes of examples
	for(std::map<std::string, std::vector<example>>::iterator class_it = example_set.begin() ; class_it != example_set.end(); class_it++){
		//For each class calculate the probability of that class
		pci = float((class_it->second).size()) / float(example_num);
		pxci = 1;
		//Iterate through all attributes of the ex example
		for(std::map<std::string, std::string>::iterator att_it = ex.attribute_set.begin() ; att_it != ex.attribute_set.end(); att_it ++){
			float att_num = 0;
			float att_match = 0;
			//Now iterate through all examples belonging to the same class calculating the probability P(Xi|Ci)
			for(int i=0 ; i< (class_it->second).size() ; i++){
				//First check if the example in vector has this particular attribute of ex
				if((class_it->second)[i].attribute_set.count(att_it->first)){
					att_num ++;
					if((class_it->second)[i].attribute_set[att_it->first] == att_it->second){
						att_match ++;
					}
				}
			}
			// This is naive bayesian assumption in which all attributes are assumed to be independent
			pxci *= (att_match/att_num);
		}
		pxci *= pci;
		std::cout<<class_it->first<<": "<<pxci<<std::endl;
		//Find which class maximaizes P(X|Ci)*P(Ci)
		if(pxci > max_p){
			max_p = pxci;
			ex.class_label = class_it->first;
		}
	}
	return ex;
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
		// number of examples will come handy in calculating P(Ci)
		example_num ++;
		//cl contains the class this example is labeled with
		//Add the example to the corresponding class label. If class label doesn't exist add it.
		if (example_set.find(cl) == example_set.end()){//This means the class doesn't yet exist in our example set
			example_set[cl] = std::vector<example>();
		}
		printf("Now enter attribute values of this example:\n");
		while(true){
			std::string input;
			std::getline(std::cin, input);
			if(input.length() == 0) break;
			int space_loc = input.find(' ');
			std::string attr_name = input.substr(0, space_loc);
			std::string attr_value = input.substr(space_loc+1 , input.length() - space_loc);
			temp.attribute_set[attr_name] = attr_value;
		}
		example_set[cl].push_back(temp);
	}
	printf("Now enter the attribute set for the example you want to label:\n");
	example ex;
	while(true){
		std::string input;
		std::getline(std::cin, input);
		if(input.length() == 0) break;
		int space_loc = input.find(' ');
		std::string attr_name = input.substr(0, space_loc);
		std::string attr_value = input.substr(space_loc +1, input.length() - space_loc);
		ex.attribute_set[attr_name] = attr_value;
	}
	classify(ex);
	return 0;
}
