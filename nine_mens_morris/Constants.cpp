#include <string>
#include <map>
#include <vector>
#include "Constants.h"
#include <stdexcept>
#include <iostream>

/************** COLOURS ***************/

const std::map<Colour, std::string> ColourMap =
{
    {Colour::red, "\033[31m"},
    {Colour::blue, "\033[34m"},
    {Colour::reset, "\033[0m"}
};

std::string getCodeFromColour(Colour colour)
{

    return ColourMap.at(colour);
}

bool matchColour(std::string colourToMatch)
{
    for (const auto pair : ColourMap) {
        if (pair.second == colourToMatch) {
            return true;
        }
    }

    return false;
}

/***************** FIELD NAMES ********************/

const std::map<std::string, FieldName> stringToFieldNameMap =
{
{"A1", FieldName::A1}, {"D1", FieldName::D1}, {"G1", FieldName::G1},
{"B2", FieldName::B2}, {"D2", FieldName::D2}, {"F2", FieldName::F2},
{"C3", FieldName::C3}, {"D3", FieldName::D3}, {"E3", FieldName::E3},
{"A4", FieldName::A4}, {"B4", FieldName::B4}, {"C4", FieldName::C4},
{"E4", FieldName::E4}, {"F4", FieldName::F4}, {"G4", FieldName::G4},
{"C5", FieldName::C5}, {"D5", FieldName::D5}, {"E5", FieldName::E5},
{"B6", FieldName::B6}, {"D6", FieldName::D6}, {"F6", FieldName::F6},
{"A7", FieldName::A7}, {"D7", FieldName::D7}, {"G7", FieldName::G7}
};

const std::vector<FieldName> FieldNames =
{
    FieldName::A1, FieldName::D1, FieldName::G1,
    FieldName::B2, FieldName::D2, FieldName::F2,
    FieldName::C3, FieldName::D3, FieldName::E3,
    FieldName::A4, FieldName::B4, FieldName::C4,
    FieldName::E4, FieldName::F4, FieldName::G4,
    FieldName::C5, FieldName::D5, FieldName::E5,
    FieldName::B6, FieldName::D6, FieldName::F6,
    FieldName::A7, FieldName::D7, FieldName::G7
};

FieldName findFieldNameByString(std::string fieldNameString) {
    auto it = stringToFieldNameMap.find(fieldNameString);
    if (it != stringToFieldNameMap.end()) {
        return it->second; 
    }
    throw std::invalid_argument("Field name not found");
}

const std::map<FieldName, std::vector<FieldName>> neighboursMap = {
    {FieldName::A1, {FieldName::A4, FieldName::D1}},
    {FieldName::D1, {FieldName::A1, FieldName::D2, FieldName::G1}},
    {FieldName::G1, {FieldName::D1, FieldName::G4}},
    {FieldName::B2, {FieldName::D2, FieldName::B4}},
    {FieldName::D2, {FieldName::B2, FieldName::F2, FieldName::D1, FieldName::D3}},
    {FieldName::F2, {FieldName::D2, FieldName::F4}},
    {FieldName::C3, {FieldName::C4, FieldName::D3}},
    {FieldName::D3, {FieldName::C3, FieldName::D2, FieldName::E3}},
    {FieldName::E3, {FieldName::D3, FieldName::E4}},
    {FieldName::A4, {FieldName::A1, FieldName::A7, FieldName::B4}},
    {FieldName::B4, {FieldName::A4, FieldName::C4, FieldName::B2, FieldName::B6}},
    {FieldName::C4, {FieldName::B4, FieldName::C3, FieldName::C5}},
    {FieldName::E4, {FieldName::E3, FieldName::E5, FieldName::F4}},
    {FieldName::F4, {FieldName::E4, FieldName::G4, FieldName::F2, FieldName::F6}},
    {FieldName::G4, {FieldName::G1, FieldName::G7, FieldName::F4}},
    {FieldName::C5, {FieldName::C4, FieldName::D5}},
    {FieldName::D5, {FieldName::C5, FieldName::E5, FieldName::D6}},
    {FieldName::E5, {FieldName::D5, FieldName::E4}},
    {FieldName::B6, {FieldName::B4, FieldName::D6}},
    {FieldName::D6, {FieldName::B6, FieldName::D5, FieldName::D7, FieldName::F6}},
    {FieldName::F6, {FieldName::D6, FieldName::F4}},
    {FieldName::A7, {FieldName::A4, FieldName::D7}},
    {FieldName::D7, {FieldName::A7, FieldName::G7, FieldName::D6}},
    {FieldName::G7, {FieldName::D7, FieldName::G4}},   
};





/******************** OTHER **********************/

const int piecesPerPlayer = 9;
const std::string defaultName = "default";
const std::string instructions = "Each player has 9 pieces to play with. In the first phase, players place their pieces on any empty field of the board, taking turns. In the second phase, players can move \
their pieces on the board between connected fields.If in any phase a player has three pieces on three adjacent fields horizontally or vertically(called a mill), that player can take one piece of the other \
player's off the board - but only of those that are not part of a mill, except when all the pieces are in a mill, in which case it is allowed to take off any one of them.The game ends when one player is \
reduced to two pieces or cannot make any moves.";

/* Used to print an example of the board when introducing the game to players */
void printBasicBoard() {
    std::cout << "   A    B    C      D      E   F     G" << std::endl;
    std::cout << "1  O----------------O----------------O" << std::endl;
    std::cout << "   |                |                |" << std::endl;
    std::cout << "2  |    O-----------O----------O     |" << std::endl;
    std::cout << "   |    |           |          |     |" << std::endl;
    std::cout << "3  |    |    O------O------O   |     |" << std::endl;
    std::cout << "   |    |    |             |   |     |" << std::endl;
    std::cout << "   |    |    |             |   |     |" << std::endl;
    std::cout << "4  O----O----O             O---O-----O" << std::endl;
    std::cout << "   |    |    |             |   |     |" << std::endl;
    std::cout << "   |    |    |             |   |     |" << std::endl;
    std::cout << "5  |    |    O------O------O   |     |" << std::endl;
    std::cout << "   |    |           |          |     |" << std::endl;
    std::cout << "6  |    O-----------O----------O     |" << std::endl;
    std::cout << "   |                |                |" << std::endl;
    std::cout << "7  O----------------O----------------O" << std::endl;
}
