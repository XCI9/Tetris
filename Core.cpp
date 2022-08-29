#include "Core.h"

Core::Core(){
    summonTetrominoes();
}

/// @brief clear all filled row
/// @return the number of row that cleared
int Core::clearLine() {
    int clearCount{ 0 };

    //check current tetrominoes positions if all line filled
    std::array<int,4> currentTetrominoesLine{ m_currentTetrominoes[0].y(), m_currentTetrominoes[1].y(),
                                   m_currentTetrominoes[2].y(), m_currentTetrominoes[3].y() };
    std::sort(currentTetrominoesLine.begin(), currentTetrominoesLine.end());
    for (const auto& line : currentTetrominoesLine) {
        if (std::all_of(std::execution::par_unseq,
                        m_board[line].begin(), m_board[line].end(),
                        [](Block::Type block) { return block != Block::Type::Empty; })) {
            for (int aboveRow{ line }; aboveRow > 0; aboveRow--) {
                m_board[aboveRow] = m_board[aboveRow - 1];
            }
            //fill top row with empty
            for (auto& col : m_board[0])
                col = Block::Type::Empty;
            clearCount++;
        }
    }

    //buttom row all empty
    if (std::all_of(std::execution::par_unseq,
                    m_board[m_height - 1].begin(), m_board[m_height - 1].end(),
                    [](Block::Type block) { return block == Block::Type::Empty; })) {
        m_isLastClearPerfect = true;
    }

    return clearCount;
}

/// @brief choose place to summon new tetrominoes
/// @return the position that is avaliable to put new tetrominoes, -1 if all possible places are invalid.
int Core::chooseSummonPosition() {
    int validYPosition{ -1 };
    for (int i{ 2 }; i >= 0; i--, validYPosition--) {
        validYPosition = i;
        for (auto& [x, y] : m_currentTetrominoes) {
            if (m_board[y + i + m_bufferSize-2][x] != Block::Type::Empty)
                validYPosition = -1;
        }
        if (validYPosition == i)
            return validYPosition + m_bufferSize-2;
    }

    return -1;
}

/// @brief summon new Tetrominoes
void Core::summonTetrominoes() {
    m_currentTetrominoesRotation = Rotation::Spawn;
    m_currentTetrominoesMove = QPoint(0, 0);

    while (m_blockQueue.size() < 8) {
        Block::Type nextChunk[7]{Block::Type::L, Block::Type::J, Block::Type::S, Block::Type::Z, Block::Type::T, Block::Type::I, Block::Type::O};

        //random the seven blocks
        for (int i{ 6 }; i > 0; i--) {
            std::swap(nextChunk[i], nextChunk[QRandomGenerator::global()->generate() % (i + 1)]);
            m_blockQueue.emplace_back(nextChunk[i]);
        }
        m_blockQueue.emplace_back(nextChunk[0]);
    }

    m_currentTetrominoesShape = m_blockQueue.front();
    m_blockQueue.pop_front();

    generateTetrominoes(m_currentTetrominoes, m_currentTetrominoesShape);

    m_currentTetrominoesMove.setX(m_width / 2 - 2);
    for (auto& [x, y] : m_currentTetrominoes)
        x += m_currentTetrominoesMove.x();

    int validYPosition{ chooseSummonPosition() };

    if (validYPosition != -1) {
        m_currentTetrominoesMove.ry() += validYPosition;
        for (auto& [x, y] : m_currentTetrominoes) {
            y += validYPosition;
        }
    }
    else {
        m_isGameOver = true;
    }
}

/// @brief set input tetrominoes coordinate as specify tetrominoes
/// @param newTetrominoes the coordinate to put new tetrominoes
/// @param newShape the shape of new tetraminoes
void Core::generateTetrominoes(TetrominoesCoord& newTetrominoes, const Block::Type newShape) {
    newTetrominoes = Block::coordinate[newShape];
}

bool Core::isValidPosition(const TetrominoesCoord& Tetrominoes, const QPoint& shift) const {
    for (QPoint block : Tetrominoes) {
        block += m_currentTetrominoesMove;
        if (block.x() + shift.x() < 0 || block.y() + shift.y() < 0 || block.x() + shift.x() >= m_width || block.y() + shift.y() >= m_height)
            return false;
        else if (m_board[block.y() + shift.y()][block.x() + shift.x()] != Block::Type::Empty)
            return false;
    }
    return true;
}

