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
    static Board* instance; // Singleton instance as a static reference
    static std::map<FieldName, std::vector<std::vector<FieldName>>> fieldNamesByMills;
    static std::vector<std::shared_ptr<Field>> fields;
    static std::map<FieldName, std::shared_ptr<Field>> fieldsMap;

    Board();

public:
    // Delete copy constructor and assignment to enforce singleton
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    static Board& getInstance();

    static void initFieldNamesByMills();
    static void initFields();
    std::map<FieldName, std::vector<std::vector<FieldName>>> getFieldNamesByMills();
    std::vector<std::shared_ptr<Field>> getFields();
    std::map<FieldName, std::shared_ptr<Field>> getFieldsMap();
    void display();
    ~Board();
};

#endif
