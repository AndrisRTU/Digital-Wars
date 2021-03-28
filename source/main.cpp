#include <QApplication>
#include <MainWindow.h>
#include "GameScene.h"
#include "GameScoreArea.h"
#include "VisualGameArea.h"
#include "GameEngine.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    std::unique_ptr<GameScene> scene = std::make_unique<GameScene>();
    std::unique_ptr<VisualGameArea> gameArea = std::make_unique<VisualGameArea>(*scene);
    std::unique_ptr<GameScoreArea> scoreArea = std::make_unique<GameScoreArea>(*scene);
    std::unique_ptr<MainWindow> window = std::make_unique<MainWindow>(*gameArea, *scoreArea);
    std::unique_ptr<IngameAI> AI = std::make_unique<IngameAI>(5, *scene);
    std::unique_ptr<GameSettingsMessageBox> gameSettingsBox = std::make_unique<GameSettingsMessageBox>(*scene, *AI, *window);
    std::unique_ptr<QThread> thread = std::make_unique<QThread>();
    std::unique_ptr<GameEngine> engine = std::make_unique<GameEngine>(*scene, *thread, *window, *gameSettingsBox, *gameArea);
    gameArea->setGameEngine(engine.get());
    window->setGameEngine(engine.get());

    AI->moveToThread(thread.get());
    QObject::connect(thread.get(),
                     &QThread::started,
                     AI.get(),
                     &IngameAI::calculatePosition);

    QObject::connect(AI.get(),
                     &IngameAI::positionCalculated,
                     thread.get(),
                     &QThread::quit);

    qRegisterMetaType<std::pair<uint8_t, uint8_t>>("Position");
    QObject::connect(AI.get(),
                     &IngameAI::positionCalculated,
                     engine.get(),
                     &GameEngine::cellSelected);

    window->show();
    gameSettingsBox->awake();
    return a.exec();
}
