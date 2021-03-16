#include "GameCell.h"
#include "RandomGenerator.h"

GameCell::GameCell(Position& position) :
    selected(false) {
    this->position = position;
    number = getRandomNumber(-9, 9);
}

int8_t GameCell::pick() {
    selected = true;
    return number;
}

int8_t GameCell::getNumber() const {
    return number;
}

std::pair<int8_t, int8_t> GameCell::getPosition() const {
    return position;
}

bool GameCell::isSelected() const {
    return selected;
}
