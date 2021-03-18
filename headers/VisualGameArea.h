#ifndef GAMEAREA_H
#define GAMEAREA_H
#include <utility>
#include <memory>
#include "QGridLayout"
#include "BoardCell.h"
#include "GameScene.h"
#include "IGamePositionReceiver.h"
#include "GameEngine.h"

class VisualGameArea : public QWidget, public IGamePositionReceiver {
    Q_OBJECT
private:
    std::unique_ptr<QGridLayout> layout;
    std::vector<std::vector<BoardCell*>> cells;
    const GameScene& scene;
    GameEngine* engine;
public:
    VisualGameArea(const GameScene& scene);
    void setGameEngine(GameEngine* engine);
    void update();
    void diactivateCells();
    void clear();
    void reset();
    virtual void receivePosition(std::pair<uint8_t, uint8_t> position) override;
public slots:
    void onClick();
};

#endif // GAMEAREA_H
