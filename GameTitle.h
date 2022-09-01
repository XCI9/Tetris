#pragma once

#include <QGraphicsTextItem>
#include <QColor>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QPen>

class GameTitle : public  QGraphicsItemGroup {
    QGraphicsRectItem* m_background;
    QGraphicsTextItem* m_title;
    QGraphicsTextItem* m_subTitle;

public:
    GameTitle();

    void setTitleText(const QString& text);

    void setSubTitleText(const QString& text);
};
