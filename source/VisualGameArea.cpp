#include "VisualGameArea.h"

VisualGameArea::VisualGameArea(const GameScene& scene) :
    scene(scene),
    layout(std::make_unique<QGridLayout>()) {
    setLayout(layout.get());
}

void VisualGameArea::setGameEngine(GameEngine* engine) {
    this->engine = engine;
}

void VisualGameArea::update() {
    if (scene.getGameConditionMembers().getMovement() == Movement::Horizontal) {
        uint8_t x = scene.getGameConditionMembers().getPosition().first;
        for (int i = 0; i < cells.size(); i++) {
            cells[x][i]->awake();
            connect(cells[x][i], &QPushButton::clicked, this, &VisualGameArea::onClick);
        }
    }
    else {
        uint8_t y = scene.getGameConditionMembers().getPosition().second;
        for (int i = 0; i < cells.size(); i++) {
            cells[i][y]->awake();
            connect(cells[i][y], &QPushButton::clicked, this, &VisualGameArea::onClick);
        }
    }
}

void VisualGameArea::diactivateCells() {
    if (scene.getGameConditionMembers().getMovement() == Movement::Horizontal) {
        uint8_t x = scene.getGameConditionMembers().getPosition().first;
        for (int i = 0; i < cells.size(); i++) {
            cells[x][i]->diactivate();
            disconnect(cells[x][i], &QPushButton::clicked, this, &VisualGameArea::onClick);
        }
    }
    else {
        uint8_t y = scene.getGameConditionMembers().getPosition().second;
        for (int i = 0; i < cells.size(); i++) {
            cells[i][y]->diactivate();
            disconnect(cells[i][y], &QPushButton::clicked, this, &VisualGameArea::onClick);
        }
    }
}

void VisualGameArea::clear() {
    cells.clear();

    QLayoutItem *item;
    while(item = layout->takeAt(0)) {
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void VisualGameArea::reset() {
    clear();
    auto& boardCells = scene.getBoard().getBoard();
    int size = scene.getBoard().getSize();
    cells.resize(size);
    for (int i = 0; i < size; i++) {
        cells[i].resize(size);
    }
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j] = new BoardCell(boardCells[i][j], scene.getGameConditionMembers());
            layout->addWidget(cells[i][j], i, j);
        }
    }
}

void VisualGameArea::receivePosition(std::pair<uint8_t, uint8_t> position) {
    cells[position.first][position.second]->update();
}

void VisualGameArea::onClick() {
    if (scene.getGameConditionMembers().getTurn() == GameTurn::AITurn) {
        return;
    }
    BoardCell* visualCell = qobject_cast<BoardCell*>(sender());
    engine->cellSelected(visualCell->cell.getPosition());
}