bool Core::isValidPreviewPosition (const TetrominoesCoord& Tetrominoes) const{
    for (const auto& [x, y] : Tetrominoes) {
        if (x < 0 || y < 0 || x >= m_width || y >= m_height)
            return false;
        else if (m_board[y][x] != Block::Type::Empty)
            return false;
    }
    return true;
}

Core::TetrominoesCoord Core::calculatePreviewPosition() const {
    TetrominoesCoord previewPosition{ m_currentTetrominoes };

    //move down until invalid
    do for (auto& [x, y] : previewPosition)
            y++;
    while (isValidPreviewPosition(previewPosition));

    //move up one block which is valid place
    for (auto& [x, y] : previewPosition)
        y--;

    return previewPosition;
}

void Core::moveRightTetrominoes() {
    for (const auto& [x, y] : m_currentTetrominoes) {
        if (x + 1 >= m_width || m_board[y][x + 1] != Block::Type::Empty)
            return;
    }

    //set new pos
    for (auto& [x, y] : m_currentTetrominoes)
        x++;
    m_lastOperation = Operation::Move;
    m_currentTetrominoesMove.rx()++;
    resetLockTimer();
}

void Core::moveLeftTetrominoes() {
    for (const auto& [x, y] : m_currentTetrominoes) {
        if (x - 1 < 0 || m_board[y][x - 1] != Block::Type::Empty)
            return;
    }

    //set new pos
    for (auto& [x, y] : m_currentTetrominoes)
        x--;
    m_lastOperation = Operation::Move;
    m_currentTetrominoesMove.rx()--;
    resetLockTimer();
}

void Core::moveDownTetrominoes(bool isSoftDrop) {
    for (const auto& [x, y] : m_currentTetrominoes) {
        if (y + 1 >= m_height || m_board[y + 1][x] != Block::Type::Empty) {
            putCurrentTetrominoes();
            return;
        }
    }

    //set new pos
    for (auto& [x, y] : m_currentTetrominoes)
        y++;
    m_currentTetrominoesMove.ry()++;
    m_lastOperation = Operation::Move;
    m_isReachFloor = false;
    if (isSoftDrop)
        addScore(1);
}

///@brief drop and lock current tetrominoes instantly
void Core::hardDrop() {
    m_isReachFloor = false;
    while (!m_isReachFloor) {
        addScore(2);
        moveDownTetrominoes();
    }
    m_isHardDrop = true;
    moveDownTetrominoes();
}

