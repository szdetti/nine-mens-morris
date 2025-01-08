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

Player& Game::getPlayerByColour(Colour colour) {
    if (getPlayer1().getColour() == colour) return player1;
    if (getPlayer2().getColour() == colour) return player2;
}

/* Check if a piece on the field associated with the fieldName in the argument is in a mill. Used to determine if a new move has resulted in a mill. */
bool Game::checkMillsByFieldName(FieldName fieldName) {
    std::vector<std::vector<FieldName>> millsToCheck =
        board.getFieldNamesByMills().at(fieldName);
    return checkFieldsByVector(millsToCheck);

}
/* Check if both of the vectors in a nested vector contain field names that hold pieces belonging to the same player 
(meaning they have achieved a mill). If any of them contains field names that form a mill, set the corresponding
pieces flag to indicate they are in a mill. */
bool Game::checkFieldsByVector(std::vector<std::vector<FieldName>>& vec) {
    bool firstMill = checkMatchingFields(vec[0], 0);
    bool secondMill = checkMatchingFields(vec[1], 0);
    if (firstMill) {
        for (auto fieldName : vec[0]) {
            board.getFieldsMap()[fieldName]->getPiece()->setInMill(true);
      }
    }

    if (secondMill) {
        for (auto fieldName : vec[0]) {
            board.getFieldsMap()[fieldName]->getPiece()->setInMill(true);
        }
    }

    return firstMill || secondMill;
   
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

/* Check if field associated with field name selected by player contains a piece that belongs to the appropriate player. Return false if 
colour of piece on field mathes colour of current player (they chose their own piece to remove). */
std::shared_ptr<Piece> Game::correctPlayerPiece(FieldName fn, Player& player) {
    std::shared_ptr<Field> f = board.getFieldsMap()[fn];
    std::shared_ptr<Piece> toRemove = f->getPiece();
    if (ColourMap.at(toRemove->getColour()) != ColourMap.at(player.getColour())) {
        return nullptr;
    } 
    return toRemove;
}



/* Called in phase 1 of the game, when players place their pieces on the board. Retrieve the field (pointer) associated with the fieldname provided by the player, 
set the field's piece field to a pointer pointing to (the memory address of) a piece object associated with the current player making the move. Keep track of
the current player's pieces by updating the vectors representing the status of the pieces (initial - yet to be placed on the board, on board - as named).
Update the board's vector that keeps track of empty fields by removing the shared_ptr of the field holding the newly placed piece.*/
void Game::addPiece(FieldName fn) {
        std::shared_ptr<Field> f = board.getFieldsMap()[fn];
        std::shared_ptr<Piece> p = currentPlayer->getInitialPieces().back();
        currentPlayer->getInitialPieces().pop_back();
        currentPlayer->getPiecesOnBoard().push_back(p);
        f->setPiece(p);
        std::vector<std::shared_ptr<Field>> emptyFields = getBoard().getEmptyFields();
        emptyFields.erase(emptyFields.begin() + static_cast<int>(fn));
}

/* When a player is allowed to remove one of the other player's pieces from the board, remove that
piece from the field specified by the player collecting the piece. Replace the removed piece with an
empty (default) one in the field of the board. Add the removed piece to the captured pieces vector
of the collecting player. Remove the removed piece from the player losing the piece. Update the board's
vector that keeps track of empty fields by removing the shared_ptr of the field that the piece was 
removed from. */

void Game::removePiece(FieldName fn) {
        std::shared_ptr<Field> f = board.getFieldsMap()[fn];
        std::shared_ptr<Piece> captured = f->getPiece();
        f->setPiece(std::make_shared<Piece>());
        currentPlayer->getCapturedPieces().push_back(captured);
        Player* p = getOtherPlayer();
        p->getPiecesOnBoard().pop_back(); 
        std::vector<std::shared_ptr<Field>> emptyFields = getBoard().getEmptyFields();
        emptyFields.insert(emptyFields.begin() + static_cast<int>(fn), f);

}

/* Called in phase 2 of the game when users have placed all their pieces on the board and can now move them between eligible fields. Similarly to the
functions that add and remove a piece, retrieve the field pointers associated with the fieldnames provided by the user and set the piece fields of the field 
objects to the appropriate piece pointer - a default piece for the field being moved from fields and the current player's piece for the field being moved to. */
void Game::movePiece(FieldName fromFn, FieldName toFn) {
        std::shared_ptr<Field> fromField = board.getFieldsMap()[fromFn];
        std::shared_ptr<Field> toField = board.getFieldsMap()[toFn];
        std::shared_ptr<Piece> toMove = fromField->getPiece();
        toField->setPiece(toMove);
        if (toMove->isInMill()) { toMove->setInMill(false); }
        fromField->setPiece(std::make_shared<Piece>());
        std::vector<std::shared_ptr<Field>> emptyFields = getBoard().getEmptyFields();
        emptyFields.erase(emptyFields.begin() + static_cast<int>(toFn));
        emptyFields.insert(emptyFields.begin() + static_cast<int>(fromFn), fromField);
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

    
    


Game::~Game() {
    currentPlayer = nullptr;
}