#ifndef IGAMESCENE_H
#define IGAMESCENE_H
#include "GameEnums.h"

class IGameScene {
public:
    virtual void startNewGame(NewGameState state, uint8_t size) = 0;
};


#endif // IGAMESCENE_H
