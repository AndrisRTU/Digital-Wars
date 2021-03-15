#ifndef NODE_H
#define NODE_H
#include <QVector>
#include "GameCondition.h"
#include <memory>

struct AlphaBetaModule {
    qint16 alpha;
    qint16 beta;
};

struct Node {
    GameCondition condition;
    QVector<bool> openNodes;
    QVector<Node> childNodes;
    std::shared_ptr<Node> parentNode;
    void addNode(const Node& node);
};

#endif // NODE_H
