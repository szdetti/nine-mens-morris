#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include "constants.h"
#include "field.h"

class Board {
private:
     std::unordered_map<FieldName, std::vector<std::vector<FieldName>>> fieldNamesByMills;
     std::vector<std::shared_ptr<Field>> fieldsToPrint;
     std::vector<std::shared_ptr<Field>> emptyFields;
     std::unordered_map<FieldName, std::shared_ptr<Field>> fieldsMap;
     void initFieldNamesByMills();
     void initFields();

public:
    Board();
    void setFieldNamesByMills(std::unordered_map<FieldName, std::vector<std::vector<FieldName>>>& newFieldNamesByMills);
    std::unordered_map<FieldName, std::vector<std::vector<FieldName>>>& getFieldNamesByMills();
    void setFieldsToPrint(std::vector<std::shared_ptr<Field>>& newFieldsToPrint);
    std::vector<std::shared_ptr<Field>>& getFieldsToPrint();
    void setEmptyFields(std::vector<std::shared_ptr<Field>>& newEmptyFields);
    std::vector<std::shared_ptr<Field>>& getEmptyFields();
    void setFieldsMap(std::unordered_map<FieldName, std::shared_ptr<Field>>& newFieldsMap);
    std::unordered_map<FieldName, std::shared_ptr<Field>>& getFieldsMap();
    void display();
    ~Board();
};

#endif
