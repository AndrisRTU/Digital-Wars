#include "Board.h"

Board::Board(int8_t size) :
    size(size) {
    init();
}

void Board::init() {
    board.clear();
    board.resize(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::pair<int8_t, int8_t> position(i, j);
            position.first = i;
            position.second = j;
            board[i].push_back(GameCell(position));
        }
    }
}

void Board::newGame(int8_t size) {
    this->size = size;
    init();
}

std::vector<std::vector<GameCell>>& Board::getBoard() {
    return board;
}

const std::vector<std::vector<GameCell>>& Board::getBoard() const {
    return board;
}

int8_t Board::getSize() const {
    return size;
}
