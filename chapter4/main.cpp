#include<stdio.h>
#include "PolynomialClassifier.h"
#include<vector>
int main(){
	PolynomialClassifier classifier("labeled.csv", "unlabeled.csv", 2);
	return 0;
}
