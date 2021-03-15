#include "Board.h"

Board::Board(quint8 size) :
    size(size) {
    init();
}

void Board::init() {
    board.clear();
    board.resize(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            QPair<quint8, quint8> position;
            position.first = i;
            position.second = j;
            board[i].push_back(GameCell(position));
        }
    }
}

void Board::newGame(quint8 size) {
    this->size = size;
    init();
}

QVector<QVector<GameCell>>& Board::getBoard() {
    return board;
}

const QVector<QVector<GameCell>>& Board::getBoard() const {
    return board;
}

quint8 Board::getSize() const {
    return size;
}
