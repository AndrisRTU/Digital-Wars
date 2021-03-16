#include "GameScene.h"

GameScene::GameScene() :
    board(std::make_unique<Board>()),
    condition(std::make_unique<GameCondition>()),
    playerWins(0),
    enemyWins(0) {

}

long long GameScene::getPlayerWins() const {
    return playerWins;
}

long long GameScene::getEnemyWins() const {
    return enemyWins;
}

void GameScene::gameEnded() {
    if (condition->getPlayerScore() > condition->getAIScore()) {
        playerWins++;
    }
    if (condition->getAIScore() > condition->getPlayerScore()) {
        enemyWins++;
    }
    condition->gameEnded();
}

void GameScene::startNewGame(NewGameState state, int8_t size) {
    board->newGame(size);
    condition->startNewGame(state, size);
}

IBoard& GameScene::getBoard() {
    return *board;
}

const IBoard& GameScene::getBoard() const {
    return *board;
}

const IGameConditionMembers& GameScene::getGameConditionMembers() const {
    return *condition;
}

IGameConditionChanger& GameScene::getGameConditionChanger() {
    return *condition;
}

const GameCondition& GameScene::getGameCondition() const {
    return *condition;
}
