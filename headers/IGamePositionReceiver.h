#ifndef IGAMEPOSITIONRECEIVER_H
#define IGAMEPOSITIONRECEIVER_H
#include <utility>
#include <cstdint>

class IGamePositionReceiver {
public:
    virtual void receivePosition(std::pair<int8_t, int8_t> position) = 0;
};


#endif // IGAMEPOSITIONRECEIVER_H
