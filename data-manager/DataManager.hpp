#ifndef __DataManager_h__
#define __DataManager_h__

#include<iostream>
#include<map>
#include <utility>
#include<vector>
#include<string>
#include<csv.hpp>

template <class type>
class example{
public:
    std::string label;
    std::vector<type> attributes;
};

template <class type>
class DataManager{
public:
    // python-like negative indexing works for label_col
    explicit DataManager(const std::string& file_path, int label_col, bool has_header = true);
    explicit DataManager(const std::string& file_path, bool has_header = true): DataManager(file_path, -1, has_header){}
    std::vector<example<type>*> getListExamples();
    std::map<std::string, std::vector<example<type>*>> getGroupedExamples();
    std::map<std::string, std::vector<example<type>*>> getGroupedExamples(std::vector<example<type>*>& example_list);
    size_t examples_num = 0;
private:
    bool has_header;
    std::string file_path;
    int label_column;
};

template <typename type>
DataManager<type>:: DataManager(const std::string& file_path, int label_col, bool has_header):file_path(file_path), has_header(has_header){
    // Create a CSVStat object just for the purpose of reading the number of columns and calculating label_column
    // TODO find out if csv library really doesn't have the seekg(0) or rewind() ability
    csv::CSVStat stat(file_path);
    label_column = (label_col + stat.get_col_names().size()) % stat.get_col_names().size();
}

template <typename type>
std::vector<example<type>*> DataManager<type>::getListExamples() {
    csv::CSVFormat format;
    std::vector<example<type>*> result;
    if (!has_header)
        format.no_header();
    csv::CSVReader reader(file_path, format);
    for(csv::CSVRow& row : reader){
        auto* ex = new example<type>();
        for(csv::CSVField& field: row){
            std::string str = field.get<type>();
            ex->attributes.push_back(str);
        }
        ex->label = ex->attributes.at(label_column);
        ex->attributes.erase(ex->attributes.begin()+label_column);
        result.push_back(ex);
    }
    examples_num = result.size();
    return result;
}

template <typename type>
std::map<std::string, std::vector<example<type>*>> DataManager<type>::getGroupedExamples() {
    csv::CSVFormat format;
    std::map<std::string, std::vector<example<type>*>> result;
    if (!has_header)
        format.no_header();
    csv::CSVReader reader(file_path, format);
    for(csv::CSVRow& row:reader){
        auto* ex = new example<type>();
        for(csv::CSVField& field: row){
            std::string str = field.get<type>();
            ex ->attributes.push_back(str);
        }
        std::string label = ex->attributes.at(label_column);
        ex->label = label;
        ex->attributes.erase(ex->attributes.begin()+label_column);
        if(result.find(label) == result.end())
            result[label] = std::vector<example<type>*>();
        result[label].push_back(ex);
        examples_num ++;
    }
    return result;
}

template <typename type>
std::map<std::string, std::vector<example<type>*>> DataManager<type>::getGroupedExamples(std::vector<example<type>*> &example_list) {
    std::map<std::string, std::vector<example<type>*>> result;
    for(auto* ex : example_list){
        if(result.find(ex->label) == result.end())
            result[ex->label] = std::vector<example<type>*>();
        result[ex->label].push_back(ex);
    }
    examples_num = example_list.size();
    return result;
}

#endif