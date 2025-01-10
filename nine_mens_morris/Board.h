#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <vector>
#include <string>
#include <memory>
#include "constants.h"
#include "field.h"

class Board {
private:
     std::map<FieldName, std::vector<std::vector<FieldName>>> fieldNamesByMills;
     std::vector<std::shared_ptr<Field>> fieldsToPrint;
     std::vector<std::shared_ptr<Field>> emptyFields;
     std::map<FieldName, std::shared_ptr<Field>> fieldsMap;
     void initFieldNamesByMills();
     void initFields();

public:
    Board();
    void setFieldNamesByMills(std::map<FieldName, std::vector<std::vector<FieldName>>>& newFieldNamesByMills);
    std::map<FieldName, std::vector<std::vector<FieldName>>>& getFieldNamesByMills();
    void setFieldsToPrint(std::vector<std::shared_ptr<Field>>& newFieldsToPrint);
    std::vector<std::shared_ptr<Field>>& getFieldsToPrint();
    void setEmptyFields(std::vector<std::shared_ptr<Field>>& newEmptyFields);
    std::vector<std::shared_ptr<Field>>& getEmptyFields();
    void setFieldsMap(std::map<FieldName, std::shared_ptr<Field>>& newFieldsMap);
    std::map<FieldName, std::shared_ptr<Field>>& getFieldsMap();
    void display();
    ~Board();
};

#endif
