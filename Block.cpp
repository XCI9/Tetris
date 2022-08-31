#include "Block.h"

using namespace Block;

Tetrominoes::Tetrominoes(float unitSize) :
    m_unitSize{ unitSize }
{
    for (int i{ 0 }; i < 4; i++) {
        m_block[i] = new QGraphicsRectItem{};
        m_block[i]->setRect(0, 0, unitSize, unitSize);
        m_block[i]->setPos(unitSize, unitSize);
        m_block[i]->show();

        this->addToGroup(m_block[i]);
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
