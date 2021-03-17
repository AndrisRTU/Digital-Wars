#ifndef BOARD_H
#define BOARD_H
#include "IBoard.h"

class Board : public IBoard {
private:
    std::vector<std::vector<GameCell>> board;
    uint8_t size;
    void init();
public:
    Board(uint8_t size = 5);
    void newGame(uint8_t size);
    std::vector<std::vector<GameCell>>& getBoard();
    const std::vector<std::vector<GameCell>>& getBoard() const;
    uint8_t getSize() const;
};

#endif // BOARD_H
