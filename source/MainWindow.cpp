#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <memory>

MainWindow::MainWindow(VisualGameArea& gameArea, GameScoreArea& scoreArea, QWidget *parent) :
    gameArea(gameArea),
    scoreArea(scoreArea),
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    window(new QWidget()),
    layout(new QVBoxLayout()) {
    ui->setupUi(this);
    resize(800, 900);
    setWindowTitle("Digital Wars");
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(&scoreArea);
    layout->addWidget(&gameArea);
    window->setLayout(layout);
    setCentralWidget(window);
    scoreArea.setFixedHeight(100);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setGameEngine(GameEngine* engine) {
    this->engine = engine;
}

void MainWindow::updateCondition() {
    gameArea.update();
    scoreArea.update();
}

void MainWindow::clearCondition() {
    gameArea.diactivateCells();
}

void MainWindow::gameEnded() {
    scoreArea.updateWinLabel();
}

void MainWindow::newGameStarted() {
    scoreArea.reset();
    gameArea.reset();
    gameArea.update();
    engine->newGameStarted();
}
