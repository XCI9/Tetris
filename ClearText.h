#pragma once

#include "Block.h"

#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include <QGraphicsItemAnimation>
#include <QColor>
#include <QFont>
#include <QObject>
#include <QTextCharFormat>
#include <QTextDocument>
#include <QTextCursor>
#include <QPen>
#include <QColor>
#include <QTimeLine>
#include <QPointF>
#include <QString>

class ClearText : public QObject, public  QGraphicsItemGroup {
    Q_OBJECT

    QGraphicsTextItem* m_normalText;
    QGraphicsTextItem* m_perfectClearText;
    QGraphicsTextItem* m_comboText;
    QGraphicsTextItem* m_backToBackText;
    QGraphicsTextItem* m_scoreText;

    QTimeLine* m_textTimer;

    void applyAnimation(QGraphicsTextItem* text);

public:
    ClearText();

    void showClear(int clearLineCount, bool isTSpin, bool isTSpinMini);

    void showBackToBack();

    void showPerfectClear();

    void show();

    void showScoreText(int score);
};
