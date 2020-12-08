#include "PolynomialClassifier.h"
#include<fstream>
#include<sstream>
#include<stdio.h>
#include<math.h>

void PolynomialClassifier::init(uint8_t n, uint8_t r){
	this->n = n;
	std::vector<uint8_t> parent_term;
	//scale values ([0,1])
	// i iterates over attributes (or columns)
	for (int i =0; i< n; i++){
		float min = training_set[0].attribute_vector.at(i);
		float max = training_set[0].attribute_vector.at(i);
		// j iterates over rows (or examples) to find the mininum and maximum value of i-th attribute in the training_set
		for (int j=0; j < training_set.size(); j ++){
			if (training_set.at(j).attribute_vector.at(i) > max)
				max = training_set.at(j).attribute_vector.at(i);
			else if(training_set.at(j).attribute_vector.at(i) < min)
				min = training_set.at(j).attribute_vector.at(i);
		}
		float diff = max - min;
		// j iterates over rows (or examples) this time to scale the values
		for (int j=0; j< training_set.size(); j++){
			training_set.at(j).attribute_vector.at(i) -= min;
			training_set.at(j).attribute_vector.at(i) /= diff;
		}
	}
	
	// Do the whole process again for dataset
	for (int i =0; i< n; i++){
		float min = dataset[0].attribute_vector.at(i);
		float max = dataset[0].attribute_vector.at(i);
		// j iterates over rows (or examples) to find the mininum and maximum value of i-th attribute in the dataset
		for (int j=0; j < dataset.size(); j ++){
			if (dataset.at(j).attribute_vector.at(i) > max)
				max = dataset.at(j).attribute_vector.at(i);
			else if(dataset.at(j).attribute_vector.at(i) < min)
				min = dataset.at(j).attribute_vector.at(i);
		}
		float diff = max - min;
		// j iterates over rows (or examples) this time to scale the values
		for (int j=0; j< dataset.size(); j++){
			dataset.at(j).attribute_vector.at(i) -= min;
			dataset.at(j).attribute_vector.at(i) /= diff;
		}
	}

	create_term(0, parent_term, r);

	/*
	for (long i =0; i<polynomial_terms.size(); i ++){
		for (short j=0; j < polynomial_terms.at(i).size(); j++){
			printf("%d ", polynomial_terms.at(i).at(j));
		}
		printf("\n");
	}
	*/
}

PolynomialClassifier::PolynomialClassifier(std::string training_set_file_path, std::string dataset_file_path, uint8_t r):r(r){
	std::ifstream fin(training_set_file_path);
	// Read the first line (csv header) which contains attribute names
	std::string line, element;
	getline(fin, line);
	std::stringstream ss(line);
	uint8_t n = 0;
	while (getline(ss, element, ',')){
		attribute_names.push_back(element);
		// For each element increment n
		n++;
	}
	// Because we don't want to include 'label' in the attribute vector, decrement n
	n --;
	fin.close();
	training_set = csv_reader(training_set_file_path, n);
	dataset = csv_reader(dataset_file_path, n);
	/*
	for (int i =0; i < dataset.size(); i++){
		for (int j =0; j < dataset[i].attribute_vector.size(); j++){
			printf("%f ", dataset[i].attribute_vector[j]);
		}
		printf("\n");
	}
	*/
	init(n, r);
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

std::vector<example> PolynomialClassifier::csv_reader(std::string file_path, int n){
	std::vector<example> output;
	// Open the file using the given file path
	std::ifstream fin(file_path);
	// Create a string that holds the lines of our csv file
	std::string line, element;
	std::vector<float> attributes;
	// Read the header line so the pointer moves past it. We don't want anything to do with it in this function
	getline(fin,line);
	if (fin.is_open()){
		// For each example read the line 
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
			output.push_back(e);
		}
	}
	else printf("Error: Could not open file\n");
	fin.close();
	return output;
}

void PolynomialClassifier::perceptron(float learning_rate, float err_tresh){
	// Initialize coefficients
	coeffs.assign(polynomial_terms.size(), 0.1);
	unsigned int errors = 0;
	float error_rate;
	std::vector<int> nonzero_terms;
	float c = 0;
	do{
		errors = 0;
		// Iterate through all examples in the training_set
		for (int example_index =0; example_index < training_set.size(); example_index++){
			// Keep the example's attribute vector
			std::vector<float> atts = training_set.at(example_index).attribute_vector;
			// We keep the nonzero terms because we only change the coefficient for those terms in perceptron learning
			nonzero_terms.clear();
			// c variable holds the classifiers evaluation of the current example
			c = 0;
			// Iterate through all polynomial terms
			for(long term_index =0; term_index < polynomial_terms.size(); term_index++){
				// Get the coefficient for the current term
				float term_result = coeffs.at(term_index);
				// Iterate through the term to calculate the term result
				for(short i = 0; i < polynomial_terms[term_index].size(); i +=2)
					term_result *= pow(atts.at(polynomial_terms[term_index].at(i)), polynomial_terms[term_index].at(i+1));
				if (term_result != 0.0000){
					nonzero_terms.push_back(term_index);
					c += term_result;
				}
			}
			if (c >0 && training_set.at(example_index).label=="-"){
				for (int i =0; i <nonzero_terms.size(); i++)
					coeffs[nonzero_terms.at(i)] -= learning_rate;
				errors ++;
			}
			else if(c<0 && training_set.at(example_index).label=="+"){
				for (int i =0; i <nonzero_terms.size(); i++)
					coeffs[nonzero_terms.at(i)] += learning_rate;
				errors ++;
			}
		}
		error_rate = float(errors)/float(training_set.size());
	}while (error_rate > err_tresh);
}

void PolynomialClassifier::label_examples(){
	float c=0;
	for (int example_index=0; example_index < dataset.size(); example_index++){
		std::vector<float> atts = training_set.at(example_index).attribute_vector;
		// This is the result of the polynomial for the example
		c = 0;
		for(long term_index=0; term_index < polynomial_terms.size(); term_index++){
			float term_result = coeffs.at(term_index);
			for(short i =0; i < polynomial_terms.at(term_index).size(); i +=2)
				term_result *= pow(atts.at(polynomial_terms.at(term_index).at(i)), polynomial_terms.at(term_index).at(i+1));
			c+= term_result;
		}
		if(c >=0)
			dataset.at(example_index).label = "+";
		else dataset.at(example_index).label = "-";
	}
}
