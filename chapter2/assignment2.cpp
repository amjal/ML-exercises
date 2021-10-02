#include<string>
#include<map>
#include<vector>
#include<iostream>
#include<DataManager.h>

std::map<std::string, std::vector<std::map<std::string,float>>> attribute_probs;

std::string classify(example* ex, size_t examples_num, const std::map<std::string, std::vector<example*>>& grouped_examples){
    std::string result;
    // I don't remove the example I want to classify from the list assuming the error that creates is negligible
	float max_p = 0;
	//pci denotes P(Ci)
	float pci;
	//pxic denotes P(X | Ci)
	float pxci = 1;
	//Iterate through all different classes of examples
	for(const auto & class_it : grouped_examples){
        std::string ci = class_it.first;
		//For each class calculate the probability of that class
		pci = float((class_it.second).size()) / float(examples_num);
		//std::cout << pci << "  " << ci << '\n';
		pxci = 1;
		//Iterate through all attributes of the ex example
		for(size_t att_index = 0; att_index< ex->attributes.size(); att_index ++){
		    std::string atti = ex->attributes.at(att_index);
			// Have we calculated the probability of this attribute for this class before?
			if (attribute_probs[ci].at(att_index).find(atti) == attribute_probs[ci].at(att_index).end()){// If no then calculate it
				long double att_num = class_it.second.size();
				long double att_match = 0;
				//Now iterate through all examples belonging to the same class calculating the probability P(Xi|Ci)
				for(example* ci_exi_it : class_it.second){
					//First check if the example in vector has this particular attribute of ex
					if(ci_exi_it->attributes.at(att_index) == atti)
                        att_match ++;
				}
				attribute_probs[ci].at(att_index)[atti] = att_match/att_num;
			}
			// This is naive bayesian assumption in which all attributes are assumed to be independent
			pxci *= attribute_probs[ci].at(att_index)[atti];
		}
		pxci *= pci;
		//Find which class maximaizes P(X|Ci)*P(Ci)
		if(pxci > max_p){
			max_p = pxci;
			result = ci;
		}
	}
	return result;
}

int main(){
    DataManager dm("../chapter2/datasets/agaricus8.data", 0,  false);
	printf("Reading data from file...\n");
    std::vector<example*> example_list = dm.getListExamples();
    printf("Grouping examples...\n");
    std::map<std::string, std::vector<example*>> grouped_examples = dm.getGroupedExamples(example_list);
	printf("Running tests...\n");
	// Initialize the attribute_probs map, this reduces the runtime in the classify function
	for(const auto& class_it : grouped_examples){
	    attribute_probs[class_it.first] = std::vector<std::map<std::string,float>>();
	    attribute_probs[class_it.first].assign(example_list.at(0)->attributes.size(), std::map<std::string,float>());
	}
	size_t true_positive =0;
	for(auto* ex : example_list){
	    std::string orig_label = ex -> label;
	    std::string new_label = classify(ex, dm.examples_num, grouped_examples);
	    if(new_label == orig_label)
	        true_positive ++;
	}
	printf("%f\n", float(true_positive)/float(dm.examples_num));
	return 0;
}
