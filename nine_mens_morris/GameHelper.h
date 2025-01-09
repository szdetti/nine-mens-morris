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
	static void printPlayerInitialPieces(Game& game);
	static void printInfoBeforePlayerMove(Game& game, GamePhase phase);
	static FieldName validateAddPiece(Game& game, FieldName fromFn = FieldName::None);
	static void placePieceOnBoard(Game& game, FieldName fn);
	static bool handleAddPiece(Game& game);
	static void printMillPlayerInfo(Game& game);
	static bool pieceRemovable(Game& game, std::shared_ptr<Piece> p);
	static FieldName validateRemovePiece(Game& game, Player& player, bool removeAfterMill =  false);
	static void handleRemovePiece(Game& game, Player& player, bool removeAfterMill = false);
	static void handleNewMill(Game& game);
	static bool handleMovePiece(Game& game);
	static void printInfoTable(Game& game);
	static std::vector<Player*> canBothPlayersMove(Game& game);
	static bool isMoveToNeighbour(FieldName fromFn, FieldName toFn);
	static bool checkPlayersHavePieces(Game& game);
	static void determineWinner(Game& game, std::vector<Player*> players);
};

#endif