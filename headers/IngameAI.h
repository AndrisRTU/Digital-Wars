#ifndef INGAMEAI_H
#define INGAMEAI_H
#include "IIngameAI.h"
#include "IGamePositionReceiver.h"
#include "GameScene.h"
#include "Node.h"

class IngameAI : public IIngameAI {
private:
    int8_t difficulty;
    int8_t foresightCount;
    const GameScene& scene;
    IGamePositionReceiver& receiver;
    int16_t scoreDifferenceHeuristic(const Node& node);
    int16_t NodeSequenceHeuristic(const Node& node, int8_t depth);
    int16_t minimax(const Node& node, int8_t depth, bool isMax, AlphaBetaModule alphaBeta);
    using Position = std::pair<int8_t, int8_t>;
    void addNode(Node& node, int8_t depth);
public:
    IngameAI(int8_t difficulty, const GameScene& scene, IGamePositionReceiver& receiver);
    virtual void setDifficulty(int8_t difficulty) override;
    virtual void makeMove() override;
};
#endif // INGAMEAI_H
