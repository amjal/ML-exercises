#ifndef __PolynomialClassifier_h__
#define __PolynomialClassifier_h__
#include<vector>
#include<stdint.h>
#include<string>
#include "example.h"
class PolynomialClassifier{
	public:
		// These are the labeled examples in the training set which we use to train the classifer
		std::vector<example> training_set;
		// These are the new unlabeled examples that we give our classifier to label
		std::vector<example> dataset; 
		// This holds the attribute names includes the label column
		std::vector<std::string> attribute_names;
		// This is the polynomial order
		uint8_t r;
		// This is the number of attributes of each example
		uint8_t n;
		// These are the terms of the polynomial used to classify examples. Eeach term is a vector that holds 
		// the index and the power of the corresponding attribute. 
		std::vector<std::vector<uint8_t>> polynomial_terms;
		// This vector holds the coefficient for each of the polynomial terms
		std::vector<float> coeffs;
		// The two constructors of the class
		PolynomialClassifier(std::vector<example> training_set, uint8_t n, uint8_t r);
		PolynomialClassifier(std::string training_set_file_path, std::string dataset_file_path, uint8_t r);
		// This member function produces all possible terms in a r-th order n-variable polynomial recursively
		void create_term(uint8_t variable_num, std::vector<uint8_t> parent_term, uint8_t k);
		// This member function gets the path to the csv file containig example data and puts it in a vector
		// n is the number of attributes of each example
		std::vector<example> csv_reader(std::string file_path, int n);
		// This member function trains the classifier based on perceptron algorithm and fills the coefficients vector
		void perceptron(float learning_rate, float err_tresh);
};
#endif
