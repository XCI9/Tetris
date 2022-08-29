#include "Board.h"

Board::Board(int width, int height):
    m_width{ width },
    m_height{ height },
    m_displayBoard(height, std::vector<QGraphicsRectItem*>(width, nullptr))
{
    BoardInit();
    //displayInit();
}

void Board::displayInit() {
    for (const auto& line : m_displayBoard)
        for (const auto& block : line)
            block->show();
}

void Board::update(int row, int col, Block::Type block) {
    m_displayBoard[row][col]->setBrush(Block::color[block]);        //filled
    m_displayBoard[row][col]->update();
}

void Board::BoardInit() {
    for (int row{ 0 }; row < m_height; row++) {
        for (int col{ 0 }; col < m_width; col++) {
            m_displayBoard[row][col] = new QGraphicsRectItem{};
            m_displayBoard[row][col]->setRect(col * m_unitSize,
                                              row * m_unitSize,
                                              m_unitSize - m_blockOutlineThickness,
                                              m_unitSize - m_blockOutlineThickness);
            m_displayBoard[row][col]->setPen(QPen(QColor(128, 128, 128)));  //outline
            this->addToGroup(m_displayBoard[row][col]);
        }
    }
}
