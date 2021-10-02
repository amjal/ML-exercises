#include "DataManager.h"
#include <iostream>

DataManager:: DataManager(const std::string& file_path, int label_col, bool has_header):file_path(file_path), has_header(has_header){
    // Create a CSVStat object just for the purpose of reading the number of columns and calculating label_column
    // TODO find out if csv library really doesn't have the seekg(0) or rewind() ability
    csv::CSVStat stat(file_path);
    label_column = (label_col + stat.get_col_names().size()) % stat.get_col_names().size();
}

std::vector<example*> DataManager::getListExamples() {
    csv::CSVFormat format;
    std::vector<example*> result;
    if (!has_header)
        format.no_header();
    csv::CSVReader reader(file_path, format);
    for(csv::CSVRow& row : reader){
        auto* ex = new example();
        for(csv::CSVField& field: row){
            std::string str = field.get<std::string>();
            ex->attributes.push_back(str);
        }
        ex->label = ex->attributes.at(label_column);
        ex->attributes.erase(ex->attributes.begin()+label_column);
        result.push_back(ex);
    }
    examples_num = result.size();
    return result;
}

std::map<std::string, std::vector<example*>> DataManager::getGroupedExamples() {
    csv::CSVFormat format;
    std::map<std::string, std::vector<example*>> result;
    if (!has_header)
        format.no_header();
    csv::CSVReader reader(file_path, format);
    for(csv::CSVRow& row:reader){
        auto* ex = new example();
        for(csv::CSVField& field: row){
            std::string str = field.get<std::string>();
            ex ->attributes.push_back(str);
        }
        std::string label = ex->attributes.at(label_column);
        ex->label = label;
        ex->attributes.erase(ex->attributes.begin()+label_column);
        if(result.find(label) == result.end())
                result[label] = std::vector<example*>();
        result[label].push_back(ex);
        examples_num ++;
    }
    return result;
}

std::map<std::string, std::vector<example*>> DataManager::getGroupedExamples(std::vector<example*> &example_list) {
    std::map<std::string, std::vector<example*>> result;
    for(auto* ex : example_list){
        if(result.find(ex->label) == result.end())
            result[ex->label] = std::vector<example*>();
        result[ex->label].push_back(ex);
    }
    examples_num = example_list.size();
    return result;
}