#ifndef __DataManager_h__
#define __DataManager_h__

#include<iostream>
#include<map>
#include <utility>
#include<vector>
#include<string>
#include<csv.hpp>

class example{
public:
    std::string label;
    std::vector<std::string> attributes;
};

class DataManager{
public:
    // python-like negative indexing works for label_col
    explicit DataManager(const std::string& file_path, int label_col, bool has_header = true);
    explicit DataManager(const std::string& file_path, bool has_header = true): DataManager(file_path, -1, has_header){}
    std::vector<example*> getListExamples();
    std::map<std::string, std::vector<example*>> getGroupedExamples();
    std::map<std::string, std::vector<example*>> getGroupedExamples(std::vector<example*>& example_list);
    size_t examples_num = 0;
private:
    bool has_header;
    std::string file_path;
    int label_column;
};

#endif