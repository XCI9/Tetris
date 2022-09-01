#include "Tetris.h"

Tetris::Tetris() :
    m_core{},
    m_board{ new Board{ m_core.m_width, m_core.m_height - m_core.m_bufferSize } },
    m_holdBlock{ new HoldBlock{} },
    m_nextBlock{ new NextBlock{ m_core.m_blockQueue } },
    m_gameInfo{ new GameInfo{} },
    m_clearText{ new ClearText{} },
    m_gameTitle{ new GameTitle{} },
    m_bgm{ new Bgm{} }
{
    m_holdBlock->setPos(0, 0);
    this->addItem(m_holdBlock);

    m_nextBlock->setPos(425, 0);
    this->addItem(m_nextBlock);

    m_gameInfo->setPos(425, 425);
    this->addItem(m_gameInfo);

    m_board->setPos(150, 0);
    this->addItem(m_board);

    m_clearText->setPos(150, 0);
    this->addItem(m_clearText);

    m_gameTitle->setPos(125 + 12.5, 100);
    this->addItem(m_gameTitle);
    m_gameTitle->hide();

    update();

    //init timer
    //m_lockTimer.start();

    m_timer = new Timer{};
    connect(m_timer, &Timer::timeout, this, [&] {tick(); });

    m_timer->start(17);  //0.017s ~= 60FPS
}

//void Tetris::keyPressEvent(QKeyEvent* event){
    /*
    switch(event->key()){
    case Qt::Key_Up:
    case Qt::Key_Z:
        m_core.rotateClockwise();
        break;
    case Qt::Key_X:
        m_core.rotateCounterClockwise();
        break;
    case Qt::Key_Down:
        m_core.moveDownTetrominoes();
        break;
    case Qt::Key_Right:
        m_core.moveRightTetrominoes();
        break;
    case Qt::Key_Left:
        m_core.moveLeftTetrominoes();
        break;
    case Qt::Key_Space:
        m_core.hardDrop();
        break;
    case Qt::Key_C:
        m_core.holdCurrentTetrominoes();
        m_holdBlock->setBlock(m_core.m_holdTetrominoesShape);
        break;
    }
    update();*/
//}

void Tetris::update() {
    if (m_core.m_isGameOver) {
        gameOver();
        return;
    }

    for (int row{ 0 }; row < m_board->m_height; row++)
        for (int col{ 0 }; col < m_board->m_width; col++)
            m_board->update(row, col, m_core.m_board[row + m_core.m_bufferSize][col]);

    Block::TetrominoesCoord previewPosition{ m_core.calculatePreviewPosition() };
    for (const auto& [x, y] : previewPosition) {
        if (m_core.m_board[y][x] == Block::Type::Empty)
            if(y - m_core.m_bufferSize >= 0)
                m_board->update(y - m_core.m_bufferSize, x, Block::Type::Preview);
    }

    for (auto [x, y] : m_core.m_currentTetrominoes) {
        //x += m_core.m_currentTetrominoesMove.x();
        //y += m_core.m_currentTetrominoesMove.y();
        if (y - m_core.m_bufferSize >= 0)
            m_board->update(y - m_core.m_bufferSize, x, m_core.m_currentTetrominoesShape);
    }

    m_nextBlock->addBlock(m_core.m_blockQueue);

    //display gameInfo
    m_gameInfo->update(m_core.getLevel(), m_core.getScore());

    //display clear Text
    if (m_core.m_isLastMoveClear) {
        m_clearText->showScoreText(m_core.m_lastClearScore);
        m_clearText->showClear(m_core.m_lastClearLineCount, m_core.m_isLastClearTSpin, m_core.m_isLastClearTSpinMini);
        if (m_core.m_isLastClearPerfect)
            m_clearText->showPerfectClear();
        if (m_core.m_lastClearBackToBack && m_core.m_lastSecondClearBackToBack)
            m_clearText->showBackToBack();

        m_clearText->show();

        m_core.m_isLastMoveClear = false;
    }
}

void Tetris::tick() {
    //max speed is lvl.18
    m_currentSpeed = std::min(m_core.getLevel(), 18);

    if (m_speed[m_currentSpeed] < 1) { //many frame move once
        if (m_counter * m_speed[m_currentSpeed] > 1) {
            m_counter = 0;
            m_core.moveDownTetrominoes();
            update();
        }
    }
    else {  //1 frame move many times
        for (int i{ static_cast<int>(m_speed[m_currentSpeed]) }; i > 0; i--)
            m_core.moveDownTetrominoes();
        update();
        m_counter = 0;
    }
    m_counter++;


    //lockTimer
    if (m_core.m_lockTimer < m_core.m_lockDelay)
        m_core.m_lockTimer++;
}

void Tetris::moveDown(){
    m_core.moveDownTetrominoes();
    update();
}

void Tetris::moveRight(){
    m_core.moveRightTetrominoes();
    update();
}

void Tetris::moveLeft(){
    m_core.moveLeftTetrominoes();
    update();
}

void Tetris::rotateClockwise(){
    m_core.rotateClockwise();
    update();
}

void Tetris::rotateCounterClockwise(){
    m_core.rotateCounterClockwise();
    update();
}

void Tetris::hardDrop(){
    m_core.hardDrop();
    update();
}

void Tetris::hold(){
    m_core.holdCurrentTetrominoes();
    m_holdBlock->setBlock(m_core.m_holdTetrominoesShape);
    update();
}

void Tetris::pause(){
    m_timer->pause();
    m_gameTitle->setTitleText("Pause");
    m_gameTitle->setSubTitleText("");
    m_gameTitle->show();
}

void Tetris::resume(){
    m_timer->resume();
    m_gameTitle->hide();
}

void Tetris::volumeUp() {
    m_bgm->volumeUp();
}

void Tetris::volumeDown() {
    m_bgm->volumeDown();
};

void Tetris::volumeMute() {
    m_bgm->mute();
}

void Tetris::switchPlayStop() {
    if (m_timer->checkPause())
        resume();
    else {
        pause();
        m_gameTitle->setTitleText("Pause");
        m_gameTitle->setSubTitleText("Press P to resume.");
        m_gameTitle->show();
    }
}

void Tetris::gameOver() {
    m_timer->stop();
    m_gameTitle->setTitleText("GameOver");
    m_gameTitle->setSubTitleText("Press P to restart.");
    m_gameTitle->show();

}


