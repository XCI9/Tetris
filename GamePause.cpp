#include "GamePause.h"

GamePause::GamePause():
    m_background{new QGraphicsRectItem{}},
    m_text{new QGraphicsTextItem{}},
    m_hintText{new QGraphicsTextItem{}}
{
    m_background->setRect(0, 0, 300, 75);
    m_background->setBrush(Qt::black);         //filled
    m_background->setPen(QColor(128,128,128)); //outline;
    this->addToGroup(m_background);

    m_text->setPlainText("Pause");
    m_text->setDefaultTextColor(QColor(255,0,0));
    m_text->setFont(QFont("arial", 20));
    m_text->setPos((300 - m_text->boundingRect().width())/2, 0); //horizontal center
    this->addToGroup(m_text);

    m_hintText->setPlainText("Press any key to continue...");
    m_hintText->setDefaultTextColor(QColor(128,128,128));
    m_hintText->setFont(QFont("arial", 14));
    m_hintText->setPos((300 - m_hintText->boundingRect().width())/2, 30); //horizontal center
    this->addToGroup(m_hintText);

}

