#include <memory>
#include "Field.h"
#include "Constants.h"
#include <iostream>

Field::Field(FieldName name) : name(name), piece(std::make_shared<Piece>()) {}

void Field::setName(FieldName newName) {
    name = newName;
}

FieldName Field::getName() {
    return name;
}

void Field::setPiece(std::shared_ptr<Piece> newPiece) {
    piece = newPiece;  
   
}

std::shared_ptr<Piece> Field::getPiece() {
    return piece;
}

Field::~Field() {}