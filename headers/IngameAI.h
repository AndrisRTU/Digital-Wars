#ifndef INGAMEAI_H
#define INGAMEAI_H
#include <QMetaType>
#include "IIngameAI.h"
#include "IGamePositionReceiver.h"
#include "GameScene.h"
#include "Node.h"

class IngameAI : public IIngameAI {
private:
    quint8 difficulty;
    quint8 foresightCount;
    const GameScene& scene;
    IGamePositionReceiver& receiver;
    qint16 scoreDifferenceHeuristic(const Node& node);
    qint16 WorstNodePlayerHeuristic(const Node& node, quint8 depth);
    qint16 BestNodeAIHeuristic(const Node& node, quint8 depth);
    qint16 minimax(const Node& node, quint8 depth, bool isMax, AlphaBetaModule alphaBeta);
    using Position = QPair<quint8, quint8>;
    void addNode(Node& node, quint8 depth);
public:
    IngameAI(quint8 difficulty, const GameScene& scene, IGamePositionReceiver& receiver);
    virtual void setDifficulty(quint8 difficulty) override;
    virtual void makeMove() override;
};
#endif // INGAMEAI_H
