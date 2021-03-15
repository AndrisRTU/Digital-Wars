#include <QApplication>
#include <MainWindow.h>
#include "GameScene.h"
#include "GameScoreArea.h"
#include "GameArea.h"
#include "GameEngine.h"
#include "IngameAI.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    std::unique_ptr<GameScene> scene = std::make_unique<GameScene>();
    std::unique_ptr<GameArea> gameArea = std::make_unique<GameArea>(*scene);
    std::unique_ptr<GameScoreArea> scoreArea = std::make_unique<GameScoreArea>(*scene);
    std::unique_ptr<MainWindow> window = std::make_unique<MainWindow>(*gameArea, *scoreArea);
    std::unique_ptr<IngameAI> AI = std::make_unique<IngameAI>(5, *scene, *gameArea);
    std::unique_ptr<GameSettingsMessageBox> gameSettingsBox = std::make_unique<GameSettingsMessageBox>(*scene, *AI, *window);
    std::unique_ptr<GameEngine> engine = std::make_unique<GameEngine>(*scene, *AI, *window, *gameSettingsBox);
    gameArea->setGameEngine(engine.get());
    window->setGameEngine(engine.get());

    window->show();
    gameSettingsBox->awake();
    return a.exec();
}
