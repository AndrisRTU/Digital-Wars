#include "GameSettingsMessageBox.h"
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QPushButton>

GameSettingsMessageBox::GameSettingsMessageBox(IGameScene& newGameObject, IIngameAI& AI, IGameStatsListener& statsListener) :
    newGameObject(newGameObject),
    AI(AI),
    statsListener(statsListener) {
    QGridLayout* layout = (QGridLayout*)this->layout();

    QPushButton* start = new QPushButton();
    start->setText("Start");
    addButton(start, QMessageBox::AcceptRole);
    layout->addWidget(start, 5, 1);

    QSpacerItem* spacer = new QSpacerItem(100, 50);
    layout->addItem(spacer, 4, 1);

    QLabel* difficulty = new QLabel();
    difficulty->setText("Choose difficulty");
    layout->addWidget(difficulty, 0, 0);

    QLabel* firstTurn = new QLabel();
    firstTurn->setText("Choose who starts the game");
    layout->addWidget(firstTurn, 1, 0);

    QLabel* boardSize = new QLabel();
    boardSize->setText("Choose board size");
    layout->addWidget(boardSize, 2, 0);

    difficultyBox = std::make_unique<QComboBox>();
    connect(difficultyBox.get(), &QComboBox::currentTextChanged, this, &GameSettingsMessageBox::setDifficulty);
    difficultyBox->setEditable(true);
    difficultyBox->addItem("1", 1);
    difficultyBox->addItem("2", 2);
    difficultyBox->addItem("3", 3);
    difficultyBox->addItem("4", 4);
    difficultyBox->addItem("5", 5);
    layout->addWidget(difficultyBox.get(), 0, 1);

    firstTurnBox = std::make_unique<QComboBox>();
    connect(firstTurnBox.get(), qOverload<int>(&QComboBox::currentIndexChanged), this, &GameSettingsMessageBox::setFirstTurn);
    firstTurnBox->addItem("Random", -1);
    firstTurnBox->addItem("Player", 0);
    firstTurnBox->addItem("AI", 1);
    layout->addWidget(firstTurnBox.get(), 1, 1);

    boardSizeBox = std::make_unique<QComboBox>();
    connect(boardSizeBox.get(), qOverload<int>(&QComboBox::currentIndexChanged), this, &GameSettingsMessageBox::setBoardSize);
    boardSizeBox->addItem("5x5", 5);
    boardSizeBox->addItem("6x6", 6);
    boardSizeBox->addItem("7x7", 7);
    boardSizeBox->addItem("8x8", 8);
    layout->addWidget(boardSizeBox.get(), 2, 1);
}

void GameSettingsMessageBox::setBoardSize(int index) {
    boardSize = boardSizeBox->itemData(index).toInt();
}

void GameSettingsMessageBox::setDifficulty() {
    difficulty = difficultyBox->currentText().toInt();
    if (difficulty <= 0) {
        difficulty = 1;
    }
}

void GameSettingsMessageBox::setFirstTurn(int index) {
    firstTurn = firstTurnBox->itemData(index).toInt();
}


int GameSettingsMessageBox::getBoardSize() {
    return boardSize;
}

int GameSettingsMessageBox::getDifficulty() {
    return difficulty;
}

NewGameState GameSettingsMessageBox::getFirstTurn() {
    if (firstTurn == -1) {
        return NewGameState::Random;
    }
    if (firstTurn == 0) {
        return NewGameState::Player;
    }
    return NewGameState::AI;
}

void GameSettingsMessageBox::awake() {
    if (exec() == QMessageBox::AcceptRole) {
        newGameObject.startNewGame(getFirstTurn(), getBoardSize());
        AI.setDifficulty(getDifficulty());
        statsListener.newGameStarted();
    }
}
