#ifndef GAMESCOREAREA_H
#define GAMESCOREAREA_H
#include <memory>
#include "QHBoxLayout"
#include "QLabel"
#include "GameScene.h"

class GameScoreArea : public QWidget {
private:
    std::unique_ptr<QHBoxLayout> layout;
    std::unique_ptr<QLabel> playerScore;
    std::unique_ptr<QLabel> enemyScore;
    std::unique_ptr<QLabel> winStatisticLabel;
    const GameScene& scene;
public:
    GameScoreArea(const GameScene& scene);
    void update();
    void reset();
    void updateWinLabel();
};

#endif // GAMESCOREAREA_H
