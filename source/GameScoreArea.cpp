#include "GameScoreArea.h"
#include "QVBoxLayout"

GameScoreArea::GameScoreArea(const GameScene& scene) :
    scene(scene),
    layout(std::make_unique<QHBoxLayout>()),
    playerScore(std::make_unique<QLabel>()),
    enemyScore(std::make_unique<QLabel>()),
    winStatisticLabel(std::make_unique<QLabel>()){

    setLayout(layout.get());

    QFont scoreFont("Arial", 16, QFont::Bold);

    playerScore->setStyleSheet("QLabel { color: White; }");
    playerScore->setAlignment(Qt::AlignCenter);
    playerScore->setFont(scoreFont);
    playerScore->setNum(0);

    enemyScore->setStyleSheet("QLabel { color: White; }");
    enemyScore->setAlignment(Qt::AlignCenter);
    enemyScore->setFont(scoreFont);
    enemyScore->setNum(0);

    QFont winFont("Arial", 18, QFont::Bold);

    winStatisticLabel->setStyleSheet("QLabel { color: Black; }");
    winStatisticLabel->setAlignment(Qt::AlignCenter);
    winStatisticLabel->setFont(winFont);
    winStatisticLabel->setText("0:0");

    QFont scoreTextFont("Arial", 10, QFont::Bold);

    QLabel* playerTextScore = new QLabel("Your score");
    playerTextScore->setAlignment(Qt::AlignCenter);
    playerTextScore->setFont(scoreTextFont);

    QLabel* enemyTextScore = new QLabel("Enemy score");
    enemyTextScore->setAlignment(Qt::AlignCenter);
    enemyTextScore->setFont(scoreTextFont);

    QVBoxLayout* playerScoreLayout = new QVBoxLayout();
    playerScoreLayout->setContentsMargins(0, 0, 0, 0);
    playerScoreLayout->addWidget(playerTextScore);
    playerScoreLayout->addWidget(playerScore.get());

    QVBoxLayout* enemyScoreLayout = new QVBoxLayout();
    enemyScoreLayout->setContentsMargins(0, 0, 0, 0);
    enemyScoreLayout->addWidget(enemyTextScore);
    enemyScoreLayout->addWidget(enemyScore.get());

    QGridLayout* winStatisticLayout = new QGridLayout();
    winStatisticLayout->setContentsMargins(0, 0, 0, 0);
    winStatisticLayout->addWidget(winStatisticLabel.get());

    QWidget* playerScoreWidget = new QWidget();
    playerScoreWidget->setContentsMargins(0, 0, 0, 0);
    QPalette plPal = playerScoreWidget->palette();
    plPal.setColor(QPalette::Background, QColorConstants::Svg::gray);
    playerScoreWidget->setPalette(plPal);
    playerScoreWidget->setAutoFillBackground(true);
    playerScoreWidget->setLayout(playerScoreLayout);

    QWidget* enemyScoreWidget = new QWidget();
    enemyScoreWidget->setContentsMargins(0, 0, 0, 0);
    QPalette enPal = enemyScoreWidget->palette();
    enPal.setColor(QPalette::Background, QColorConstants::Svg::gray);
    enemyScoreWidget->setPalette(enPal);
    enemyScoreWidget->setAutoFillBackground(true);
    enemyScoreWidget->setLayout(enemyScoreLayout);

    QWidget* winStatisticWidget = new QWidget();
    winStatisticWidget->setContentsMargins(0, 0, 0, 0);
    winStatisticWidget->setLayout(winStatisticLayout);

    layout->addWidget(playerScoreWidget);
    layout->addWidget(winStatisticWidget);
    layout->addWidget(enemyScoreWidget);
}

void GameScoreArea::update() {
    QString strScore = QString::number(scene.getGameConditionMembers().getAIScore());
    enemyScore->setText(strScore);
    strScore = QString::number(scene.getGameConditionMembers().getPlayerScore());
    playerScore->setText(strScore);
}

void GameScoreArea::reset() {
    QString zero = QString::number(0);
    enemyScore->setText(zero);
    playerScore->setText(zero);
}

void GameScoreArea::updateWinLabel() {
    QString playerWins = QString::number(scene.getPlayerWins());
    QString enemyWins = QString::number(scene.getEnemyWins());
    winStatisticLabel->setText(playerWins + ":" + enemyWins);
}
