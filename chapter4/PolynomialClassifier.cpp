#include "PolynomialClassifier.h"
#include<fstream>
#include<sstream>
#include<stdio.h>

PolynomialClassifier::PolynomialClassifier(std::vector<example> training_set, uint8_t n, uint8_t r):training_set(training_set), n(n), r(r){
	std::vector<uint8_t> parent_term;
	create_term(0, parent_term, r);
}

PolynomialClassifier::PolynomialClassifier(std::string file_path, uint8_t r){
	std::vector<example> training_set;
	// Open the file using the given file path
	std::ifstream fin(file_path);
	// Craete a string that holds the lines of our csv file
	std::string line, element;
	std::vector<float> attributes;
	uint8_t n = 0;
	if (fin.is_open()){
		// Read the first line (csv header) which contains attribute names
		getline(fin, line);
		std::stringstream ss(line);
		while (getline(ss, element, ',')){
			attribute_names.push_back(element);
			// For each element increment n
			n++;
		}
		// Because we don't want to include 'lablel' in the attribute vector, decrement n
		n --;
		// Now for each example read the line 
		while (getline(fin, line)){
			std::stringstream ss(line);
			for (int i=0; i < n; i++){
				// Read the comma separated values of the line
				getline(ss, element, ',');
				// Add the value to attributes vector
				attributes.push_back(std::stof(element));
			}
			// Make an example using the just acquired attributes
			example e(attributes);
			// Read the final element which is the label
			getline(ss, element, ',');
			// Set the label of the example
			e.label = element;
			// Clear the attributes vector for use in the next example
			attributes.clear();
			// Push the newly made example into the trainig_set
			training_set.push_back(e);
		}
	}
	else printf("Error: Could not open file\n");
	PolynomialClassifier(training_set, n, r);
}

void PolynomialClassifier::create_term(uint8_t variable_num, std::vector<uint8_t> parent_term, uint8_t k){
	// In this finish case, we might still have some variables left but the variables up until now have already 
	// reached the polynomial order so we should not add any other variables
	if (k == 0){
		polynomial_terms.push_back(parent_term);
		return;
	}
	// In this finish case we have k != 0; meaning there still some power left. However, since this is last variable, 
	// make the all possible terms and finalize
	if (variable_num == n -1){
		for (uint8_t p = 0; p <=k; p++){
			parent_term.push_back(variable_num);
			parent_term.push_back(p);
			polynomial_terms.push_back(parent_term);
			// Delete the new variable and power added so the original vector yields
			parent_term.pop_back();
			parent_term.pop_back();
		}
		return;
	}
	// The first selected power for this variable is 0. then just pass the parent_term vector to 
	// your child without appending anything to it
	create_term(variable_num +1, parent_term, k);	
	// Iterate over all possible powers that are greater than zero for this variable
	for (uint8_t p = 1; p <= k; p++){
		// Push the attribute (polynomial variable) index
		parent_term.push_back(variable_num);
		// Push the power of the attribute right after it
		parent_term.push_back(p);
		// Call the function to complete the term for the next variable
		create_term(variable_num +1, parent_term, k-p);
		// Delete the new variable and power added so the original vector yields
		parent_term.pop_back();
		parent_term.pop_back();
	}
}
