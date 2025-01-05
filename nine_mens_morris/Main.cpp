#include <iostream>
#include "Player.h"
#include "Constants.h"
#include "Board.h"
#include "Game.h"

int main() {

	Player player1 = Player("bernadett", Colour::red);
	Player player2 = Player("Arthur", Colour::blue);
	Game g = Game(player1, player2);
	g.addPiece("A1");
	g.getBoard().display();
	g.movePiece("A1", "D1");
	g.getBoard().display();
	g.printInfoTable();
	return 0;
}