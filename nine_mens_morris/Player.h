#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory> 
#include "Piece.h"

class Player {
private:
    std::string name;
    Colour colour;
    std::vector<std::shared_ptr<Piece>> initialPieces; 
    std::vector<std::shared_ptr<Piece>> piecesOnBoard;  
    std::vector<std::shared_ptr<Piece>> capturedPieces;  

public:
   // Player();
    Player(std::string name, Colour colour);

    void setName(std::string& newName);
    std::string& getName();
    void setColour(Colour newColour);
    Colour getColour();
    void setInitialPieces(std::vector<std::shared_ptr<Piece>> newInitialPieces);
    std::vector<std::shared_ptr<Piece>>& getInitialPieces();
    void setPiecesOnBoard(std::vector<std::shared_ptr<Piece>> newPiecesOnBoard);
    std::vector<std::shared_ptr<Piece>>& getPiecesOnBoard();
    void setCapturedPieces(std::vector<std::shared_ptr<Piece>> newCapturedPieces);
    std::vector<std::shared_ptr<Piece>>& getCapturedPieces();

    void createInitialPieces(Colour colour);
    bool allPiecesInMill();
    ~Player();
};

#endif
