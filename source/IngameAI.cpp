#include "IngameAI.h"
#include <future>
bool& getNode(QVector<bool>& vector, int x, int y, int size) {
    return vector[x * size + y];
}

const bool& getNode(const QVector<bool>& vector, int x, int y, int size) {
    return vector[x * size + y];
}

IngameAI::IngameAI(quint8 difficulty, const GameScene& scene, IGamePositionReceiver& receiver) :
    difficulty(difficulty),
    scene(scene),
    receiver(receiver),
    foresightCount(difficulty) {
}

void IngameAI::setDifficulty(quint8 difficulty) {
    this->difficulty = difficulty;
    foresightCount = difficulty;
}


qint16 IngameAI::scoreDifferenceHeuristic(const Node &node) {
    return node.condition.getAIScore() - node.condition.getPlayerScore();
}

qint16 IngameAI::WorstNodePlayerHeuristic(const Node& node, quint8 depth) {
    if (!node.parentNode) {
        return 0;
    }
    if (depth == 2 && node.childNodes.size() == 0) {
        if (node.condition.getPlayerScore() > node.condition.getAIScore()) {
            return -999;
        }
    }
    return 0;
}

qint16 IngameAI::BestNodeAIHeuristic(const Node& node, quint8 depth) {
    if (depth == 1 && node.childNodes.size() == 0) {
        if (node.condition.getAIScore() > node.condition.getPlayerScore()) {
            return 999;
        }
    }
    return 0;
}

qint16 IngameAI::minimax(const Node& node, quint8 depth, bool isMax, AlphaBetaModule alphaBeta) {
    depth++;
    if (node.childNodes.size() == 0) {
        return scoreDifferenceHeuristic(node) + BestNodeAIHeuristic(node, depth) + WorstNodePlayerHeuristic(node, depth);
    }
    if (isMax) {
        qint16 bestVal = -9999;
        for (const auto& childNode : node.childNodes) {
            qint16 Heuristic = minimax(childNode, depth, false, alphaBeta);
            bestVal = std::max(bestVal, Heuristic);
            alphaBeta.alpha = std::max(alphaBeta.alpha, Heuristic);
            if (alphaBeta.beta <= alphaBeta.alpha) {
                break;
            }
        }
        return bestVal;
    }
    else {
        qint16 bestVal = 9999;
        for (const auto& childNode : node.childNodes) {
            qint16 Heuristic = minimax(childNode, depth, true, alphaBeta);
            bestVal = std::min(bestVal, Heuristic);
            alphaBeta.beta = std::min(alphaBeta.beta, Heuristic);
            if (alphaBeta.beta <= alphaBeta.alpha) {
                break;
            }
        }
        return bestVal;
    }
}

void IngameAI::addNode(Node& node, quint8 depth) {
    if (depth == foresightCount) {
        return;
    }
    depth++;
    const quint8 x = node.condition.getPosition().first;
    const quint8 y = node.condition.getPosition().second;
    const quint8 size = scene.getBoard().getSize();
    if (node.condition.getMovement() == Movement::Horizontal) {
        for (quint8 i = 0; i < size; i++) {
            if (getNode(node.openNodes, x, i, size)) {
                Node newNode;
                newNode.openNodes = node.openNodes;
                newNode.condition = node.condition;
                getNode(newNode.openNodes, x, i, size) = false;
                const qint16 number = scene.getBoard().getBoard()[x][i].getNumber();
                newNode.condition.scoreChanged(number);
                newNode.condition.gameTurnChanged();
                newNode.condition.movementChanged();
                newNode.condition.positionChanged({x, i});
                addNode(newNode, depth);
                node.addNode(newNode);
            }
        }
    }
    else {
        for (quint8 i = 0; i < size; i++) {
            if (getNode(node.openNodes, i, y, size)) {
                Node newNode;
                newNode.openNodes = node.openNodes;
                newNode.condition = node.condition;
                getNode(newNode.openNodes, i, y, size) = false;
                const qint16 number = scene.getBoard().getBoard()[i][y].getNumber();
                newNode.condition.scoreChanged(number);
                newNode.condition.gameTurnChanged();
                newNode.condition.movementChanged();
                newNode.condition.positionChanged({i, y});
                addNode(newNode, depth);
                node.addNode(newNode);
            }
        }
    }
}

void IngameAI::makeMove() {
    const int size = scene.getBoard().getSize();
    const auto& cells = scene.getBoard().getBoard();

    QVector<bool> openNodes;
    openNodes.resize(size * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            getNode(openNodes, i, j, size) = true;
            if (cells[i][j].isSelected()) {
                getNode(openNodes, i, j, size) = false;
            }
        }
    }

    /*
    std::future<bool> isWaiting = std::async(std::launch::async, [](){
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        return true;
    });
    */

    Node node;
    node.parentNode = nullptr;
    node.openNodes = openNodes;
    node.condition = scene.getGameCondition();
    addNode(node, 0);
    QVector<qint16> nodeValues;
    for (const auto& availableNode : node.childNodes) {
        nodeValues.push_back(minimax(availableNode, 0, false, {-9999, 9999}));
    }
    Position position = node.childNodes[0].condition.getPosition();
    qint16 bestValue = nodeValues[0];

    for (int i = 0; i < node.childNodes.size(); i++) {
        if (nodeValues[i] > bestValue) {
            bestValue = nodeValues[i];
            position = node.childNodes[i].condition.getPosition();
        }
    }

    //isWaiting.get();

    receiver.receivePosition(position);
}
