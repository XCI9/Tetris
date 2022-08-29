#pragma once

#include "Block.h"
#include <QGraphicsTextItem>
#include <QColor>
#include <QFont>

class HoldBlock : public  QGraphicsItemGroup {
    QGraphicsRectItem* m_background;
    QGraphicsTextItem* m_text;

    Block::Tetrominoes* m_holdBlock;

    static constexpr float m_unitSize{ 25.f };
    static constexpr float m_blockOutlineThickness{ .5f };

public:
    HoldBlock();

    void setBlock(Block::Type type);
};
