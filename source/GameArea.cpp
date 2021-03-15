#include "GameArea.h"

GameArea::GameArea(const GameScene& scene) :
    scene(scene),
    layout(std::make_unique<QGridLayout>()) {
    setLayout(layout.get());
}

void GameArea::setGameEngine(IGameEngine* engine) {
    this->engine = engine;
}

void GameArea::update() {
    if (scene.getGameConditionMembers().getMovement() == Movement::Horizontal) {
        quint8 x = scene.getGameConditionMembers().getPosition().first;
        for (int i = 0; i < cells.size(); i++) {
            cells[x][i]->awake();
            connect(cells[x][i], &QPushButton::clicked, this, &GameArea::onClick);
        }
    }
    else {
        quint8 y = scene.getGameConditionMembers().getPosition().second;
        for (int i = 0; i < cells.size(); i++) {
            cells[i][y]->awake();
            connect(cells[i][y], &QPushButton::clicked, this, &GameArea::onClick);
        }
    }
}

void GameArea::diactivateCells() {
    if (scene.getGameConditionMembers().getMovement() == Movement::Horizontal) {
        quint8 x = scene.getGameConditionMembers().getPosition().first;
        for (int i = 0; i < cells.size(); i++) {
            cells[x][i]->diactivate();
            disconnect(cells[x][i], &QPushButton::clicked, this, &GameArea::onClick);
        }
    }
    else {
        quint8 y = scene.getGameConditionMembers().getPosition().second;
        for (int i = 0; i < cells.size(); i++) {
            cells[i][y]->diactivate();
            disconnect(cells[i][y], &QPushButton::clicked, this, &GameArea::onClick);
        }
    }
}

void GameArea::clear() {
    cells.clear();

    QLayoutItem *item;
    while(item = layout->takeAt(0)) {
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void GameArea::reset() {
    clear();
    auto& boardCells = scene.getBoard().getBoard();
    int size = scene.getBoard().getSize();
    cells.resize(size);
    for (int i = 0; i < size; i++) {
        cells[i].resize(size);
    }
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j] = new BoardCell(boardCells[i][j], scene.getGameConditionMembers(), *engine);
            layout->addWidget(cells[i][j], i, j);
        }
    }
}

void GameArea::receivePosition(QPair<quint8, quint8> position) {
    cells[position.first][position.second]->pressed();
}

void GameArea::onClick() {
    BoardCell* cell = qobject_cast<BoardCell*>(sender());
    cell->pressed();
}
