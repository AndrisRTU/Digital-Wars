#ifndef IGAMECONDITIONMEMBERS_H
#define IGAMECONDITIONMEMBERS_H
#include "GameEnums.h"
#include <utility>
#include <cstdint>

class IGameConditionMembers {
public:
    virtual int getPlayerScore() const = 0;
    virtual int getAIScore() const = 0;
    virtual GameTurn getTurn() const = 0;
    virtual Movement getMovement() const = 0;
    virtual std::pair<uint8_t, uint8_t> getPosition() const = 0;
};


#endif // IGAMECONDITIONMEMBERS_H
