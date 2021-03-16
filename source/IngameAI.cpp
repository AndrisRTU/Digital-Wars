#include "IngameAI.h"
#include <future>

int getElementPlainVector(int x, int y, int size) {
    return x * size + y;
}

IngameAI::IngameAI(int8_t difficulty, const GameScene& scene, IGamePositionReceiver& receiver) :
    difficulty(difficulty),
    scene(scene),
    receiver(receiver),
    foresightCount(difficulty) {
}

void IngameAI::setDifficulty(int8_t difficulty) {
    this->difficulty = difficulty;
    foresightCount = difficulty;
}


int16_t IngameAI::scoreDifferenceHeuristic(const Node &node) {
    return node.condition.getAIScore() - node.condition.getPlayerScore();
}
#include <QMessageBox>
int16_t IngameAI::NodeSequenceHeuristic(const Node& node, int8_t depth) {
    if (!node.parentNode || depth == foresightCount) {
        return 0;
    }
    const Node* parentNode = node.parentNode;
    while (true) {
        if (!parentNode->parentNode) {
            break;
        }
        if (parentNode->openNodes.size() != 1) {
            return 0;
        }
        parentNode = parentNode->parentNode;
    }
    if (node.condition.getAIScore() > node.condition.getPlayerScore()) {
        return 999;
    }
    if (node.condition.getPlayerScore() > node.condition.getAIScore()) {
        return -999;
    }
}

int16_t IngameAI::minimax(const Node& node, int8_t depth, bool isMax, AlphaBetaModule alphaBeta) {
    if (node.childNodes.size() == 0) {
        return scoreDifferenceHeuristic(node) + NodeSequenceHeuristic(node, depth);
    }
    depth++;
    if (isMax) {
        int16_t bestVal = -9999;
        for (const auto& childNode : node.childNodes) {
            int16_t Heuristic = minimax(*childNode, depth, false, alphaBeta);
            bestVal = std::max(bestVal, Heuristic);
            alphaBeta.alpha = std::max(alphaBeta.alpha, Heuristic);
            if (alphaBeta.beta <= alphaBeta.alpha) {
                break;
            }
        }
        return bestVal;
    }
    else {
        int16_t bestVal = 9999;
        for (const auto& childNode : node.childNodes) {
            int16_t Heuristic = minimax(*childNode, depth, true, alphaBeta);
            bestVal = std::min(bestVal, Heuristic);
            alphaBeta.beta = std::min(alphaBeta.beta, Heuristic);
            if (alphaBeta.beta <= alphaBeta.alpha) {
                break;
            }
        }
        return bestVal;
    }
}

void IngameAI::addNode(Node& node, int8_t depth) {
    if (depth == foresightCount) {
        return;
    }
    depth++;
    const int8_t x = node.condition.getPosition().first;
    const int8_t y = node.condition.getPosition().second;
    const int8_t size = scene.getBoard().getSize();
    if (node.condition.getMovement() == Movement::Horizontal) {
        for (int8_t i = 0; i < size; i++) {
            if (node.openNodes[getElementPlainVector(x, i, size)]) {
                std::unique_ptr<Node> newNode = std::make_unique<Node>();
                newNode->openNodes = node.openNodes;
                newNode->condition = node.condition;
                newNode->addParentNode(node);
                newNode->openNodes[getElementPlainVector(x, i, size)] = false;
                const int16_t number = scene.getBoard().getBoard()[x][i].getNumber();
                newNode->condition.scoreChanged(number);
                newNode->condition.gameTurnChanged();
                newNode->condition.movementChanged();
                newNode->condition.positionChanged({x, i});
                addNode(*newNode, depth);
                node.addNode(newNode);
            }
        }
    }
    else {
        for (int8_t i = 0; i < size; i++) {
            if (node.openNodes[getElementPlainVector(i, y, size)]) {
                std::unique_ptr<Node> newNode = std::make_unique<Node>();
                newNode->openNodes = node.openNodes;
                newNode->condition = node.condition;
                newNode->addParentNode(node);
                newNode->openNodes[getElementPlainVector(i, y, size)] = false;
                const int16_t number = scene.getBoard().getBoard()[i][y].getNumber();
                newNode->condition.scoreChanged(number);
                newNode->condition.gameTurnChanged();
                newNode->condition.movementChanged();
                newNode->condition.positionChanged({i, y});
                addNode(*newNode, depth);
                node.addNode(newNode);
            }
        }
    }
}

void IngameAI::makeMove() {
    const int size = scene.getBoard().getSize();
    const auto& cells = scene.getBoard().getBoard();

    std::vector<bool> openNodes;
    openNodes.resize(size * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            openNodes[getElementPlainVector(i, j, size)] = true;
            if (cells[i][j].isSelected()) {
                openNodes[getElementPlainVector(i, j, size)] = false;
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
    std::vector<int16_t> nodeValues;
    for (const auto& availableNode : node.childNodes) {
        nodeValues.push_back(minimax(*availableNode, 0, false, {-9999, 9999}));
    }
    Position position = node.childNodes[0]->condition.getPosition();
    int16_t bestValue = nodeValues[0];

    for (int i = 0; i < node.childNodes.size(); i++) {
        if (nodeValues[i] > bestValue) {
            bestValue = nodeValues[i];
            position = node.childNodes[i]->condition.getPosition();
        }
    }

    //isWaiting.get();

    receiver.receivePosition(position);
}
