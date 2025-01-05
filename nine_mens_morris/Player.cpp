#include "Player.h"

Player::Player() : name("default"), winner(false), initialPieces(), piecesOnBoard(), capturedPieces() {
    createInitialPieces(Colour::reset);
}

Player::Player(std::string name, Colour colour) : name(name), winner(false), initialPieces(), piecesOnBoard(), capturedPieces() {
    createInitialPieces(colour);
}

void Player::setName(std::string newName) {
    name = newName;
}

std::string Player::getName() {
    return name;
}

void Player::setWinner(bool win) {
    winner = win;
}

bool Player::isWinner() {
    return winner;
}

void Player::setInitialPieces(std::vector<std::shared_ptr<Piece>> newInitialPieces) {
    initialPieces = newInitialPieces;
}

std::vector<std::shared_ptr<Piece>>& Player::getInitialPieces() {
    return initialPieces;
}

void Player::setPiecesOnBoard(std::vector<std::shared_ptr<Piece>> newPiecesOnBoard) {
    piecesOnBoard = newPiecesOnBoard;
}

std::vector<std::shared_ptr<Piece>>& Player::getPiecesOnBoard() {
    return piecesOnBoard;
}

void Player::setCapturedPieces(std::vector<std::shared_ptr<Piece>> newCapturedPieces) {
    capturedPieces = newCapturedPieces;
}

std::vector<std::shared_ptr<Piece>>& Player::getCapturedPieces() {
    return capturedPieces;
}

void Player::createInitialPieces(Colour colour) {
    for (int i = 0; i < piecesPerPlayer; i++) {
        // Creating a new Piece using shared_ptr
        initialPieces.push_back(std::make_shared<Piece>(colour));
    }
}

bool Player::allPiecesInMill() {
    for (auto p : piecesOnBoard) {
        if (!p->isInMill()) {
            return false;
        }
    }

    return true;
}

Player::~Player() {}
