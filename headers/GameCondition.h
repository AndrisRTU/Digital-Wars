#ifndef GAMETURN_H
#define GAMETURN_H
#include "IGameConditionChanger.h"
#include "IGameConditionMembers.h"

class GameCondition : public IGameConditionMembers, public IGameConditionChanger {
private:
    int16_t playerScore;
    int16_t AIScore;
    GameTurn turn;
    Movement movement;
    std::pair<uint8_t, uint8_t> position;
public:
    GameCondition();
    void gameEnded();
    void startNewGame(NewGameState state, uint8_t size);
    virtual void scoreChanged(int number) override;
    virtual void gameTurnChanged() override;
    virtual void movementChanged() override;
    virtual void positionChanged(std::pair<uint8_t, uint8_t> position) override;
    virtual int getPlayerScore() const override;
    virtual int getAIScore() const override;
    virtual GameTurn getTurn() const override;
    virtual Movement getMovement() const override;
    virtual std::pair<uint8_t, uint8_t> getPosition() const override;

};
#endif // GAMETURN_H
