#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "GameScene.h"
#include "IGameStatsListener.h"
#include "IGameSettingsBox.h"
#include <QThread>

class GameEngine : public QObject {
    Q_OBJECT
private:
    GameScene& scene;
    QThread& AI;
    IGameStatsListener& statsListener;
    IGameSettingsBox& msgBox;
    IGamePositionReceiver& visualReceiver;
    bool checkForMoves();
    using Position = std::pair<uint8_t, uint8_t>;
public:
    GameEngine(GameScene& scene, QThread& AI, IGameStatsListener& statsListener, IGameSettingsBox& msgBox, IGamePositionReceiver& visualReceiver);
    void cellSelected(Position position);
    void newGameStarted();
};

#endif // GAMEENGINE_H
