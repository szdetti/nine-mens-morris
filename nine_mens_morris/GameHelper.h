#pragma once
#ifndef GAMEHELPER_H
#define GAMEHELPER_H
#include <string>
#include <vector>
#include "Constants.h"
#include "Game.h"

class GameHelper {
public:
	static FieldName getFieldInput();
	static void printGameRules();
	static std::vector<std::string> getPlayerNames();
	static void printPlayerTurnBanner(Game& game);
	static void printInfoBeforePlayerMove_phase1(Game& game);
	static void printInfoBeforePlayerMove_phase2(Game& game);
	static FieldName validateAddPiece(Game& game);
	static void placePieceOnBoard(Game& game, FieldName fn);
	static bool handleAddPiece(Game& game);
	static void printMillPlayerInfo(Game& game);
	static bool pieceRemovable(Game& game, std::shared_ptr<Piece> p);
	static FieldName validateRemovePiece(Game& game, Player& player);
	static void handleRemovePiece(Game& game, Player& player);
	static void handleNewMill(Game& game);
	static bool handleMovePiece(Game& game);
	static void printInfoTable(Game& game);
	static bool canBothPlayersMove(Game& game);
};

#endif