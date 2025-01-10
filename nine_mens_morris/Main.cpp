#include <iostream>
#include <string>
#include <memory>
#include "Player.h"
#include "Constants.h"
#include "Board.h"
#include "Game.h"
#include "GameHelper.h"

int main() {
	/* INTRODUCTION TO GAME RULES */
	GameHelper::printGameRules();

	/* Start or Exit */
	std::string response;
	while (response != "s" && response != "e") {
		std::cout << "Type S to start game, E to exit: ";
		std::cin >> response;
		std::cout << std::endl;
		response = response.substr(0, 1);
		response[0] = std::tolower(static_cast<unsigned char>(response[0]));
		/* Get names and create players */
		if (response == "s") {
			std::vector<std::string> names = GameHelper::getPlayerNames();
			Game game = Game(names[0], names[1]);

			/* PHASE 1 */

			/* Print who's turn it is and display both players' pieces. Get a field name input, check name validity and field availability. If
			field name is valid and field is empty, place piece on field and display new board status and players' pieces' status. Check if new
			mill has been formed. If yes, print info to user and ask for field input. Validate input, check that filed is not empty and contains
			piece of the opposite player, and that the piece is either not in a mill or all pieces are in a mill, therefore can be taken from the
			board. If piece can be taken, remove piece from board and print board and player piece info. If not, ask player to choose different
			field / piece. */
			while (game.getPlayer1().getInitialPieces().size() > 0 || game.getPlayer2().getInitialPieces().size() > 0) {
				GameHelper::printInfoBeforePlayerMove(game, GamePhase::phase1);	
				bool newMill = GameHelper::handleAddPiece(game);
				if (newMill) { GameHelper::handleNewMill(game); }
				game.setCurrentPlayer(*game.getOtherPlayer());
			}
			 

			/* PHASE 2 */
			std::vector<Player*> playersWhoCanMove = GameHelper::canBothPlayersMove(game);
			if ( playersWhoCanMove.size() == 2) {
				std::cout << "All pieces have been placed on the board. Now players can move their pieces between adjacent fields. Try to reduce the opponent's pieces to 2 to win by forming mills." << std::endl;
				while (GameHelper::checkPlayersHavePieces(game) && playersWhoCanMove.size() == 2) {		
					std::cout << std::endl;
					GameHelper::printInfoBeforePlayerMove(game, GamePhase::phase2);
					bool newMill = GameHelper::handleMovePiece(game);
					if (newMill) { GameHelper::handleNewMill(game); }
					playersWhoCanMove = GameHelper::canBothPlayersMove(game);
					game.setCurrentPlayer(*game.getOtherPlayer());
				}
			}
			GameHelper::determineWinner(game, playersWhoCanMove);
			Player* winner = game.getWinner();
			Player& other = game.getOtherPlayer(*winner);
			if (winner != nullptr) {
				std::cout << other.getName() << " cannot make any more moves. " << std::endl;
				std::cout << getCodeFromColour(winner->getColour()) << "The winner is: " << winner->getName() << getCodeFromColour(Colour::reset) << std::endl;
			}
		}
		else if (response == "e") {
			return 0;
		}
		else {
			std::cout << "Please enter a valid option." << std::endl;
		}
	}
	return 0;
}
	

