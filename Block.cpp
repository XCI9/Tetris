#include "Block.h"

using namespace Block;

Tetrominoes::Tetrominoes(float unitSize) :
    m_unitSize{ unitSize }
{
    for (auto& block : m_block) {
        block = new QGraphicsRectItem{};
        block->setRect(0, 0, unitSize, unitSize);
        block->setPos(unitSize, unitSize);
        block->show();

        this->addToGroup(block);
    }
}

void Tetrominoes::setBlock(enum Type type) {
    m_currentBlock = type;
    for (int i{ 0 }; i < 4; i++) {
        const QPoint coord{ coordinate[type][i] };

        m_block[i]->setBrush(color[type]);

        switch (type) {
        case Type::I:
            m_block[i]->setPos(coord * m_unitSize + QPoint(m_unitSize * 0.5, 0));
            break;
        case Type::O:
            m_block[i]->setPos(coord * m_unitSize + QPoint(m_unitSize * 1.5, m_unitSize * 0.5));
            break;
        default:
            m_block[i]->setPos(coord * m_unitSize + QPoint(m_unitSize, m_unitSize * 0.5));
        }
    }
}

enum Type Tetrominoes::getType() const{
    return m_currentBlock;
}
