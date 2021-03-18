#ifndef IGAMEPOSITIONRECEIVER_H
#define IGAMEPOSITIONRECEIVER_H
#include <utility>
#include <cstdint>
#include <QObject>

class IGamePositionReceiver {
public slots:
    virtual void receivePosition(std::pair<uint8_t, uint8_t> position) = 0;
};

#endif // IGAMEPOSITIONRECEIVER_H
