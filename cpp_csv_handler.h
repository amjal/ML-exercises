#ifndef __cpp_csv_handler__
#define __cpp_csv_handler__

#include<fstream>
#include<string>
#include<vector>
#include<map>

struct example{
	std::string class_label;
	// the below map has the following structure: {attribute --> value}
	std::map<std::string, std::string> attribute_set;
};

class csvhandler{
	public:
		// The file stream
		std::ifstream csv_file;
		// The headers of the CSV file are kept here
		std::vector<std::string> headers;
		inline csvhandler(){}
		inline csvhandler(std::vector<std::string> headers):headers(headers){}
		// If the headers of the csv are not specified, this function sets att0, att1, ... as headers
		void headers_init();
		// This function returns a vector of all examples in the file
		std::vector<example> get_examples(std::string file_path);
		// This function returns vectors of examples in the file grouped by their label class, which is the key of this map
		std::map<std::string, std::vector<example>> get_grouped_examples(std::string file_path);
		std::map<std::string, std::vector<example>> get_grouped_examples(std::vector<example> example_vector);
};
#endif
