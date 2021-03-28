#ifndef GAMESETTINGSMESSAGEBOX_H
#define GAMESETTINGSMESSAGEBOX_H
#include <QComboBox>
#include <QMessageBox>
#include "IGameSettingsBox.h"
#include "IGameScene.h"
#include "IGameStatsListener.h"
#include "IngameAI.h"

class GameSettingsMessageBox : public QMessageBox, public IGameSettingsBox {
private:
    int boardSize;
    int difficulty;
    int firstTurn;
    std::unique_ptr<QComboBox> difficultyBox;
    std::unique_ptr<QComboBox> firstTurnBox;
    std::unique_ptr<QComboBox> boardSizeBox;
    IGameScene& newGameObject;
    IngameAI& AI;
    IGameStatsListener& statsListener;
private slots:
    void setBoardSize(int index);
    void setDifficulty();
    void setFirstTurn(int index);
public:
    GameSettingsMessageBox(IGameScene& newGameObject, IngameAI& AI, IGameStatsListener& statsListener);
    int getBoardSize();
    int getDifficulty();
    NewGameState getFirstTurn();
    virtual void awake() override;
};

#endif // GAMESETTINGSMESSAGEBOX_H
