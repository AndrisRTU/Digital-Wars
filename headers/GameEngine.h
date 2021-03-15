#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "GameScene.h"
#include "IGameEngine.h"
#include "IngameAI.h"
#include "IGameStatsListener.h"
#include "IGameSettingsBox.h"

class GameEngine : public IGameEngine {
private:
    GameScene& scene;
    IIngameAI& AI;
    IGameStatsListener& statsListener;
    IGameSettingsBox& msgBox;
    bool checkForMoves();
public:
    GameEngine(GameScene& scene, IIngameAI& AI, IGameStatsListener& statsListener, IGameSettingsBox& msgBox);
    virtual void cellSelected(QPair<qint8, qint8> position) override;
    virtual void newGameStarted() override;
};

#endif // GAMEENGINE_H
