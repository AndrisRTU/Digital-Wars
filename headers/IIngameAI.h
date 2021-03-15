#ifndef IINGAMEAI_H
#define IINGAMEAI_H
#include <QMetaType>

class IIngameAI {
public:
    virtual void setDifficulty(quint8 difficulty) = 0;
    virtual void makeMove() = 0;
};

#endif // IINGAMEAI_H
