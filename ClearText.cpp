#include "ClearText.h"

ClearText::ClearText() :
    m_normalText{ new QGraphicsTextItem{} },
    m_perfectClearText{ new QGraphicsTextItem{} },
    m_comboText{ new QGraphicsTextItem{} },
    m_backToBackText{ new QGraphicsTextItem{} },
    m_scoreText{ new QGraphicsTextItem{} },
    m_textTimer{ new QTimeLine(2000) }
{
    //ScoreText
    m_scoreText->setPos(80, 50);
    applyAnimation(m_scoreText);
    this->addToGroup(m_scoreText);

    m_normalText->setPos(-150, 200);
    applyAnimation(m_normalText);
    this->addToGroup(m_normalText);

    m_perfectClearText->setPos(-150, 220);
    m_perfectClearText->document()->setHtml("<font color='red' font='times' size='20' >Perfect Clear</font>");
    m_perfectClearText->setVisible(false);
    applyAnimation(m_perfectClearText);
    this->addToGroup(m_perfectClearText);

    m_comboText->setPos(-150, 180);
    applyAnimation(m_comboText);
    this->addToGroup(m_comboText);

    m_backToBackText->setPos(-150, 240);
    m_backToBackText->document()->setHtml("<font color='red' font='times' size='20' >Back To Back</font>");
    m_backToBackText->setVisible(false);
    applyAnimation(m_backToBackText);
    this->addToGroup(m_backToBackText);
}

void ClearText::applyAnimation(QGraphicsTextItem* text) {
    m_textTimer->setFrameRange(0, 100);

    auto* animation{ new QGraphicsItemAnimation{} };
    animation->setItem(text);
    animation->setTimeLine(m_textTimer);

    animation->setPosAt(0.0, text->pos() + QPointF(0, 0));
    animation->setPosAt(1.0, text->pos() + QPointF(-5, -10));

    animation->setScaleAt(0.0, 1, 1);
    animation->setScaleAt(1.0, 1.1, 1.1);
    //https://stackoverflow.com/questions/5153157/passing-an-argument-to-a-slot
    connect(m_textTimer, &QTimeLine::finished, text, [text] { text->setVisible(false); });
}

void ClearText::showScoreText(int score) {
    //ScoreText
    QTextCharFormat charFormat{};
    charFormat.setFont(QFont("arial", 24, QFont::Bold));

    QPen outlinePen{ QColor(128, 128, 128), 2, Qt::SolidLine };
    charFormat.setTextOutline(outlinePen);

    m_scoreText->setPlainText("");
    auto document{ m_scoreText->document() };
    QTextCursor cursor{ document };
    cursor.insertText("+" + QString::number(score), charFormat);

    m_scoreText->setVisible(true);
}

void ClearText::showClear(int clearLineCount, bool isTSpin, bool isTSpinMini) {
    QString displayText{ [&]() -> QString {
        if (isTSpin) {
            switch (clearLineCount) {
            case 1: return " TSpin\nSingle!";
            case 2: return " TSpin\nDouble!";
            case 3: return " TSpin\nTriple!";
            }
        }
        else if (isTSpinMini) {
            switch (clearLineCount) {
            case 1: return "TSpinMini\n Single!";
            case 2: return "TSpinMini\n Double!";
            case 3: return "TSpinMini\n Triple!";
            }
        }
        else {
            switch (clearLineCount) {
            case 1: return " Single!";
            case 2: return " Double!";
            case 3: return " Triple!";
            case 4: return " Tetris!";
            }
        }
        throw "Should not reach here.\n";
    }()};
    

    m_normalText->document()->setHtml("<font color='red' font='times' size='24' >" + displayText + "</font>");
    m_normalText->setVisible(true);
}

void ClearText::showBackToBack() {
    m_backToBackText->setVisible(true);
}

void ClearText::showPerfectClear() {
    m_perfectClearText->setVisible(true);
}

void ClearText::show() {
    //restart timer
    m_textTimer->setCurrentTime(0);
    m_textTimer->start();
}
