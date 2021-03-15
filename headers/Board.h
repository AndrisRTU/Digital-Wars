#ifndef BOARD_H
#define BOARD_H
#include <QVector>
#include "IBoard.h"

class Board : public IBoard {
private:
    QVector<QVector<GameCell>> board;
    quint8 size;
    void init();
public:
    Board(quint8 size = 5);
    void newGame(quint8 size);
    QVector<QVector<GameCell>>& getBoard();
    const QVector<QVector<GameCell>>& getBoard() const;
    quint8 getSize() const;
};

#endif // BOARD_H
