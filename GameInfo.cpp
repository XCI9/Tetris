#include "GameInfo.h"

GameInfo::GameInfo():
    m_background{new QGraphicsRectItem{}},
    m_level{new QGraphicsTextItem{}},
    m_score{new QGraphicsTextItem{}}
{
    m_background->setRect(0, 0, m_unitSize * 5, m_unitSize * 3);
    m_background->setBrush(Qt::black);      //filled
    m_background->setPen(QColor(128,128,128)); //outline;
    m_background->show();
    this->addToGroup(m_background);

    m_level->setPlainText("Level  0");
    m_level->setDefaultTextColor(QColor(128,128,128));
    m_level->setFont(QFont("sans-serif", 14, 127));
    m_level->setPos(10, 10);
    m_level->show();
    this->addToGroup(m_level);

    m_score->setPlainText("Score  0");
    m_score->setDefaultTextColor(QColor(128,128,128));
    m_score->setFont(QFont("sans-serif", 14, 127));
    m_score->setPos(10, 40);
    m_score->show();
    this->addToGroup(m_score);
}

void GameInfo::update(int level, int score){
    m_level->setPlainText("Level  " + QString::number(level));
    m_score->setPlainText("Score  " + QString::number(score));
}

