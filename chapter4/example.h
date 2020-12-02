#ifndef __example_h__
#define __example_h__
#include<vector>
#include<string>
class example{
	private:
		std::vector<int> attribute_vector;
		std::string label;
	public:
		// Each attribute has an ID that is specified by its index in the attribute vector
		inline example(std::vector<int> attribute_vector):attribute_vector(attribute_vector){}
};
#endif
