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
    IngameAI& AI;
    IGameStatsListener& statsListener;
    IGameSettingsBox& msgBox;
    bool checkForMoves();
    using Position = std::pair<uint8_t, uint8_t>;
    void updateScene(Position position);
public:
    GameEngine(GameScene& scene, IngameAI& AI, IGameStatsListener& statsListener, IGameSettingsBox& msgBox);
    virtual void cellSelected(Position position) override;
    virtual void newGameStarted() override;
};

#endif // GAMEENGINE_H
