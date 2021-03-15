#include <QRandomGenerator>
#include "RandomGenerator.h"

int getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    return mersenne() % (max - min + 1) + min;
}
