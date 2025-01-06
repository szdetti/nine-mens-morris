#include <vector>
#include <map>
#include "Game.h"
#include "Board.h"
#include <iostream>


Game::Game(std::string playerName1, std::string playerName2)
    : board(Board::getInstance()), player1(Player(playerName1, Colour::red)), player2(playerName2, Colour::blue), currentPlayer(&this->player1) {}

Board& Game::getBoard() {
    return board;
}

void Game::setPlayer1(Player& newPlayer1) {
    player1 = newPlayer1;
}

Player& Game::getPlayer1() {
    return player1;
}

void Game::setPlayer2(Player& newPlayer2) {
    player2 = newPlayer2;
}

Player& Game::getPlayer2() {
    return player2;
}
void Game::setCurrentPlayer(Player& player) {
    currentPlayer = &player;
}

Player* Game::getCurrentPlayer() {
    return currentPlayer;
}

Player* Game::getOtherPlayer() {
    return (currentPlayer == &player1) ? &player2 : &player1;
}
/* Check if a piece on the field associated with the fieldName in the argument is in a mill. Used to determine if a new move has resulted in a mill. */
bool Game::checkMillsByFieldName(FieldName fieldName) {
    std::vector<std::vector<FieldName>> millsToCheck =
        board.getFieldNamesByMills().at(fieldName);
    return checkFieldsByVector(millsToCheck, 0);

}
/* Recursively check if all of the vectors in a nested vector contain pieces belonging to the same player (meaning they contain a mill)*/
bool Game::checkFieldsByVector(std::vector<std::vector<FieldName>>& vec, int index) {
    if (index >= 0 && index < vec.size() - 1) {
        return checkMatchingFields(vec[index], 0) || checkMatchingFields(vec[index + 1], 0);
    }
    else {
        return true;
    }
}
/* Recursively check that fields in a vector contain pieces beloning to the same player by comparing the colour of the pieces. */
bool Game::checkMatchingFields(std::vector<FieldName>& fieldNames, int index) {
    if (index >= 0 && index < fieldNames.size() - 1) {
        return    board.getFieldsMap()[fieldNames[index]]->getPiece()->getColour()
            == board.getFieldsMap()[fieldNames[index + 1]]->getPiece()->getColour()
            && checkMatchingFields(fieldNames, index + 1);
    }
    else {
        return true;
    }
}

/* Check that the selected field is empty by determining the colour of the piece in the field. Return true if the colour
of the piece is Colour::reset, which is the colour of default piece objects that act as placeholders in empty fields. */
bool Game::checkFieldEmpty(FieldName fieldName) {
    std::shared_ptr<Field> fieldToCheckPtr = board.getFieldsMap()[fieldName];
    return fieldToCheckPtr->getPiece()->getColour() == Colour::reset;
}

/* Check if field associated with field name selected by player contains a piece that belongs to the other player. Return false if 
colour of piece on field mathes colour of current player (they chose their own piece to remove). */
std::shared_ptr<Piece> Game::correctPlayerPiece(FieldName fn) {
    std::shared_ptr<Field> f = board.getFieldsMap()[fn];
    std::shared_ptr<Piece> toRemove = f->getPiece();
    if (ColourMap.at(toRemove->getColour()) == ColourMap.at(currentPlayer->getColour())) {
        return nullptr;
    } 
    return toRemove;
}

bool Game::pieceRemovable(std::shared_ptr<Piece> p) {
    if (p == nullptr) {
        return false;
    }
    else {
        Player* other = getOtherPlayer();
        if (!p->isInMill() || other->allPiecesInMill()) {
            return true;
        }
    }
    return false;
}

/* Called in phase 1 of the game, when players place their pieces on the board. Retrieve the field (pointer) associated with the fieldname provided by the player, 
set the field's piece field to a pointer pointing to (the memory address of) a piece object associated with the current player making the move. Keep track of
the current player's pieces by updating the vectors representing the status of the pieces (initial - yet to be placed on the board, on board - as named) */
void Game::addPiece(FieldName fn) {
        std::shared_ptr<Field> f = board.getFieldsMap()[fn];
        std::shared_ptr<Piece> p = currentPlayer->getInitialPieces().back();
        currentPlayer->getInitialPieces().pop_back();
        currentPlayer->getPiecesOnBoard().push_back(p);
        f->setPiece(p);
}

/* When a player is allowed to remove one of the other player's pieces from the board, remove that
piece from the field specified by the player collecting the piece. Replace the removed piece with an
empty (default) one in the field of the board. Add the removed piece to the captured pieces vector
of the collecting player. Remove the removed piece from the player losing the piece.  */

