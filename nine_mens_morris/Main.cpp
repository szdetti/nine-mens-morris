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
	std::cout << "***************************" << std::endl;
	std::cout << "*     About The Game      *" << std::endl;
	std::cout << "***************************" << std::endl;
	std::cout << instructions << std::endl;
	std::cout << std::endl;
	printBasicBoard();

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
			std::string name1, name2;
			std::cin.ignore();
			std::cout << "Type in a name for Player 1: ";
			std::getline(std::cin, name1);
			std::cout << "Type in a name for Player 2: ";
			std::getline(std::cin, name2);
			std::cout << std::endl;
		
			Game game = Game(name1, name2);

			/* PHASE 1 */

			while (game.getPlayer1().getInitialPieces().size() > 0 && game.getPlayer2().getInitialPieces().size() > 0) {
				GameHelper::printInfoBeforeUserMove(game);
				FieldName fName;
				bool fieldEmpty = false;
				while (!fieldEmpty) {
					fName = GameHelper::getFieldInput();
					fieldEmpty = game.checkFieldEmpty(fName);
					if (!fieldEmpty) {
						std::cout << "The selected field already has a piece on it. Please select an empty field." << std::endl;
					}
				}
				GameHelper::placePieceOnBoard(game, fName);

				bool newMill = game.checkMillsByFieldName(fName);
				if (newMill) {
					std::string currentPlayerName = game.getCurrentPlayer()->getName();
					std::string otherPlayerName = game.getOtherPlayer() -> getName();
					std::cout << currentPlayerName << " created a mill. " << std::endl;
					std::cout << currentPlayerName << " has to select a field to take  one of " << otherPlayerName << "'s pieces off the board." << std::endl;					
					FieldName fn;
					bool fieldEmpty1 = true;
					std::shared_ptr<Piece> p = nullptr;
					bool isRemovable = false;
					while (fieldEmpty1 || p ==  nullptr || !isRemovable) {
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
				game.setCurrentPlayer(*game.getOtherPlayer());
			}

			/* PHASE 2 */

			/*while (game.getPlayer1().getPiecesOnBoard().size() > 2 && game.getPlayer2().getPiecesOnBoard().size() > 2) {

			}*/

		} else if (response == "e") {
			return 0;
		}
		else {
			std::cout << "Please enter a valid option." << std::endl;
		}
	}
	return 0;

	

}