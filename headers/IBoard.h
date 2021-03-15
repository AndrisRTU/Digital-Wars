#ifndef IBOARD_H
#define IBOARD_H
#include "GameCell.h"

class IBoard {
public:
    virtual QVector<QVector<GameCell>>& getBoard() = 0;
    virtual const QVector<QVector<GameCell>>& getBoard() const = 0;
    virtual quint8 getSize() const = 0;
};

#endif // IBOARD_H
