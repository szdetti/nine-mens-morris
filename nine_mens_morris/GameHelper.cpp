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

void GameHelper::printInfoBeforeUserMove(Game& game) {
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
	std::cout<<"*" << std::endl;
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