#ifndef IGAMECONDITIONCHANGER_H
#define IGAMECONDITIONCHANGER_H
#include <QPair>

class IGameConditionChanger {
public:
    virtual void scoreChanged(int number) = 0;
    virtual void gameTurnChanged() = 0;
    virtual void movementChanged() = 0;
    virtual void positionChanged(QPair<quint8, quint8> position) = 0;
};

#endif // IGAMECONDITIONCHANGER_H
