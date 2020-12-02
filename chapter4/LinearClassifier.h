#ifndef __LinearClassifier_h__
#define __LinearClassifier_h__
class example;
class LinearClassifier{
	private:
		// These are the labeled examples in the training set which we use to train the classifer
		std::vector<example*> training_set;
		// These are the new unlabeled examples that we give our classifier to label
		std::vector<example*> dataset; 
		// This is the polynomial order
		uint8_t r;
		// This is the number of attributes of each example
		uint8_t n;
		// These are the terms of the polynomial classifer
		std::vector<int*
	public:
		inline LinearClassifer(std::vector<example*> training_set):training_set(training_set){}

#endif
