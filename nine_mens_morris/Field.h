#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <memory>  
#include "Piece.h"
#include "Constants.h"

class Field {
    FieldName name;
    std::shared_ptr<Piece> piece;  

public:
    Field(FieldName name);
    void setName(FieldName name);
    FieldName getName();
    void setPiece(std::shared_ptr<Piece> newPiece);  
    std::shared_ptr<Piece> getPiece();  
    ~Field();
};

#endif
