#ifndef IGAMESCENE_H
#define IGAMESCENE_H
#include "GameEnums.h"
#include <QMetaType>

class IGameScene {
public:
    virtual void startNewGame(NewGameState state, quint8 size) = 0;
};


#endif // IGAMESCENE_H
