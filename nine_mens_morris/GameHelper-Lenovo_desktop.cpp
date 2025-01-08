#include<iostream>
#include "GameHelper.h"
#include "Constants.h"
#include "Game.h"

FieldName GameHelper::getFieldInput() {
	bool validField = false;
	std::string selectedField;
	FieldName f;
	while (!validField) {
		std::cout << "Please select a field: ";
		std::cin >> selectedField;
		selectedField[0] = std::toupper(static_cast<unsigned char>(selectedField[0]));
		try {
			f = findFieldNameByString(selectedField);
			validField = true;
		}
		catch (std::invalid_argument e) {
			std::cout << "Invalid field name, please try again" << std::endl;
		}
	}
	return f;
}
void GameHelper::printPlayerTurnBanner(Game& game) {
	std::string playerName = game.getCurrentPlayer()->getName();
	int star = 44;
	int space = star - 12 - playerName.length();
	if (space < 0) {
		star += -1 * space + 4;
		space = 4;
	}
	int space1, space2;
	if (space % 2 == 0) {
		space1 = space / 2;
		space2 = space1;
	}
	else {
		space1 = space / 2;
		space2 = space1 + 1;
	}
	std::cout << getCodeFromColour(game.getCurrentPlayer()->getColour()) << "*";
	for (int i = 0; i < star; i++)
	{
		std::cout << "*";
	}
	std::cout << "*" << std::endl;
	std::cout << "*";
	for (int i = 0; i < space1; i++)
	{
		std::cout << " ";
	}
	std::cout << "It's " << playerName << "'s Turn";
	for (int i = 0; i < space2; i++)
	{
		std::cout << " ";
	}
	std::cout << "*" << std::endl;
	std::cout << "*";
	for (int i = 0; i < star; i++)
	{
		std::cout << "*";
	}
	std::cout << "*" << getCodeFromColour(Colour::reset) << std::endl;
}
void GameHelper::printInfoBeforePlayerMove(Game& game) {
	printPlayerTurnBanner(game);
	game.printPlayerInitialPieces();
	std::cout << std::endl;
	game.getBoard().display();
}

void GameHelper::placePieceOnBoard(Game& game, FieldName fName) {
	game.addPiece(fName);
	game.getBoard().display();
	std::cout << std::endl;
	game.printInfoTable();
	std::cout << std::endl;
}
void GameHelper::printMillUserInfo(Game& game) {
	std::string currentPlayerName = game.getCurrentPlayer()->getName();
	std::string otherPlayerName = game.getOtherPlayer()->getName();
	std::cout << currentPlayerName << " created a mill. " << std::endl;
	std::cout << currentPlayerName << " has to select a field to take  one of " << otherPlayerName << "'s pieces off the board." << std::endl;
}
void GameHelper::handleNewMill(Game& game) {
	printMillUserInfo(game);
	FieldName fn;
	bool fieldEmpty1 = true;
	std::shared_ptr<Piece> p = nullptr;
	bool isRemovable = false;
	while (fieldEmpty1 || p == nullptr || !isRemovable) {
		fn = GameHelper::getFieldInput();
		fieldEmpty1 = game.checkFieldEmpty(fn);
		if (fieldEmpty1) {
			std::cout << "The selected field does not have a piece on it. Please select a field that contains a piece of the other player." << std::endl;
		}
		else {
			p = game.correctPlayerPiece(fn);
			if (p == nullptr) {
				std::cout << "Please select a field that contains a piece of the other player to remove it." << std::endl;
			}
			else {
				isRemovable = game.pieceRemovable(p);
				if (!isRemovable) {
					std::cout << "Only pieces that are not in a mill can be removed, unless all pieces are in a mill. Please select a different field." << std::endl;
				}
			}
		}
	}
	game.removePiece(fn);
}