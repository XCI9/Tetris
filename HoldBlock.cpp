#include "HoldBlock.h"

HoldBlock::HoldBlock():
    m_background{new QGraphicsRectItem{}},
    m_text{new QGraphicsTextItem{}},
    m_holdBlock{new Block::Tetrominoes{ m_unitSize }}
{
    m_background->setRect(0, 0, m_unitSize * 5, m_unitSize * 3);
    m_background->setBrush(Qt::black);      //filled
    m_background->setPen(QColor(128,128,128)); //outline;
    m_background->show();
    this->addToGroup(m_background);

    m_text->setPlainText("Hold");
    m_text->setDefaultTextColor(QColor(128,128,128));
    m_text->setFont(QFont("sans-serif", 18));
    m_text->setPos(m_unitSize * 5/2 - m_text->boundingRect().width()/2, -30); //horizontal center
    m_text->show();
    this->addToGroup(m_text);

    m_holdBlock->show();
    this->addToGroup(m_holdBlock);
}

void HoldBlock::setBlock(Block::Type type){
    m_holdBlock->setBlock(type);
}
