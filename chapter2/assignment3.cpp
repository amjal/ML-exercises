#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<cmath>
#include<DataManager.hpp>
#include<algorithm>


std::vector<float> sigmas;
std::vector<float> u_max;
std::vector<float> u_min;

float classify(example<float>* ex, size_t examples_num, const std::map<float, std::vector<example<float>*>> & grouped_examples){
    // Calculate sigma for each attribute
	float max_p = 0;
	float result;
	//pci denotes P(Ci)
	float pci;
	//pxic denotes P(X | Ci)
	float pxci = 1;
	//Iterate through all different classes of examples
	for(const auto & class_it : grouped_examples){
		//For each class calculate the probability of that class
		pci = float(class_it.second.size())/float(examples_num);
		//Iterate through all attributes of the new example
		for(size_t att_index =0 ; att_index < ex->attributes.size(); att_index ++){
            const float denominator = (examples_num -1)*sigmas.at(att_index)*sqrt(2*M_PI);
			float pxi = 0;
            //Now calculate the superposition pdf of the current attribute
            for(example<float>* ci_exi_it : class_it.second){
                // Do not calculate the test examples as data
                if(ex != ci_exi_it){
                    float pow = ex->attributes.at(att_index) - ci_exi_it->attributes.at(att_index);
                    pxi += exp(-pow*pow/2.0/sigmas.at(att_index)/sigmas.at(att_index));
                }
            }
			pxi /= denominator;
			// This is the naive Bayesian assumption
			pxci *= pxi;
		}
		pxci *= pci;
		//Find which class maximaizes P(X|Ci)*P(Ci)
		if(pxci > max_p){
			max_p = pxci;
			result = class_it.first;
		}
	}
	return result;
}

int main(){
    DataManager<float> dm("../chapter2/datasets/Frogs_MFCCs.csv", true);
    std::cout << "Reading examples from file...\n";
    std::vector<example<float>*> example_list = dm.getListExamples();
    std::cout << "Grouping examples...\n";
    std::map<float, std::vector<example<float>*>> grouped_examples = dm.getGroupedExamples(example_list);
    size_t examples_num = example_list.size();
    // Initialize u_max and u_min lists
    u_max = example_list.at(0)->attributes;
    u_min = example_list.at(0)->attributes;
    // Calculate sigmas
    std::cout << "Calculating parameters...\n";
    for(int att_index = 0 ; att_index < u_max.size() ; att_index ++){
        for(example<float>* ex : example_list){
            if (ex->attributes.at(att_index) > u_max.at(att_index))
                u_max.at(att_index) = ex->attributes.at(att_index);
            else if ( ex->attributes.at(att_index) < u_min.at(att_index))
                u_min.at(att_index) = ex->attributes.at(att_index);
        }
        sigmas.push_back((u_max.at(att_index) - u_min.at(att_index))/float(examples_num));
        //std::cout << sigmas.at(att_index)<< "  ";
    }
    std::cout << '\n';
    sigmas.assign(u_max.size(), 1);
    // Now classify and see the results
    std::cout << "classifying...\n";
    size_t true_positive = 0;
    for(example<float>* ex: example_list){
        float result =  classify(ex, examples_num, grouped_examples);
        if(result == ex->label)
            true_positive ++;
    }
    std::cout << float(true_positive)/float(examples_num);
	return 0;
}
