#ifndef GAMESTRUCTURES_H
#define GAMESTRUCTURES_H

enum class GameTurn {
    PlayerTurn,
    AITurn
};

enum class NewGameState {
    Random,
    Player,
    AI
};

enum class Movement {
    Horizontal,
    Vertical
};

#endif // GAMESTRUCTURES_H
