#include<iostream>
#include "GameHelper.h"
#include "Constants.h"
#include "Game.h"

FieldName GameHelper::getFieldInput() {
	std::string selectedField;
	FieldName f = FieldName::None;
	std::cout << "Please select a field: ";
	std::cin >> selectedField;
	selectedField[0] = std::toupper(static_cast<unsigned char>(selectedField[0]));
	try {
		f = findFieldNameByString(selectedField);
	}
	catch (std::invalid_argument e) {
		std::cout << "Invalid field name." << std::endl;
	}
	
	return f;
}
void GameHelper::printGameRules() {
	std::cout << "***************************" << std::endl;
	std::cout << "*     About The Game      *" << std::endl;
	std::cout << "***************************" << std::endl;
	std::cout << instructions << std::endl;
	std::cout << std::endl;
	printBasicBoard();

}

std::vector<std::string> GameHelper::getPlayerNames() {
	std::string name1, name2;
	std::cin.ignore();
	std::cout << "Type in a name for Player 1: ";
	std::getline(std::cin, name1);
	std::cout << "Type in a name for Player 2: ";
	std::getline(std::cin, name2);
	std::cout << std::endl;

	std::vector<std::string> names = { name1, name2 };
	return names;
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
void GameHelper::printInfoBeforePlayerMove_phase1(Game& game) {
	printPlayerTurnBanner(game);
	std::cout << std::endl;
	game.printPlayerInitialPieces();
	std::cout << std::endl;
	game.getBoard().display();
	std::cout << std::endl;
}

void GameHelper::printInfoBeforePlayerMove_phase2(Game& game) {
	printPlayerTurnBanner(game);
	std::cout << std::endl;
	game.getBoard().display();
	std::cout << std::endl;

}


FieldName GameHelper::validateAddPiece(Game& game) {
	FieldName fn = getFieldInput();
	if (fn == FieldName::None) {
		std::cout << "Please enter a valid field name." << std::endl;
	} else if (!game.checkFieldEmpty(fn)) {
		std::cout << "The selected field already has a piece on it. Please select an empty field." << std::endl;
		fn = FieldName::None;
	}
	
	return fn;
} 

void GameHelper::placePieceOnBoard(Game& game, FieldName fn) {
	game.addPiece(fn);
	game.getBoard().display();
	std::cout << std::endl;
	printInfoTable(game);
	std::cout << std::endl;
}

bool GameHelper::handleAddPiece(Game& game){
	FieldName fn = FieldName::None;
	while (fn == FieldName::None) {
		fn = validateAddPiece(game);
	}
	placePieceOnBoard(game, fn);

	return game.checkMillsByFieldName(fn);
}

void GameHelper::printMillPlayerInfo(Game& game) {
	std::string currentPlayerName = game.getCurrentPlayer()->getName();
	std::string otherPlayerName = game.getOtherPlayer()->getName();
	std::cout << currentPlayerName << " created a mill. " << std::endl;
	std::cout << currentPlayerName << " has to select a field to take  one of " << otherPlayerName << "'s pieces off the board." << std::endl;
}
bool GameHelper::pieceRemovable(Game& game, std::shared_ptr<Piece> p) {
	if (p == nullptr) {
		return false;
	}
	else {
		Player* other = game.getOtherPlayer();
		if (!p->isInMill() || other->allPiecesInMill()) {
			return true;
		}
	}
	return false;
}

FieldName GameHelper::validateRemovePiece(Game& game, Player& player){
	FieldName fn = GameHelper::getFieldInput();
	if (fn == FieldName::None) {
		std::cout << "Please select a valid field Name." << std::endl;
	} else {
		if (game.checkFieldEmpty(fn)) {
			std::cout << "The selected field does not have a piece on it. Please select a field that contains "<< player.getName() <<"'s piece." << std::endl;
			fn = FieldName::None;
		}
		else {
			std::shared_ptr<Piece> p = game.correctPlayerPiece(fn, player);
			if (p == nullptr) {
				std::cout << "Please select a field that contains " << player.getName() << "'s piece." << std::endl;
				fn = FieldName::None;
			}
			else {
				if (!pieceRemovable(game, p)) {
					std::cout << "Only pieces that are not in a mill can be removed, unless all pieces are in a mill. Please select a different field." << std::endl;
					fn = FieldName::None;
				}
			}
		}
	}
	return fn;
}

void GameHelper::handleRemovePiece(Game& game, Player& player) {
	FieldName fn = FieldName::None;
	while (fn == FieldName::None) {
		fn = validateRemovePiece(game, player);
	}
	game.removePiece(fn);
}

void GameHelper::handleNewMill(Game& game) {
	printMillPlayerInfo(game);
	handleRemovePiece(game, *game.getOtherPlayer());
	std::cout << std::endl;
	game.getBoard().display();
	std::cout << std::endl;
	printInfoTable(game);
	std::cout << std::endl;
}

bool GameHelper::handleMovePiece(Game& game) {
	std::cout << "First, select the field to move from." << std::endl;
	FieldName fromFn = FieldName::None;
	while (fromFn == FieldName::None) {
		fromFn = validateRemovePiece(game, *game.getCurrentPlayer());
	}

	std::cout << "Now choose an empty field to move to." << std::endl;
	FieldName toFn = FieldName::None;
	while (toFn == FieldName::None) {
		toFn = validateAddPiece(game);
	}

	game.movePiece(fromFn, toFn);
	game.getBoard().display();
	std::cout << std::endl;
	printInfoTable(game);
	std::cout << std::endl;

	return game.checkMillsByFieldName(toFn);
}


/* Print the pieces of each player that are on the board and captured from the other player to visualise game status. */
void GameHelper::printInfoTable(Game& game) {

	/************* player1 name ******************/

	std::cout << "                     +--------------------+--------------------+" << std::endl;
	std::cout << "                     + " << game.getPlayer1().getName();
	int space1 = 19 - game.getPlayer1().getName().length();
	for (int i = 0; i < space1; i++) {
		std::cout << " ";
	}

	/**************** player2 name ******************/

	std::cout << "+ " << game.getPlayer2().getName();
	int space2 = 19 - game.getPlayer2().getName().length();
	for (int i = 0; i < space2; i++) {
		std::cout << " ";
	}
	std::cout << "+" << std::endl;
	std::cout << "+--------------------+--------------------+--------------------+" << std::endl;
	std::cout << "+  pieces on board   + ";

	/***************** player1 pieces on board ******************/

	for (auto p : game.getPlayer1().getPiecesOnBoard()) {
		p->display();
		std::cout << " ";
	}
	int space3 = 19 - game.getPlayer1().getPiecesOnBoard().size() * 2;
	for (int i = 0; i < space3; i++) {
		std::cout << " ";
	}

	/**************** player2 pieces on board ******************/

	std::cout << "+ ";
	for (auto p : game.getPlayer2().getPiecesOnBoard()) {
		p->display();
		std::cout << " ";
	}
	int space4 = 19 - game.getPlayer2().getPiecesOnBoard().size() * 2;
	for (int i = 0; i < space4; i++) {
		std::cout << " ";
	}
	std::cout << "+" << std::endl;
	std::cout << "+--------------------+--------------------+--------------------+" << std::endl;
	/**************** player1 captured pieces ******************/

	std::cout << "+  captured pieces   + ";
	for (auto p : game.getPlayer1().getCapturedPieces()) {
		p->display();
		std::cout << " ";
	}
	int space5 = 19 - game.getPlayer1().getCapturedPieces().size() * 2;
	for (int i = 0; i < space5; i++) {
		std::cout << " ";
	}

	/***************** player2 captured pieces ******************/

	std::cout << "+ ";
	for (auto p : game.getPlayer2().getCapturedPieces()) {
		p->display();
		std::cout << " ";
	}
	int space6 = 19 - game.getPlayer2().getCapturedPieces().size() * 2;
	for (int i = 0; i < space6; i++) {
		std::cout << " ";
	}
	std::cout << "+" << std::endl;
	std::cout << "+--------------------+--------------------+--------------------+" << std::endl;
}

bool GameHelper::canBothPlayersMove(Game& game) {
	std::vector<std::shared_ptr<Field>> emptyFields = game.getBoard().getEmptyFields();
	for (auto f : emptyFields) {
		f->getPiece()->getColour();
	}

	return false;
}