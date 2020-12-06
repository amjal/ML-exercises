#ifndef __example_h__
#define __example_h__
#include<vector>
#include<string>
class example{
	public:
		std::vector<float> attribute_vector;
		std::string label;
		// Each attribute has an ID that is specified by its index in the attribute vector
		inline example(std::vector<float> attribute_vector):attribute_vector(attribute_vector){}
};
#endif