void Core::TSpinCheck(){
    m_isLastClearTSpinMini = false;
    m_isLastClearTSpin = false;

    //current block is T and operation is spin =>TSpin
    if (m_currentTetrominoesShape != Block::Type::T || m_lastOperation != Operation::Spin)
        return;

    QPoint TPosition{ m_currentTetrominoes[2] };
    int tetrominoCountAtBackCorner{};
    int tetrominoCountAtFrontCorner{};
    switch (m_currentTetrominoesRotation) {
    case Rotation::Spawn:
        //  ■
        //■ ■ ■
        if (TPosition.y() + 1 == m_height)  //at Bottom
            tetrominoCountAtBackCorner = 2;
        else {
            if (m_board[TPosition.y() + 1][TPosition.x() - 1] != Block::Type::Empty)
                tetrominoCountAtBackCorner++;
            if (m_board[TPosition.y() + 1][TPosition.x() + 1] != Block::Type::Empty)
                tetrominoCountAtBackCorner++;
        }

        if (m_board[TPosition.y() - 1][TPosition.x() - 1] != Block::Type::Empty)
            tetrominoCountAtFrontCorner++;
        if (m_board[TPosition.y() - 1][TPosition.x() + 1] != Block::Type::Empty)
            tetrominoCountAtFrontCorner++;
        break;
    case Rotation::Right:
        //■
        //■ ■
        //■
        if (TPosition.x() - 1 < 0)  //Beside Left Wall
            tetrominoCountAtBackCorner = 2;
        else {
            if (m_board[TPosition.y() - 1][TPosition.x() - 1] != Block::Type::Empty)
                tetrominoCountAtBackCorner++;
            if (m_board[TPosition.y() + 1][TPosition.x() - 1] != Block::Type::Empty)
                tetrominoCountAtBackCorner++;
        }

        if (m_board[TPosition.y() - 1][TPosition.x() + 1] != Block::Type::Empty)
            tetrominoCountAtFrontCorner++;
        if (m_board[TPosition.y() + 1][TPosition.x() + 1] != Block::Type::Empty)
            tetrominoCountAtFrontCorner++;
        break;
    case Rotation::SpawnUpSideDown:
        //■ ■ ■
        //  ■
        if (m_board[TPosition.y() - 1][TPosition.x() - 1] != Block::Type::Empty)
            tetrominoCountAtBackCorner++;
        if (m_board[TPosition.y() - 1][TPosition.x() + 1] != Block::Type::Empty)
            tetrominoCountAtBackCorner++;


        if (m_board[TPosition.y() + 1][TPosition.x() - 1] != Block::Type::Empty)
            tetrominoCountAtFrontCorner++;
        if (m_board[TPosition.y() + 1][TPosition.x() + 1] != Block::Type::Empty)
            tetrominoCountAtFrontCorner++;
        break;
    case Rotation::Left:
        //  ■
        //■ ■
        //  ■
        if (TPosition.x() + 1 == m_width)  //Beside Right Wall
            tetrominoCountAtBackCorner = 2;
        else {
            if (m_board[TPosition.y() - 1][TPosition.x() + 1] != Block::Type::Empty)
                tetrominoCountAtBackCorner++;
            if (m_board[TPosition.y() + 1][TPosition.x() + 1] != Block::Type::Empty)
                tetrominoCountAtBackCorner++;
        }

        if (m_board[TPosition.y() - 1][TPosition.x() - 1] != Block::Type::Empty)
            tetrominoCountAtFrontCorner++;
        if (m_board[TPosition.y() + 1][TPosition.x() - 1] != Block::Type::Empty)
            tetrominoCountAtFrontCorner++;
        break;
    }

    if (tetrominoCountAtFrontCorner == 2 && tetrominoCountAtBackCorner >= 1)  //T Spin
        m_isLastClearTSpin = true;
    else if (tetrominoCountAtFrontCorner >= 1 && tetrominoCountAtBackCorner == 2) { //Mini T Spin
        if(m_currentTetrominoesLastSpinMoveDistance == 3)  //T Spin
            m_isLastClearTSpin = true;
        else
            m_isLastClearTSpinMini = true;
    }

}

