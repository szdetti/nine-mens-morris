#pragma once
#ifndef GAME_H
#define GAME_H
#include <string>
#include <memory>
#include "Board.h"
#include "Player.h"

class Game {
private:
    Board& board;
    Player player1;
    Player player2;
    Player* currentPlayer;
    friend class GameHelper;

public:
    Game(std::string playerName1, std::string playerName2);
    Board& getBoard();
    void setPlayer1(Player& newPlayer1);
    Player& getPlayer1();
    void setPlayer2(Player& newPlayer2);
    Player& getPlayer2();
    void setCurrentPlayer(Player& player);
    Player* getCurrentPlayer();
    Player* getOtherPlayer();
    Player& getPlayerByColour(Colour colour);
    bool checkMillsByFieldName(FieldName fieldName);
    bool checkFieldsByVector(std::vector<std::vector<FieldName>>& fieldNames);
    bool checkMatchingFields(std::vector<FieldName>& fieldNames, int index);
    bool checkFieldEmpty(FieldName fieldName);
    std::shared_ptr<Piece> correctPlayerPiece(FieldName f, Player& player);
    void addPiece(FieldName fn);
    void removePiece(FieldName fn);
    void movePiece(FieldName fromFn, FieldName toFn);
    void printPlayerInitialPieces();
    ~Game();

};

#endif