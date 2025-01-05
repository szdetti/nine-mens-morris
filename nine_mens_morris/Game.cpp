#include <vector>
#include <map>
#include "Game.h"
#include "Board.h"
#include <iostream>


Game::Game(Player player1, Player player2)
    : board(Board::getInstance()), player1(player1), player2(player2), currentPlayer(&this->player1) {}



Board& Game::getBoard() {
    return board;
}

void Game::setPlayer1(Player newPlayer1) {
    player1 = newPlayer1;
}

Player& Game::getPlayer1() {
    return player1;
}

void Game::setPlayer2(Player newPlayer2) {
    player2 = newPlayer2;
}

Player& Game::getPlayer2() {
    return player2;
}
void Game::setCurrentPlayer(Player player) {
    currentPlayer = &player;
}

Player* Game::getCurrentPlayer() {
    return currentPlayer;
}

Player* Game::getOtherPlayer() {
    return (currentPlayer == &player1) ? &player2 : &player1;
}
bool Game::checkMillsByFieldName(FieldName fieldName) {
    std::vector<std::vector<FieldName>> millsToCheck =
        board.getFieldNamesByMills().at(fieldName);
    return checkFieldsByVector(millsToCheck, 0);

}

bool Game::checkFieldsByVector(std::vector<std::vector<FieldName>>& vec, int index) {
    if (index >= 0 && index < vec.size() - 1) {
        return checkMatchingFields(vec[index], 0) || checkMatchingFields(vec[index + 1], 0);
    }
    else {
        return true;
    }
}

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

/* Check that the selected field is empty by determining the colour of the piece in the field. Empty
fields have a default piece on them whose colour is Colour::reset. */
bool Game::checkFieldEmpty(FieldName fieldName) {
    std::shared_ptr<Field> fieldToCheckPtr = board.getFieldsMap()[fieldName];
    return fieldToCheckPtr->getPiece()->getColour() == Colour::reset;
}

/* */
void Game::addPiece(std::string fieldNameString) {
    try{
        FieldName fn = findFieldNameByString(fieldNameString);
        std::shared_ptr<Field> f = board.getFieldsMap()[fn];
        std::shared_ptr<Piece> p = currentPlayer->getInitialPieces().back();
        currentPlayer->getInitialPieces().pop_back();
        currentPlayer->getPiecesOnBoard().push_back(p);
        f->setPiece(p);
   
   
    }
    catch (std::invalid_argument e) {
        std::cout << e.what() << std::endl;
    }
}

/* When a player is allowed to remove one of the other player's pieces from the board, remove that
piece from the field specified by the player collecting the piece. Replace the removed piece with an
empty (default) one in the field of the board. Add the removed piece to the captured pieces vector
of the collecting player. Remove the removed piece from the player losing the piece.  */
void Game::removePiece(std::string fieldNameString)
{
    try{
        FieldName fn = findFieldNameByString(fieldNameString);
        std::shared_ptr<Field> f = board.getFieldsMap()[fn];
        std::shared_ptr<Piece> captured = f->getPiece();
        f->setPiece(std::make_shared<Piece>());
        currentPlayer->getCapturedPieces().push_back(captured);
        Player* p = getOtherPlayer();
        p->getPiecesOnBoard().pop_back();
    } catch (std::invalid_argument e) {
        std::cout << e.what() << std::endl;
    }
}

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

void Game::printInfoTable() {
   /************* player1 name ******************/
    std::cout << "                     +--------------------+--------------------+" << std::endl;
    std::cout << "                     + " << player1.getName();
    int space1 = 19-player1.getName().length();
    for (int i = 0; i < space1; i++) {
        std::cout << " ";
    }

    /************* player2 name ******************/

    std::cout << "+ " << player2.getName();
    int space2 = 19 - player2.getName().length();
    for (int i = 0; i < space2; i++) {
        std::cout << " ";
    }
    std::cout << "+" << std::endl;
    std::cout << "+--------------------+--------------------+--------------------+" << std::endl;
    std::cout << "+  pieces on board   + ";

    /************* player1 pieces on board ******************/

    for (auto p : player1.getPiecesOnBoard()){
        p->display();
        std::cout << " ";
    }
    int space3 = 19-player1.getPiecesOnBoard().size() * 2;
    for (int i = 0; i < space3; i++) {
        std::cout << " ";
    }

    /************* player2 pieces on board ******************/

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

    /************* player1 captured pieces ******************/

    std::cout << "+  captured pieces   + ";
    for (auto p : player1.getCapturedPieces()) {
        p->display();
        std::cout << " ";
    }
    int space5 = 19-player1.getCapturedPieces().size() * 2;
    for (int i = 0; i < space5; i++) {
        std::cout << " ";
    }

    /************* player2 captured pieces ******************/

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