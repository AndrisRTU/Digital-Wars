#include "GameCell.h"
#include "RandomGenerator.h"

GameCell::GameCell(Position& position) :
    selected(false) {
    this->position = position;
    number = getRandomNumber(-9, 9);
}

qint8 GameCell::pick() {
    selected = true;
    return number;
}

qint8 GameCell::getNumber() const {
    return number;
}

QPair<quint8, quint8> GameCell::getPosition() const {
    return position;
}

bool GameCell::isSelected() const {
    return selected;
}
