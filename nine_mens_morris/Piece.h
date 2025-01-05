#pragma once
#ifndef PIECE_H
#define PIECE_H
#include <string>
#include "Constants.h"

class Piece {
    Colour colour;
    bool inMill;
public:
    static const std::string symbol;

    Piece();
    Piece(Colour colour);
    void setColour(Colour newColour);
    Colour getColour();
    void setInMill(bool isInMill);
    bool isInMill();
    void display();
    ~Piece();

};

#endif