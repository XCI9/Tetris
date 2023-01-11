#pragma once
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QFont>

class TitleScreen : public QGraphicsScene {
    QGraphicsTextItem* m_text;

public:
    TitleScreen();
};
