#include "NextBlock.h"

NextBlock::NextBlock(const std::list<Block::Type>& nextBlock) :
    m_background{ new QGraphicsRectItem{} },
    m_text{ new QGraphicsTextItem{} }
{
    m_background->setRect(0, 0, m_unitSize * 5, m_unitSize * 17);
    m_background->setBrush(Qt::black);      //filled
    m_background->setPen(QColor(128, 128, 128)); //outline;
    m_background->show();
    this->addToGroup(m_background);

    m_text->setPlainText("Next");
    m_text->setDefaultTextColor(QColor(128, 128, 128));
    m_text->setFont(QFont("sans-serif", 18));
    m_text->setPos(m_unitSize * 5 / 2 - m_text->boundingRect().width() / 2, -30); //horizontal center
    m_text->adjustSize();
    m_text->show();
    this->addToGroup(m_text);

    for (int i{ 0 }; const auto & block : nextBlock) {
        if (i >= 6)
            break;
        auto currentTetrominoes{ new Block::Tetrominoes{ m_unitSize } };
        currentTetrominoes->setBlock(block);
        currentTetrominoes->show();
        this->addToGroup(currentTetrominoes);
        m_nextBlock.push_back(currentTetrominoes);
        i++;
    }
    adjustPos();
}

void NextBlock::addBlock(const std::list<Block::Type>& blockQueue) {
    auto block{ blockQueue.begin() };
    auto display{ m_nextBlock.begin() };
    for (int i{ 0 }; i < 6; i++, block++, display++)
        (*display)->setBlock(*block);
}

void NextBlock::adjustPos() {
    for (int i{ 0 }; auto & block : m_nextBlock) {
        block->setY(m_unitSize * 2.5 * i);
        i++;
    }
}
