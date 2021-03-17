#ifndef INGAMEAI_H
#define INGAMEAI_H
#include "IIngameAI.h"
#include "IGamePositionReceiver.h"
#include "GameScene.h"
#include "Node.h"

class IngameAI : public IIngameAI {
private:
    uint8_t difficulty;
    uint8_t foresightCount;
    const GameScene& scene;
    IGamePositionReceiver& receiver;
    int16_t scoreDifferenceHeuristic(const Node& node);
    int16_t NodeSequenceHeuristic(const Node& node, uint8_t depth);
    int16_t minimax(const Node& node, uint8_t depth, bool isMax, AlphaBetaModule alphaBeta);
    using Position = std::pair<uint8_t, uint8_t>;
    void addNode(Node& node, uint8_t depth);
public:
    IngameAI(uint8_t difficulty, const GameScene& scene, IGamePositionReceiver& receiver);
    virtual void setDifficulty(uint8_t difficulty) override;
    virtual void makeMove() override;
};
#endif // INGAMEAI_H
