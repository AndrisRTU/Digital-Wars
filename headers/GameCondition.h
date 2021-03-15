#ifndef GAMETURN_H
#define GAMETURN_H
#include <QPair>
#include "IGameConditionChanger.h"
#include "IGameConditionMembers.h"

class GameCondition : public IGameConditionMembers, public IGameConditionChanger {
private:
    qint16 playerScore;
    qint16 AIScore;
    GameTurn turn;
    Movement movement;
    QPair<quint8, quint8> position;
public:
    GameCondition();
    void gameEnded();
    void startNewGame(NewGameState state, quint8 size);
    virtual void scoreChanged(int number) override;
    virtual void gameTurnChanged() override;
    virtual void movementChanged() override;
    virtual void positionChanged(QPair<quint8, quint8> position) override;
    virtual int getPlayerScore() const override;
    virtual int getAIScore() const override;
    virtual GameTurn getTurn() const override;
    virtual Movement getMovement() const override;
    virtual QPair<quint8, quint8> getPosition() const override;

};
#endif // GAMETURN_H
