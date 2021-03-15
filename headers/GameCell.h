#ifndef BOARDGAMECELL_H
#define BOARDGAMECELL_H
#include <QMetaType>

class GameCell {
private:
    qint8 number;
    using Position = QPair<quint8, quint8>;
    Position position;
    bool selected;
public:
    GameCell(Position& position);
    qint8 pick();
    qint8 getNumber() const;
    QPair<quint8, quint8> getPosition() const;
    bool isSelected() const;
};

#endif // BOARDGAMECELL_H
