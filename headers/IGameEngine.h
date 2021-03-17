#ifndef IGAMEENGINE_H
#define IGAMEENGINE_H
#include <utility>
#include <cstdint>

class IGameEngine {
public:
    virtual void cellSelected(std::pair<uint8_t, uint8_t> position) = 0;
    virtual void newGameStarted() = 0;
};

#endif // IGAMEENGINE_H
