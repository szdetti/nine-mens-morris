#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <vector> 
#include <string>
#include <map>

/************** COLOURS ***************/
enum class Colour { red, blue, reset };
extern const std::map<Colour, std::string> ColourMap;
std::string getCodeFromColour(Colour colour);
bool matchColour(std::string colourToMatch);


/***************** FIELD NAMES ********************/

/* Although enums are automatically assigned an int value, they were declared explicitly
to enforce the order in which they need to be printed to the console */
enum class FieldName {
    A1 = 1,
    D1 = 2,
    G1 = 3,
    B2 = 4,
    D2 = 5,
    F2 = 6,
    C3 = 7,
    D3 = 8,
    E3 = 9,
    A4 = 10,
    B4 = 11,
    C4 = 12,
    E4 = 13,
    F4 = 14,
    G4 = 15,
    C5 = 16,
    D5 = 17,
    E5 = 18,
    B6 = 19,
    D6 = 20,
    F6 = 21,
    A7 = 22,
    D7 = 23,
    G7 = 24
};

extern const std::map<std::string, FieldName> stringToFieldNameMap;
extern const std::vector<FieldName> FieldNames;
FieldName findFieldNameByString(std::string fieldNameString);


/******************** OTHER **********************/

extern const int piecesPerPlayer;
extern const std::string defaultName;
extern const std::string instructions;
void printBasicBoard();


#endif