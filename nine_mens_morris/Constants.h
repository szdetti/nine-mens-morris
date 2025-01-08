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
to enforce the order in which they need to be printed to the console. The None value is 
used as a return value from functions that check for a valid FieldName */
enum class FieldName {
    A1 = 0,
    D1 = 1,
    G1 = 2,
    B2 = 3,
    D2 = 4,
    F2 = 5,
    C3 = 6,
    D3 = 7,
    E3 = 8,
    A4 = 9,
    B4 = 10,
    C4 = 11,
    E4 = 12,
    F4 = 13,
    G4 = 14,
    C5 = 15,
    D5 = 16,
    E5 = 17,
    B6 = 18,
    D6 = 19,
    F6 = 20,
    A7 = 21,
    D7 = 22,
    G7 = 23,
    None = 24
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