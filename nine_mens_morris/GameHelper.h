#pragma once
#ifndef GAMEHELPER_H
#define GAMEHELPER_H
#include <string>
#include "Constants.h"
#include "Game.h"

class GameHelper {
public:
	static FieldName getFieldInput();
	static void printInfoBeforeUserMove(Game& game);
	static void placePieceOnBoard(Game& game, FieldName fName);

};

#endif