void Game::removePiece(FieldName fn) {
        std::shared_ptr<Field> f = board.getFieldsMap()[fn];
        std::shared_ptr<Piece> captured = f->getPiece();
        f->setPiece(std::make_shared<Piece>());
        currentPlayer->getCapturedPieces().push_back(captured);
        Player* p = getOtherPlayer();
        p->getPiecesOnBoard().pop_back();  
}

/* Called in phase 2 of the game when users have placed all their pieces on the board and can now move them between eligible fields. Similarly to the
functions that add and remove a piece, retrieve the field pointers associated with the fieldnames provided by the user and set the piece fields of the field 
objects to the appropriate piece pointer - a default piece for the field being moved from fields and the current player's piece for the field being moved to. */
void Game::movePiece(std::string fromFieldNameString, std::string toFieldNameString) {
    try{
        FieldName fromFn = findFieldNameByString(fromFieldNameString);
        FieldName toFn = findFieldNameByString(toFieldNameString);
        std::shared_ptr<Field> fromField = board.getFieldsMap()[fromFn];
        std::shared_ptr<Field> toField = board.getFieldsMap()[toFn];
        std::shared_ptr<Piece> toMove = fromField->getPiece();
        toField->setPiece(toMove);
        fromField->setPiece(std::make_shared<Piece>());
     } catch (std::invalid_argument e) {
        std::cout << e.what() << std::endl;
    }
}

/* Print both player's pieces yet to be placed on the board.  */
void Game::printPlayerInitialPieces() {
    if (player1.getInitialPieces().size() > 0) {
        std::cout << player1.getName() << "'s pieces to place on board: ";
        for (auto p : player1.getInitialPieces()) {
            p->display();
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    if (player2.getInitialPieces().size() > 0) {
        std::cout << player2.getName() << "'s pieces to place on board: ";
        for (auto p : player2.getInitialPieces()) {
            p->display();
            std::cout << " ";
        }
    }
    std::cout << std::endl;

}
/* Print the pieces of each player that are on the board and captured from the other player to visualise game status. */
void Game::printInfoTable() {
 
    /************* player1 name ******************/
    
    std::cout << "                     +--------------------+--------------------+" << std::endl;
    std::cout << "                     + " << player1.getName();
    int space1 = 19-player1.getName().length();
    for (int i = 0; i < space1; i++) {
        std::cout << " ";
    }

    /**************** player2 name ******************/

    std::cout << "+ " << player2.getName();
    int space2 = 19 - player2.getName().length();
    for (int i = 0; i < space2; i++) {
        std::cout << " ";
    }
    std::cout << "+" << std::endl;
    std::cout << "+--------------------+--------------------+--------------------+" << std::endl;
    std::cout << "+  pieces on board   + ";

    /***************** player1 pieces on board ******************/

    for (auto p : player1.getPiecesOnBoard()){
        p->display();
        std::cout << " ";
    }
    int space3 = 19-player1.getPiecesOnBoard().size() * 2;
    for (int i = 0; i < space3; i++) {
        std::cout << " ";
    }

    /**************** player2 pieces on board ******************/

    std::cout << "+ ";
    for (auto p : player2.getPiecesOnBoard()) {
        p->display();
        std::cout << " ";
    }
    int space4 = 19-player2.getPiecesOnBoard().size() * 2;
    for (int i = 0; i < space4; i++) {
        std::cout << " ";
    }
    std::cout << "+" << std::endl;
    std::cout << "+--------------------+--------------------+--------------------+" << std::endl;
    
    /**************** player1 captured pieces ******************/

    std::cout << "+  captured pieces   + ";
    for (auto p : player1.getCapturedPieces()) {
        p->display();
        std::cout << " ";
    }
    int space5 = 19-player1.getCapturedPieces().size() * 2;
    for (int i = 0; i < space5; i++) {
        std::cout << " ";
    }

    /***************** player2 captured pieces ******************/

    std::cout << "+ ";
    for (auto p : player2.getCapturedPieces()) {
        p->display();
        std::cout << " ";
    }
    int space6 = 19-player2.getCapturedPieces().size() * 2;
    for (int i = 0; i < space6; i++) {
        std::cout << " ";
    }
    std::cout << "+" << std::endl;
    std::cout << "+--------------------+--------------------+--------------------+" << std::endl;
}


Game::~Game() {
    currentPlayer = nullptr;
}