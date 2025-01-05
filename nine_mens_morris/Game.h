#pragma once
#ifndef GAME_H
#define GAME_H
#include <string>
#include "Board.h"
#include "Player.h"

class Game {
private:
    Board& board;
    Player player1;
    Player player2;
    Player* currentPlayer;


public:
    Game(Player player1, Player player2);
    Board& getBoard();
    void setPlayer1(Player newPlayer1);
    Player& getPlayer1();
    void setPlayer2(Player newPlayer2);
    Player& getPlayer2();
    void setCurrentPlayer(Player player);
    Player* getCurrentPlayer();
    Player* getOtherPlayer();
    bool checkMillsByFieldName(FieldName fieldName);
    bool checkFieldsByVector(std::vector<std::vector<FieldName>>& fieldNames, int index);
    bool checkMatchingFields(std::vector<FieldName>& fieldNames, int index);
    bool checkFieldEmpty(FieldName fieldName);
    void addPiece(std::string fieldNameString);
    void removePiece(std::string fieldNameString);
    void movePiece(std::string fromFieldNameString, std::string toFieldNameString);
    void printInfoTable();
    ~Game();

};

#endif