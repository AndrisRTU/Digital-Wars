#ifndef GAMEAREA_H
#define GAMEAREA_H
#include <utility>
#include <memory>
#include "QGridLayout"
#include "BoardCell.h"
#include "GameScene.h"
#include "IGamePositionReceiver.h"

class GameArea : public QWidget, public IGamePositionReceiver {
private:
    std::unique_ptr<QGridLayout> layout;
    std::vector<std::vector<BoardCell*>> cells;
    const GameScene& scene;
    IGameEngine* engine;
public:
    GameArea(const GameScene& scene);
    void setGameEngine(IGameEngine* engine);
    void update();
    void diactivateCells();
    void clear();
    void reset();
    virtual void receivePosition(std::pair<int8_t, int8_t> position) override;
signals:
    void onClick();
};

#endif // GAMEAREA_H
