#pragma once

#include "Block.h"

#include <QGraphicsTextItem>
#include <QColor>
#include <QFont>

class GameInfo : public  QGraphicsItemGroup {
    QGraphicsRectItem* m_background;
    QGraphicsTextItem* m_level;
    QGraphicsTextItem* m_score;

    static constexpr float m_unitSize{ 25.f };
    static constexpr float m_blockOutlineThickness{ .5f };

public:
    GameInfo();

    void update(int level, int score);
};
