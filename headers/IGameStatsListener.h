#ifndef IGAMESTATSLISTENER_H
#define IGAMESTATSLISTENER_H

class IGameStatsListener {
public:
    virtual void updateCondition() = 0;
    virtual void clearCondition() = 0;
    virtual void newGameStarted() = 0;
    virtual void gameEnded() = 0;
};

#endif // IGAMESTATSLISTENER_H
