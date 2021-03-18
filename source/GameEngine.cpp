#include "GameEngine.h"

GameEngine::GameEngine(GameScene& scene, QThread& AI, IGameStatsListener& statsListener, IGameSettingsBox& msgBox, IGamePositionReceiver& visualReceiver) :
    scene(scene),
    AI(AI),
    statsListener(statsListener),
    msgBox(msgBox),
    visualReceiver(visualReceiver) {

}

bool GameEngine::checkForMoves() {
    const std::vector<std::vector<GameCell>>& cells = scene.getBoard().getBoard();
    if (scene.getGameConditionMembers().getMovement() == Movement::Horizontal) {
        int8_t x = scene.getGameConditionMembers().getPosition().first;
        for (int i = 0; i < cells.size(); i++) {
            if (!cells[x][i].isSelected()) {
                return true;
            }
        }
    }
    else {
        int8_t y = scene.getGameConditionMembers().getPosition().second;
        for (int i = 0; i < cells.size(); i++) {
            if (!cells[i][y].isSelected()) {
                return true;
            }
        }
    }
    return false;
}

void GameEngine::cellSelected(Position position) {
    const int8_t x = position.first;
    const int8_t y = position.second;
    std::vector<std::vector<GameCell>>& cells = scene.getBoard().getBoard();
    if (cells[x][y].isSelected()) {
        return;
    }

    visualReceiver.receivePosition(position);

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
        return;
    }

    if (scene.getGameConditionMembers().getTurn() == GameTurn::AITurn) {
        AI.start();
    }
}

void GameEngine::newGameStarted() {
    if (scene.getGameConditionMembers().getTurn() == GameTurn::AITurn) {
        AI.start();
    }
}
