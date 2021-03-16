#ifndef BOARDGAMECELL_H
#define BOARDGAMECELL_H
#include <cstdint>
#include <utility>

class GameCell {
private:
    int8_t number;
    using Position = std::pair<int8_t, int8_t>;
    Position position;
    bool selected;
public:
    GameCell(Position& position);
    int8_t pick();
    int8_t getNumber() const;
    std::pair<int8_t, int8_t> getPosition() const;
    bool isSelected() const;
};

#endif // BOARDGAMECELL_H
