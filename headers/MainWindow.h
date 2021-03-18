#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "VisualGameArea.h"
#include "GameScoreArea.h"
#include "GameSettingsMessageBox.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public IGameStatsListener {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QWidget* window;
    QVBoxLayout* layout;
    VisualGameArea& gameArea;
    GameScoreArea& scoreArea;
    GameEngine* engine;
public:
    MainWindow(VisualGameArea& gameArea, GameScoreArea& scoreArea, QWidget *parent = nullptr);
    ~MainWindow();
    void setGameEngine(GameEngine* engine);
    virtual void updateCondition() override;
    virtual void clearCondition() override;
    virtual void newGameStarted() override;
    virtual void gameEnded() override;
};
#endif // MAINWINDOW_H
