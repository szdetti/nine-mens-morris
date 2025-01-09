#include<iostream>
#include "GameHelper.h"
#include "Constants.h"
#include "Game.h"

/* Get player input to determine selected field. Transform first character to uppercase and attempt to 
retrieve a Field object based on the field name provided by the player. If it triggers an exception to 
be thrown, the player will be warned and the FieldName will remain FieldName::None.  */
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

/* Print instructions from the Constants file */
void GameHelper::printGameRules() {
	std::cout << "***************************" << std::endl;
	std::cout << "*     About The Game      *" << std::endl;
	std::cout << "***************************" << std::endl;
	std::cout << std::endl;
	std::cout << instructions << std::endl;
	std::cout << std::endl;
	printBasicBoard();

}/* Read two player names from user input into two variables and return them in a vector. */
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

/* Print a banner that has a border made of star symbols and displays which player's turn it is.
Whitespace between the banner's left and right borders and text is calculated based on the number
of characters of the displayed text, including the length of the player's name. */
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

/* Print both player's pieces yet to be placed on the board.  */
void GameHelper::printPlayerInitialPieces(Game& game) {
	if (game.getPlayer1().getInitialPieces().size() > 0) {
		std::cout << game.getPlayer1().getName() << "'s pieces to place on board: ";
		for (auto p : game.getPlayer1().getInitialPieces()) {
			p->display();
			std::cout << " ";
		}
	}
	std::cout << std::endl;
	if (game.getPlayer2().getInitialPieces().size() > 0) {
		std::cout << game.getPlayer2().getName() << "'s pieces to place on board: ";
		for (auto p : game.getPlayer2().getInitialPieces()) {
			p->display();
			std::cout << " ";
		}
	}
	std::cout << std::endl;	
}/* Display which player's turn it is, and in phase 1 of the game also print the players' pieces
 that are yet to be placed on the Board */
void GameHelper::printInfoBeforePlayerMove(Game& game, GamePhase phase) {
	printPlayerTurnBanner(game);
	std::cout << std::endl;
	if (phase == GamePhase::phase1) {
		printPlayerInitialPieces(game);
	}
	std::cout << std::endl;
}

/* Perform all necessary checks to ensure that: the selected field name is an existing field name, the selected field is empty and in case of the 
player moving their piece from one field to another, that the selected field they are moving to is a neighbour of the field they are moving from. */
FieldName GameHelper::validateAddPiece(Game& game, FieldName fromFn) {
	FieldName toFn = getFieldInput();
	if (toFn == FieldName::None) {
		std::cout << "Please enter a valid field name." << std::endl;
	} else if (!game.checkFieldEmpty(toFn)) {
		std::cout << "The selected field already has a piece on it. Please select an empty field." << std::endl;
		toFn = FieldName::None;
	} else if (fromFn != FieldName::None && !isMoveToNeighbour(fromFn, toFn)) {
		std::cout << "You can only move to a neighbouring empty field. Jumping is not allowed. Please select a different field." << std::endl;
		toFn = FieldName::None;
	}
	
	return toFn;
} 
/* Place piece onto Board and update game visuals. */
void GameHelper::placePieceOnBoard(Game& game, FieldName fn) {
	game.addPiece(fn);
	game.getBoard().display();
	std::cout << std::endl;
	printInfoTable(game);
	std::cout << std::endl;
}

/* Place piece on selected field of the Board after validating selected field. */
bool GameHelper::handleAddPiece(Game& game){
	FieldName fn = FieldName::None;
	while (fn == FieldName::None) {
		fn = validateAddPiece(game);
	}
	placePieceOnBoard(game, fn);

	return game.checkMillsByFieldName(fn);
}

/* Prints who created a mill and what they need to do. */
void GameHelper::printMillPlayerInfo(Game& game) {
	std::string currentPlayerName = game.getCurrentPlayer()->getName();
	std::string otherPlayerName = game.getOtherPlayer()->getName();
	std::cout << currentPlayerName << " created a mill. " << std::endl;
	std::cout << currentPlayerName << " has to select a field to take  one of " << otherPlayerName << "'s pieces off the board." << std::endl;
}
bool GameHelper::pieceRemovable(Game& game, std::shared_ptr<Piece> p) {
	if (p == nullptr) {
		return false;
	} else {
		Player* other = game.getOtherPlayer();
		if (!p->isInMill() || other->allPiecesInMill()) {
			return true;
		}
	}
	return false;
}
/* Perform all necessary checks to ensure that: the seleceted field name is an existing field name, that the selected field is not empty and 
contains the piece that belongs to the appropriate user depending on whehter the player is moving their own piece or taking off the piece 
of the opponent, and if the opponent's piece is being removed, that the piece eligible to be removed (is not in a mill, or all the opponent's
pieces are in a mill so any can be selected) */
FieldName GameHelper::validateRemovePiece(Game& game, Player& player, bool removeAfterMill){
	FieldName fn = GameHelper::getFieldInput();
	if (fn == FieldName::None) {
		std::cout << "Please select a valid field Name." << std::endl;
	} else if (game.checkFieldEmpty(fn))  {	 
		std::cout << "The selected field does not have a piece on it. Please select a field that contains "<< player.getName() <<"'s piece." << std::endl;
		fn = FieldName::None;
	} else {
		std::shared_ptr<Piece> p = game.correctPlayerPiece(fn, player);
		if (p == nullptr) {
			std::cout << "Please select a field that contains " << player.getName() << "'s piece." << std::endl;
			fn = FieldName::None;
		} else if (removeAfterMill && !pieceRemovable(game, p)) {			 
			std::cout << "Only pieces that are not in a mill can be removed, unless all pieces are in a mill. Please select a different field." << std::endl;
			fn = FieldName::None;
				
		}
	}
	
	return fn;
}
/* Remove piece after ensuring the selected field is eligible for the operation. */
void GameHelper::handleRemovePiece(Game& game, Player& player, bool removeAfterMill) {
	FieldName fn = FieldName::None;
	while (fn == FieldName::None) {
		fn = validateRemovePiece(game, player, removeAfterMill);
	}
	game.removePiece(fn);
}
/* Inform player of next steps, remove piece and update game visuals */
void GameHelper::handleNewMill(Game& game) {
	printMillPlayerInfo(game);
	handleRemovePiece(game, *game.getOtherPlayer(), true);
	std::cout << std::endl;
	game.getBoard().display();
	std::cout << std::endl;
	printInfoTable(game);
	std::cout << std::endl;
}

