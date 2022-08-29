#pragma once

#include <QGraphicsTextItem>
#include <QColor>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QPen>

class GamePause : public  QGraphicsItemGroup {
    QGraphicsRectItem* m_background;
    QGraphicsTextItem* m_text;
    QGraphicsTextItem* m_hintText;

public:
    GamePause();
};
