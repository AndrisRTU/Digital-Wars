#ifndef IBOARD_H
#define IBOARD_H
#include "GameCell.h"
#include <vector>

class IBoard {
public:
    virtual std::vector<std::vector<GameCell>>& getBoard() = 0;
    virtual const std::vector<std::vector<GameCell>>& getBoard() const = 0;
    virtual uint8_t getSize() const = 0;
};

#endif // IBOARD_H
