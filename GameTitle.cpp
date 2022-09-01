#include "GameTitle.h"

GameTitle::GameTitle() :
    m_background{ new QGraphicsRectItem{} },
    m_title{ new QGraphicsTextItem{} },
    m_subTitle{ new QGraphicsTextItem{} }
{
    m_background->setRect(0, 0, 300, 75);
    m_background->setBrush(Qt::black);         //filled
    m_background->setPen(QColor(128, 128, 128)); //outline;
    this->addToGroup(m_background);

    m_title->setPlainText("title");
    m_title->setDefaultTextColor(QColor(255, 0, 0));
    m_title->setFont(QFont("arial", 20));
    m_title->setPos((300 - m_title->boundingRect().width()) / 2, 0); //horizontal center
    this->addToGroup(m_title);

    m_subTitle->setPlainText("sub title");
    m_subTitle->setDefaultTextColor(QColor(128, 128, 128));
    m_subTitle->setFont(QFont("arial", 14));
    m_subTitle->setPos((300 - m_subTitle->boundingRect().width()) / 2, 30); //horizontal center
    this->addToGroup(m_subTitle);
}

void GameTitle::setTitleText(const QString& text) {
    m_title->setPlainText(text);
    m_title->setPos((300 - m_title->boundingRect().width()) / 2, 0); //horizontal center
};

void GameTitle::setSubTitleText(const QString& text) {
    m_subTitle->setPlainText(text);
    m_subTitle->setPos((300 - m_subTitle->boundingRect().width()) / 2, 30); //horizontal center
};
