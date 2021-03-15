#include "GameEngine.h"

GameEngine::GameEngine(GameScene& scene, IIngameAI& AI, IGameStatsListener& statsListener, IGameSettingsBox& msgBox) :
    scene(scene),
    AI(AI),
    statsListener(statsListener),
    msgBox(msgBox) {
}

bool GameEngine::checkForMoves() {
    const QVector<QVector<GameCell>>& cells = scene.getBoard().getBoard();
    if (scene.getGameConditionMembers().getMovement() == Movement::Horizontal) {
        quint8 x = scene.getGameConditionMembers().getPosition().first;
        for (int i = 0; i < cells.size(); i++) {
            if (!cells[x][i].isSelected()) {
                return true;
            }
        }
    }
    else {
        quint8 y = scene.getGameConditionMembers().getPosition().second;
        for (int i = 0; i < cells.size(); i++) {
            if (!cells[i][y].isSelected()) {
                return true;
            }
        }
    }
    return false;
}

void GameEngine::cellSelected(QPair<qint8, qint8> position) {
    const quint8 x = position.first;
    const quint8 y = position.second;
    QVector<QVector<GameCell>>& cells = scene.getBoard().getBoard();

    scene.getGameConditionChanger().scoreChanged(cells[x][y].pick());
    statsListener.clearCondition();
    scene.getGameConditionChanger().gameTurnChanged();
    scene.getGameConditionChanger().positionChanged(position);
    scene.getGameConditionChanger().movementChanged();
    statsListener.updateCondition();

    if (!checkForMoves()) {
        scene.gameEnded();
        statsListener.gameEnded();
        msgBox.awake();
    }

    if (scene.getGameConditionMembers().getTurn() == GameTurn::AITurn) {
        AI.makeMove();
    }
}

void GameEngine::newGameStarted() {
    if (scene.getGameConditionMembers().getTurn() == GameTurn::AITurn) {
        AI.makeMove();
    }
}
