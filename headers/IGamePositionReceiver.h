#ifndef IGAMEPOSITIONRECEIVER_H
#define IGAMEPOSITIONRECEIVER_H
#include <QPair>

class IGamePositionReceiver {
public:
    virtual void receivePosition(QPair<quint8, quint8> position) = 0;
};


#endif // IGAMEPOSITIONRECEIVER_H
