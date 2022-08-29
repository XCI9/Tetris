#pragma once

#include "Block.h"

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <vector>

class Board : public QGraphicsItemGroup {
    friend class Tetris;

    const int m_width, m_height;
    static constexpr float m_unitSize{ 25.f };
    static constexpr float m_blockOutlineThickness{ .5f };
    std::vector<std::vector<QGraphicsRectItem*>> m_displayBoard;

    void tick();

    void displayInit();

    void update(int row, int col, Block::Type block);

public:
    Board(int, int);

    void BoardInit();
};
