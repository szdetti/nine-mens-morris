#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <vector> 
#include <string>
#include <unordered_map>

/************** COLOURS ***************/
enum class Colour { red, blue, reset };
extern const std::unordered_map<Colour, std::string> ColourMap;
std::string getCodeFromColour(Colour colour);
bool matchColour(std::string colourToMatch);


/***************** FIELD NAMES ********************/

/* Although tradiditonal enums implicitly convert to integers, enum class members do not.
In this case values were declared explicitly to enforce the order in fields assiociated 
with the FieldNames need to be printed to the console. The None value is 
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

extern const std::unordered_map<std::string, FieldName> stringToFieldNameMap;
extern const std::vector<FieldName> FieldNames;
FieldName findFieldNameByString(std::string fieldNameString);
extern const std::unordered_map<FieldName, std::vector<FieldName>> neighboursMap;


/******************** OTHER **********************/

extern const int piecesPerPlayer;
extern const std::string defaultName;
extern const std::string instructions;
void printBasicBoard();

enum class GamePhase {
    phase1,
    phase2
};

#endif