void Core::putCurrentTetrominoes() {
    if (!m_isReachFloor) {
        m_isReachFloor = true;
        m_lockTimer = 0;
        //m_lockTimerStartPoint = std::chrono::steady_clock::now();
        return;
    }

    if(m_isHardDrop || m_lockTimer >= m_lockDelay){
        //put current Tetrominoes
        m_isHardDrop = false;
        m_isReachFloor = false;
        m_isSwapedHoldingBlock = false;
        m_resetTimerCount = 0;
        m_lastSecondClearBackToBack = m_lastClearBackToBack;

        for (const auto& [x, y] : m_currentTetrominoes)
            m_board[y][x] = m_currentTetrominoesShape;

        m_isLastClearPerfect = false;

        TSpinCheck();

        //caluclate score
        m_lastClearLineCount = clearLine();
        const float BackToBackBonus{ m_lastClearBackToBack ? 1.5f : 1 };
        int score{};
        int sendGarbageLineCount{ 0 };
        if (m_lastClearLineCount >= 1) {
            m_isLastMoveClear = true;
            m_comboCount++;
            if (m_isLastClearTSpin) {
                switch (m_lastClearLineCount) {
                case 1: score = 800;  printf("T-Spin Single!"); break;
                case 2: score = 1200; printf("T-Spin Double!"); break;
                case 3: score = 1600; printf("T-Spin Triple!"); break;
                }

                sendGarbageLineCount += m_lastClearLineCount * 2;
                if (m_lastClearBackToBack) {
                    switch (m_lastClearLineCount) {
                    case 1: sendGarbageLineCount += 1; break;
                    case 2: sendGarbageLineCount += 2; break;
                    case 3: sendGarbageLineCount += 3; break;
                    }
                }

                addScore(static_cast<int>(score * BackToBackBonus));
                if (m_lastClearBackToBack)
                    printf(" With Back to Back.");
                printf(" +%d scores.\n", static_cast<int>(score * BackToBackBonus));
                if (m_lastClearLineCount > 0)
                    m_lastClearBackToBack = true;

                m_lastClearScore = static_cast<int>(score * BackToBackBonus);
            }
            else if (m_isLastClearTSpinMini) {
                switch (m_lastClearLineCount) {
                case 1: score = 200; printf("T-Spin Mini Single!"); break;
                case 2: score = 400; printf("T-Spin Mini Double!"); sendGarbageLineCount += 1; break;
                }

                if(m_lastClearBackToBack)
                    sendGarbageLineCount += 1;

                addScore(static_cast<int>(score * BackToBackBonus));
                if (m_lastClearBackToBack)
                    printf(" With Back to Back.");
                printf(" +%d scores.\n", static_cast<int>(score * BackToBackBonus));
                if (m_lastClearLineCount > 0)
                    m_lastClearBackToBack = true;
                m_lastClearScore = static_cast<int>(score * BackToBackBonus);
            }
            else {
                switch (m_lastClearLineCount) {
                case 1: score = 100; printf("Single!"); break;
                case 2: score = 300; sendGarbageLineCount += 1; printf("Double!"); break;
                case 3: score = 500; sendGarbageLineCount += 2; printf("Triple!"); break;
                case 4: score = 800; sendGarbageLineCount += 4; printf("Tetris!"); break;
                }

                if(m_lastClearBackToBack && m_lastClearLineCount == 3)
                    sendGarbageLineCount += 2;

                if (m_lastClearLineCount > 0) {
                    if (m_lastClearLineCount == 4) {
                        m_lastClearBackToBack = true;
                        addScore(static_cast<int>(score * BackToBackBonus));
                        m_lastClearScore = static_cast<int>(score * BackToBackBonus);
                    }
                    else {
                        m_lastClearBackToBack = false;
                        addScore(score);
                        m_lastClearScore = score;
                    }
                    if (m_lastClearBackToBack)
                        printf(" With Back to Back.");
                    printf(" +%d scores.\n", static_cast<int>(score * BackToBackBonus));
                }
            }

            if (m_isLastClearPerfect) {
                printf("Perfect clear!\n");
                sendGarbageLineCount += 10;
            }

            if (m_comboCount > 0) {
                switch (m_comboCount) {
                case 1: case 2: sendGarbageLineCount += 1; break;
                case 3: case 4: sendGarbageLineCount += 2; break;
                case 5: case 6: sendGarbageLineCount += 3; break;
                case 7: case 8: case 9: sendGarbageLineCount += 4; break;
                default: sendGarbageLineCount += 5;
                }
            }
        }
        else {
            m_comboCount = -1;
        }

        if(m_lastClearLineCount > 0)
            m_clearLineTextTimer = 0;

        m_neededClearLineBeforeLevelUp -= m_lastClearLineCount;
        if (m_neededClearLineBeforeLevelUp <= 0) {
            m_level++;
            printf("Level up! Now lvl.%d\n", m_level);
            m_neededClearLineBeforeLevelUp += m_neededClearLineBeforeLevelUp + m_levelUpGoal;
        }

        m_currentTetrominoesLastSpinMoveDistance = 0;
        summonTetrominoes();
    }
}

void Core::resetLockTimer() {
    if (m_resetTimerCount <= m_resetTimerCountLimit) {
        m_lockTimer = 0;
        //m_lockTimerStartPoint = std::chrono::steady_clock::now();
        m_resetTimerCount++;
    }
}

