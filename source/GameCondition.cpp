#include "GameCondition.h"
#include "RandomGenerator.h"

GameCondition::GameCondition() :
    playerScore(0),
    AIScore(0),
    turn(GameTurn::PlayerTurn),
    movement(Movement::Vertical),
    position({0, 0}) {

}

void GameCondition::scoreChanged(int number){
    if (turn == GameTurn::AITurn) {
        AIScore += number;
    }
    else {
        playerScore += number;
    }
}

void GameCondition::gameTurnChanged(){
    if (turn == GameTurn::AITurn) {
        turn = GameTurn::PlayerTurn;
    }
    else {
        turn = GameTurn::AITurn;
    }
}

void GameCondition::movementChanged(){
    if (movement == Movement::Horizontal) {
        movement = Movement::Vertical;
    }
    else {
        movement = Movement::Horizontal;
    }
}

void GameCondition::positionChanged(QPair<quint8,quint8>position) {
    this->position = position;
}

void GameCondition::gameEnded() {
    AIScore = 0;
    playerScore = 0;
}

void GameCondition::startNewGame(NewGameState state, quint8 size) {
    if (state == NewGameState::Random) {
        if (getRandomNumber(0, 1) == 0) {
            turn = GameTurn::PlayerTurn;
        }
        else {
            turn = GameTurn::AITurn;
        }
    }
    else if (state == NewGameState::Player) {
        turn = GameTurn::PlayerTurn;
    }
    else {
        turn = GameTurn::AITurn;
    }
    if (getRandomNumber(0, 1) == 0) {
        movement = Movement::Horizontal;
    }
    else {
        movement = Movement::Vertical;
    }
    position.first = getRandomNumber(0, size - 1);
    position.second = getRandomNumber(0, size - 1);
    playerScore = 0;
    AIScore = 0;
}

int GameCondition::getPlayerScore() const {
    return playerScore;
}

int GameCondition::getAIScore() const {
    return AIScore;
}

GameTurn GameCondition::getTurn() const {
    return turn;
}

Movement GameCondition::getMovement() const {
    return movement;
}

QPair<quint8,quint8> GameCondition::getPosition() const {
    return position;
}
