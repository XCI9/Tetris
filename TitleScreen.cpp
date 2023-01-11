#include "TitleScreen.h"


TitleScreen::TitleScreen():
    m_text{ new QGraphicsTextItem{} }
{
    m_text->setPlainText("Tetris");
    m_text->setDefaultTextColor(QColor(255, 0, 0));
    m_text->setFont(QFont("arial", 18));
    m_text->setPos(100, 100); //horizontal center
    m_text->show();
};



