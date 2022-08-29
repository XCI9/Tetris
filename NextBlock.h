#pragma once

#include "Block.h"

#include <QGraphicsTextItem>
#include <QColor>
#include <QFont>
#include <list>

class NextBlock : public  QGraphicsItemGroup {
    QGraphicsRectItem* m_background;
    QGraphicsTextItem* m_text;

    std::list<Block::Tetrominoes*> m_nextBlock;

    static constexpr float m_unitSize{ 25.f };
    static constexpr float m_blockOutlineThickness{ .5f };

    void adjustPos();

public:
    NextBlock(const std::list<Block::Type>& nextBlock);

    void addBlock(const std::list<Block::Type>& blockQueue);

};