/* Validate seleceted fields and once both are eligible, move the piece with the Game's movePiece function. Check if the new move results in a mill
 and return the bool value of this check. */
bool GameHelper::handleMovePiece(Game& game) {
	std::cout << "First, select the field to move from." << std::endl;
	FieldName fromFn = FieldName::None;
	while (fromFn == FieldName::None) {
		fromFn = validateRemovePiece(game, *game.getCurrentPlayer());
	}

	std::cout << "Now choose an empty field to move to." << std::endl;
	FieldName toFn = FieldName::None;
	while (toFn == FieldName::None) {
		toFn = validateAddPiece(game, fromFn);
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

/* Determine whether both players can make at least one more move by examining the pieces on the neighbouring fields of empty fields.
If there is at least one field that has a "blue neighbour" and one that has a "red neighbour", or one that has both colour neighbours,
the condition of continuing the game for a next round is met and loops can be exited. Pointers to players (one or two or none) who can
make a move is returned to the caller in a vector. */
std::vector<Player*> GameHelper::canBothPlayersMove(Game& game) {
	std::vector<Player*> players = {};
	std::vector<std::shared_ptr<Field>>& emptyFields = game.getBoard().getEmptyFields();
	bool bluePlayerCanMove = false;
	bool redPlayerCanMove = false;
	for (auto& f : emptyFields) {	
		std::vector<FieldName> neighbourFieldNames = neighboursMap.at(f->getName());
		for (auto fn : neighbourFieldNames) {
			if (bluePlayerCanMove && redPlayerCanMove) { break;} // exit the loop if both players can move
			std::shared_ptr<Field>& field = game.getBoard().getFieldsMap().at(fn);
			if (!redPlayerCanMove && field->getPiece()->getColour() == Colour::red) {
				redPlayerCanMove = true;
			}
			
			if (!bluePlayerCanMove && field->getPiece()->getColour() == Colour::blue) {
				bluePlayerCanMove = true;
			}
			
		}
	
		if (redPlayerCanMove && bluePlayerCanMove) {
			break; 
		}

	}
	if (redPlayerCanMove) {
		players.push_back(&game.getPlayerByColour(Colour::red));

	}
	if (bluePlayerCanMove) {
		players.push_back(&game.getPlayerByColour(Colour::blue));

	}
	return players;
}
/* Examine whether the selected filed to move to is a neighbour of the field being moved from to prevent
prohibited moves. */
bool GameHelper::isMoveToNeighbour(FieldName fromFn, FieldName toFn) {
	std::vector<FieldName> neighbourFieldNames = neighboursMap.at(fromFn);
	auto it = std::find(neighbourFieldNames.begin(), neighbourFieldNames.end(), toFn);
	return it != neighbourFieldNames.end();
}
/* Check that both players have more than two pieces on the board*/
bool GameHelper::checkPlayersHavePieces(Game & game) {
	return  game.getPlayer1().getPiecesOnBoard().size() > 2
		&& game.getPlayer2().getPiecesOnBoard().size() > 2;
}

/* Check which players can move: if both, examine the number of pieces on board. If one player has two
pieces on the board, the other will be set as winner. If there is only one player who can move, that
player will be set as winner. If no player is set, the default value (nullptr) */
void GameHelper::determineWinner(Game& game, std::vector<Player*> players) {
	if (players.size() == 2) {
		if (game.getPlayer1().getPiecesOnBoard().size() == 2) {
			game.setWinner(game.getPlayer2());
		}
		else if (game.getPlayer2().getPiecesOnBoard().size() == 2) {
			game.setWinner(game.getPlayer1());
		}
	}
	else if (players.size() == 1) {
		game.setWinner(*players[0]);
	}
}