#ifndef IGAMEENGINE_H
#define IGAMEENGINE_H
#include <QPair>

class IGameEngine {
public:
    virtual void cellSelected(QPair<qint8, qint8> position) = 0;
    virtual void newGameStarted() = 0;
};

#endif // IGAMEENGINE_H
