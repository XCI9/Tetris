#pragma once

#include "Board.h"
#include "Core.h"
#include "HoldBlock.h"
#include "NextBlock.h"
#include "GameInfo.h"
#include "ClearText.h"
#include "Timer.h"
#include "GameTitle.h"
#include "Bgm.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QShortcut>
#include <QKeySequence>

class Tetris : public QGraphicsScene{
    Q_OBJECT

    friend class MainWindow;

    Core m_core;
    Board* m_board;
    HoldBlock* m_holdBlock;
    NextBlock* m_nextBlock;
    GameInfo* m_gameInfo;
    ClearText* m_clearText;
    GameTitle* m_gameTitle;

    Timer* m_timer;
    int m_counter{ 0 };

    Bgm* m_bgm;

    static constexpr float m_speed[]{ 0.01667f, 0.021017f, 0.026977f, 0.035256f, 0.04693f, 0.06361f, 0.0879f, 0.1236f, 0.1775f, 0.2598f,
                        0.388f, 0.59f, 0.92f, 1.46f, 2.36f, 3.91f, 6.61f, 11.43f, 20.f };
    char m_currentSpeed{ 0 };

    bool m_isPauseByUser{ false };

    void update();

    //void keyPressEvent(QKeyEvent* event);

    void tick();

signals:
    void gameOverSignal();

public:
    void moveDown();

    void moveRight();

    void moveLeft();

    void rotateClockwise();

    void rotateCounterClockwise();

    void hardDrop();

    void hold();

    void pause();

    void resume();

    void volumeUp();

    void volumeDown();

    void volumeMute();

    void volumeMute(bool mute);

    int getVolume() const;

    void setVolume(const int value);

    void switchPlayStop();

    void gameOver();

    bool isNeedAnyKeyHandle();

    void anyKeyHandle();

    Tetris();
};
