#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Board.h"
#include "GameCondition.h"
#include "IGameScene.h"
#include <memory>

class GameScene : public IGameScene {
private:
    long long playerWins;
    long long enemyWins;
    std::unique_ptr<Board> board;
    std::unique_ptr<GameCondition> condition;
public:
    GameScene();
    long long getPlayerWins() const;
    long long getEnemyWins() const;
    void gameEnded();
    virtual void startNewGame(NewGameState state, int8_t size) override;
    IBoard& getBoard();
    const IBoard& getBoard() const;
    const IGameConditionMembers& getGameConditionMembers() const;
    IGameConditionChanger& getGameConditionChanger();
    const GameCondition& getGameCondition() const;
};

#endif // GAMESCENE_H
