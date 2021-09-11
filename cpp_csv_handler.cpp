#include "cpp_csv_handler.h"
#include<cstdio>
#include<iostream>

void csvhandler:: headers_init(){
	size_t pos;
	std::string line;
	std::getline(csv_file, line);
	for(int i=0; (pos = line.find(",")) != std::string::npos; i++){
		std::string new_header = std::string("att").append(std::to_string(i));
		headers.push_back(new_header);
		line.erase(0, pos+1);
	}
	csv_file.seekg(0);
}

std::vector<example> csvhandler::get_examples(std::string file_path){
	csv_file.open(file_path);
	std::string line;
	std::vector<example> result;
	size_t pos;
	std::string token;
	example temp;
	if(headers.size() == 0) headers_init();
	while(std::getline(csv_file, line)){
		for(int i =0;(pos =line.find(",")) != std::string::npos; i++){
			token = line.substr(0, pos);
			line.erase(0, pos +1);
			temp.attribute_set[headers[i]] = token;
		}
		temp.class_label = line;
		result.push_back(temp);
	}
	csv_file.close();
	return result;
}

std::map<std::string, std::vector<example>> csvhandler::get_grouped_examples(std::vector<example> example_vector){
	std::map<std::string, std::vector<example>> result;
	std::string cl;
	for(int i =0; i < example_vector.size(); i ++){
		cl = example_vector[i].class_label;
		if(result.find(cl) == result.end())
			result[cl] = std::vector<example>();
		result[cl].push_back(example_vector[i]);
	}
	return result;
}
std::map<std::string, std::vector<example>> csvhandler::get_grouped_examples(std::string file_path){
	return get_grouped_examples(get_examples(file_path));
}

		

