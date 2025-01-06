#include "Piece.h"
#include "Constants.h"
#include <iostream>

const std::string Piece::symbol = "O";

Piece::Piece() : colour(Colour::reset), inMill(false) {}
Piece::Piece(Colour colour) : colour(colour), inMill(false) {}

void Piece::setColour(Colour newColour) {
    colour = newColour;

}

Colour Piece::getColour() {
    return colour;
}

void Piece::setInMill(bool isInMill) {
    inMill = isInMill;
}

bool Piece::isInMill() {
    return inMill;
}

void Piece::display() {
   
    std::cout << getCodeFromColour(colour) << "O" << getCodeFromColour(Colour::reset);
}

Piece::~Piece() {}