//rotate Right
void Core::rotateClockwise() {
    if (m_currentTetrominoesShape == Block::Type::O)
        return;

    //clear current
    for (auto& pos : m_currentTetrominoes)
        pos -= m_currentTetrominoesMove;

    //basic rotation
    TetrominoesCoord rotationPlace{ m_currentTetrominoes };
    Rotation directionAfterSpin{};
    switch (m_currentTetrominoesRotation) {
    case Rotation::Spawn:
        directionAfterSpin = Rotation::Right;
        break;
    case Rotation::Right:
        directionAfterSpin = Rotation::SpawnUpSideDown;
        break;
    case Rotation::SpawnUpSideDown:
        directionAfterSpin = Rotation::Left;
        break;
    case Rotation::Left:
        directionAfterSpin = Rotation::Spawn;
    }

    if(m_currentTetrominoesShape == Block::Type::I) [[unlikely]] {
        for (auto& block : rotationPlace) {
            block = QPoint(block.y(), block.x());
            block.setX(3 - block.x());
        }
    }
    else [[likely]] {  //LJTSZ
        for (auto& block : rotationPlace) {
            //row col reverse
            block = QPoint(block.y(), block.x());
            block.setX(2 - block.x());
        }
    }
    judgeSpinPosition(rotationPlace, directionAfterSpin, SpinDirection::Clockwise);
}

void Core::judgeSpinPosition(const TetrominoesCoord& rotationPlace, const Rotation directionAfterSpin, const SpinDirection spinDirection) {
    if (m_currentTetrominoesShape == Block::Type::I) [[unlikely]] {
        ISpinType currentRotationType{};

        if ((directionAfterSpin == Rotation::Spawn || directionAfterSpin == Rotation::Right)
            && (m_currentTetrominoesRotation == Rotation::Spawn || m_currentTetrominoesRotation == Rotation::Right))
            currentRotationType = ISpinType::SpawnToRight;
        else if ((directionAfterSpin == Rotation::Right || directionAfterSpin == Rotation::SpawnUpSideDown)
            && (m_currentTetrominoesRotation == Rotation::Right || m_currentTetrominoesRotation == Rotation::SpawnUpSideDown))
            currentRotationType = ISpinType::RightToSpawnUpSideDown;
        else if ((directionAfterSpin == Rotation::SpawnUpSideDown || directionAfterSpin == Rotation::Left)
            && (m_currentTetrominoesRotation == Rotation::SpawnUpSideDown || m_currentTetrominoesRotation == Rotation::Left))
            currentRotationType = ISpinType::SpawnUpSideDownToLeft;
        else if ((directionAfterSpin == Rotation::Left || directionAfterSpin == Rotation::Spawn)
            && (m_currentTetrominoesRotation == Rotation::Left || m_currentTetrominoesRotation == Rotation::Spawn))
            currentRotationType = ISpinType::LeftToSpawn;

        const int spinDirectionReverse{ (spinDirection == SpinDirection::Clockwise) ? 1 : -1 };

        //for position test
        for (std::size_t i{ 0 }; i < Block::ISpinTable[currentRotationType].size(); i++) {
            if (isValidPosition(rotationPlace, Block::ISpinTable[currentRotationType][i] * spinDirectionReverse)) {
                //set current
                m_currentTetrominoes = rotationPlace;
                m_currentTetrominoesRotation = directionAfterSpin;
                m_currentTetrominoesMove += Block::ISpinTable[currentRotationType][i] * spinDirectionReverse;
                for (auto& pos : m_currentTetrominoes)
                    pos += m_currentTetrominoesMove;
                m_lastOperation = Operation::Spin;
                resetLockTimer();
                return;
            }
        }
    }
    else [[likely]] {  //LJSZT
        SpinType currentRotationType{};
        if (directionAfterSpin == Rotation::Right)
            currentRotationType = SpinType::AfterSpinRight;
        else if (directionAfterSpin == Rotation::Left)
            currentRotationType = SpinType::AfterSpinLeft;
        else if (m_currentTetrominoesRotation == Rotation::Right)
            currentRotationType = SpinType::OriginalRight;
        else if (m_currentTetrominoesRotation == Rotation::Left)
            currentRotationType = SpinType::OriginalLeft;

        //for position test
        for (std::size_t i{ 0 }; i < Block::normalSpinTable[currentRotationType].size(); i++) {
            if (isValidPosition(rotationPlace, Block::normalSpinTable[currentRotationType][i])) {
                //set current
                m_currentTetrominoes = rotationPlace;
                m_currentTetrominoesRotation = directionAfterSpin;
                m_currentTetrominoesMove += Block::normalSpinTable[currentRotationType][i];
                m_currentTetrominoesLastSpinMoveDistance = 0;
                m_currentTetrominoesLastSpinMoveDistance += abs(Block::normalSpinTable[currentRotationType][i].x());
                m_currentTetrominoesLastSpinMoveDistance += abs(Block::normalSpinTable[currentRotationType][i].y());
                for (auto& pos : m_currentTetrominoes)
                    pos += m_currentTetrominoesMove;
                m_lastOperation = Operation::Spin;
                resetLockTimer();
                return;
            }
        }
    }

    //reset current
    for (auto& pos : m_currentTetrominoes)
        pos += m_currentTetrominoesMove;
}

