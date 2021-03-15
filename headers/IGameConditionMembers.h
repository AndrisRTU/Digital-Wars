#ifndef IGAMECONDITIONMEMBERS_H
#define IGAMECONDITIONMEMBERS_H
#include "GameEnums.h"
#include <QPair>

class IGameConditionMembers {
public:
    virtual int getPlayerScore() const = 0;
    virtual int getAIScore() const = 0;
    virtual GameTurn getTurn() const = 0;
    virtual Movement getMovement() const = 0;
    virtual QPair<quint8, quint8> getPosition() const = 0;
};


#endif // IGAMECONDITIONMEMBERS_H
