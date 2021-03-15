#ifndef BOARDCELL_H
#define BOARDCELL_H
#include "GameCell.h"
#include <QPushButton>
#include "IBoard.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "IGameEngine.h"
#include "GameEnums.h"
#include "IGameConditionMembers.h"

class BoardCell : public QPushButton {
    Q_OBJECT
private:
    const GameCell& cell;
    const IGameConditionMembers& gameCondition;
    IGameEngine& listener;
    std::unique_ptr<QPropertyAnimation> fadeAnimation;
    std::unique_ptr<QGraphicsOpacityEffect> opacity;
public:
    BoardCell(const GameCell& cell, const IGameConditionMembers& gameCondition, IGameEngine& listener);
    void awake();
    void diactivate();
    void pressed();
};

#endif // BOARDCELL_H
