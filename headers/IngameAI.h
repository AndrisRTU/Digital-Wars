#ifndef IngameAI_H
#define IngameAI_H
#include <QThread>
#include <utility>
#include "Node.h"
#include "IGamePositionReceiver.h"
#include "GameScene.h"
#include "VisualGameArea.h"

class IngameAI : public QObject {
    Q_OBJECT
private:
    uint8_t difficulty;
    uint8_t foresightCount;
    const GameScene& scene;
    int16_t scoreDifferenceHeuristic(const Node& node);
    int16_t NodeSequenceHeuristic(const Node& node, uint8_t depth);
    int16_t minimax(const Node& node, uint8_t depth, bool isMax, AlphaBetaModule alphaBeta);
    using Position = std::pair<uint8_t, uint8_t>;
    void addNode(Node& node, uint8_t depth);
public:
    IngameAI(uint8_t difficulty, const GameScene& scene);
    void calculatePosition();
    void setDifficulty(uint8_t difficulty);
signals:
    void positionCalculated(Position position);
};

#endif // IngameAI_H
