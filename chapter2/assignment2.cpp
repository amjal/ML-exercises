#include<string>
#include<map>
#include<vector>
#include"../cpp_csv_handler.h"

int example_num = 0;

// A map from class label to examples that are labeled with that class label
std::map<std::string, std::vector<example>> example_set;
// This has has the following structure: { class label --> {attribute value --> {probability of the attribute in the class}}}
std::map<std::string, std::map<std::string, float>> attribute_probs;

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
			// Have we calculated the probability of this attribute for this class before?
			if (attribute_probs[class_it -> first].count(att_it -> second) == 0){// If no then calculate it
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
				attribute_probs[class_it ->first][att_it ->second] = att_match/att_num;
			}
			// This is naive bayesian assumption in which all attributes are assumed to be independent
			pxci *= attribute_probs[class_it ->first][att_it ->second];
		}
		pxci *= pci;
		//Find which class maximaizes P(X|Ci)*P(Ci)
		if(pxci > max_p){
			max_p = pxci;
			ex.class_label = class_it->first;
		}
	}
	return ex;
}
		
int main(){
	csvhandler file_handler;	
	printf("Reading data from file...\n");
	std::vector<example> example_vector = file_handler.get_examples("datasets/agaricus8.data");
	example_num = example_vector.size();
	printf("Grouping examples...\n");
	example_set = file_handler.get_grouped_examples(example_vector);
	printf("Running tests...\n");
	int true_positive =0;
	for(int i=0 ; i < example_vector.size(); i++){
		std::string cl = example_vector[i].class_label;
		example ex = classify(example_vector[i]);	
		if(ex.class_label == cl)
			true_positive ++;
	}
	printf("%f\n", float(true_positive)/float(example_vector.size()));
	return 0;
}
