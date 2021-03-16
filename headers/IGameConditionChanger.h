#ifndef IGAMECONDITIONCHANGER_H
#define IGAMECONDITIONCHANGER_H
#include <utility>
#include <cstdint>

class IGameConditionChanger {
public:
    virtual void scoreChanged(int number) = 0;
    virtual void gameTurnChanged() = 0;
    virtual void movementChanged() = 0;
    virtual void positionChanged(std::pair<int8_t, int8_t> position) = 0;
};

#endif // IGAMECONDITIONCHANGER_H
