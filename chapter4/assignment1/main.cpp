#include<stdio.h>
#include "../PolynomialClassifier.h"
#include<vector>
int main(){
	PolynomialClassifier classifier("labeled.csv", "unlabeled.csv", 1);
	classifier.perceptron(0.3, 0.01);
	return 0;
}