//rotate Left
void Core::rotateCounterClockwise() {
    if (m_currentTetrominoesShape == Block::Type::O)
        return;

    //clear current
    for (auto& pos : m_currentTetrominoes)
        pos -= m_currentTetrominoesMove;

    //basic rotation
    TetrominoesCoord rotationPlace{ m_currentTetrominoes };
    Rotation directionAfterSpin{};
    switch (m_currentTetrominoesRotation) {
    case Rotation::Spawn:
        directionAfterSpin = Rotation::Left;
        break;
    case Rotation::Left:
        directionAfterSpin = Rotation::SpawnUpSideDown;
        break;
    case Rotation::SpawnUpSideDown:
        directionAfterSpin = Rotation::Right;
        break;
    case Rotation::Right:
        directionAfterSpin = Rotation::Spawn;
    }

    if(m_currentTetrominoesShape == Block::Type::I) [[unlikely]] {
        for (auto& block : rotationPlace) {
            block = QPoint(block.y(), block.x());
            block.setY(3 - block.y());
        }
    }
    else [[likely]] { //LJTSZ
        for (auto& block : rotationPlace) {
            //row col reverse
            block = QPoint(block.y(), block.x());
            block.setY(2 - block.y());
        }
    }
    judgeSpinPosition(rotationPlace, directionAfterSpin, SpinDirection::CounterClockwise);
}

void Core::holdCurrentTetrominoes() {
    //current block have been swapped
    if (m_isSwapedHoldingBlock)
        return;

    m_isReachFloor = false;
    m_currentTetrominoesMove = QPoint(0, 0);

    if (m_isHoldingTetrominoes) [[likely]] {
        m_currentTetrominoes = m_holdTetrominoes;
        m_currentTetrominoesMove.setX(m_width / 2 - 2);
        m_currentTetrominoesRotation = Rotation::Spawn;
        generateTetrominoes(m_holdTetrominoes, m_currentTetrominoesShape);
        std::swap(m_holdTetrominoesShape, m_currentTetrominoesShape);
        for (auto& [x, y] : m_currentTetrominoes)
            x += m_currentTetrominoesMove.x();

        int validYPosition{ chooseSummonPosition() };

        if (validYPosition == -1) {
            m_isGameOver = true;
            return;
        }
        m_currentTetrominoesMove.ry() += validYPosition;
        for (auto& [x, y] : m_currentTetrominoes)
            y += validYPosition;
    }
    else [[unlikely]] {
        m_isHoldingTetrominoes = true;
        generateTetrominoes(m_holdTetrominoes, m_currentTetrominoesShape);
        m_holdTetrominoesShape = m_currentTetrominoesShape;
        summonTetrominoes();
    }
    m_isSwapedHoldingBlock = true;
}

void Core::addScore(const int score) {
    m_score += score;
}

int Core::getScore() const {
    return m_score;
}

int Core::getLevel() const {
    return m_level;
}

void Core::newGame() {
    m_isGameOver = false;
    m_score = 0;
    m_level = 0;

    for (auto& row : m_board)
        for (auto& block : row)
            block = Block::Type::Empty;

    m_resetTimerCount = 0;
    m_isReachFloor = false;
    m_isHardDrop =false;

    m_neededClearLineBeforeLevelUp = m_levelUpGoal;
    m_lastClearBackToBack = false;
    m_lastSecondClearBackToBack = false;
    m_lastClearScore = 0;

    m_lastClearLineCount = 0 ;
    m_comboCount = -1;
    m_isLastClearTSpin = false;
    m_isLastClearTSpinMini = false;
    m_isLastClearPerfect = false;
    m_clearLineTextTimer = 120;

    //current block attribute
    summonTetrominoes();

    //hold block attribute
    m_isHoldingTetrominoes = false;
    m_isSwapedHoldingBlock = false;
}
