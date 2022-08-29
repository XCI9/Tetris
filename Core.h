#pragma once

#include "Block.h"

#include <array>
#include <list>
#include <execution>
#include <algorithm>
#include <ctime>
#include <QColor>
#include <QObject>
#include <QPoint>           //setX(), x(), rx()  reference x
#include <QRandomGenerator>

#include <QDebug>

class Core{
    friend class Board;
    friend class HoldBlock;
    friend class Tetris;
    friend class MainWindow;

    using SpinDirection = Block::SpinDirection;
    using SpinType = Block::SpinType;
    using ISpinType = Block::ISpinType;

    enum class Rotation : char {
        Spawn,
        Right,
        Left,
        SpawnUpSideDown
    };

    enum class Operation : bool{
        Move,
        Spin
    };

    using TetrominoesCoord = Block::TetrominoesCoord;

    //static constexpr std::chrono::milliseconds m_lockDelay{ 600 };
    static constexpr int m_lockDelay{ 36 };   //36 frames before lock
    //std::chrono::steady_clock::time_point m_lockTimerStartPoint{ std::chrono::steady_clock::now() };
    int m_lockTimer{ 0 };
    int m_resetTimerCount{};
    static constexpr  int m_resetTimerCountLimit{ 15 };
    bool m_isReachFloor{ false };
    bool m_isHardDrop{ false };

    int m_score{ 0 };
    int m_level{ 0 };
    static constexpr int m_levelUpGoal{ 10 };
    int m_neededClearLineBeforeLevelUp{ m_levelUpGoal };
    bool m_lastClearBackToBack{ false };
    bool m_lastSecondClearBackToBack{ false };
    int m_lastClearScore{ 0 };

    int m_lastClearLineCount{ 0 };
    int m_comboCount{ -1 };
    bool m_isLastClearTSpin{ false };
    bool m_isLastClearTSpinMini{ false };
    bool m_isLastClearPerfect{ false };
    bool m_isLastMoveClear{ false };
    int m_clearLineTextTimer{ 120 };

    //Board attributes
    static constexpr int m_clearLineTextLast{ 120 };
    static constexpr int m_width{ 10 };
    static constexpr int m_height{ 36 };
    static constexpr int m_bufferSize{ 16 };
    static constexpr int m_displayHeight{ m_height - m_bufferSize };
    std::array<std::array<Block::Type, m_width>, m_height> m_board{};

    //current block attribute
    TetrominoesCoord m_currentTetrominoes;
    QPoint m_currentTetrominoesMove{ 0, 0 };
    Block::Type m_currentTetrominoesShape;
    Rotation m_currentTetrominoesRotation{ Rotation::Spawn };
    int m_currentTetrominoesLastSpinMoveDistance{ 0 };
    Operation m_lastOperation{ Operation::Move };

    //hold block attribute
    bool m_isHoldingTetrominoes{ false };
    TetrominoesCoord m_holdTetrominoes;
    Block::Type m_holdTetrominoesShape;
    Rotation m_holdTetrominoesRotation;
    bool m_isSwapedHoldingBlock{ false };

    std::list<Block::Type> m_blockQueue{};

    bool m_isGameOver{ false };
    bool m_isWin{ false };
public:
    Core();

private:

    void blockInit();

    void spinTableInitial();

    /// @brief clear all filled row
    /// @return the number of row that cleared
    int clearLine();

    /// @brief choose place to summon new tetrominoes
    /// @return the position that is avaliable to put new tetrominoes, -1 if all possible places are invalid.
    int chooseSummonPosition();


    /// @brief summon new Tetrominoes
    void summonTetrominoes() ;

    /// @brief set input tetrominoes coordinate as specify tetrominoes
    /// @param newTetrominoes the coordinate to put new tetrominoes
    /// @param newShape the shape of new tetraminoes
    void generateTetrominoes(TetrominoesCoord& newTetrominoes, const Block::Type newShape);

    bool isValidPosition(const TetrominoesCoord& Tetrominoes, const QPoint& shift = QPoint(0,0)) const;

    bool isValidPreviewPosition (const TetrominoesCoord& Tetrominoes) const;

    TetrominoesCoord calculatePreviewPosition() const ;

    void moveRightTetrominoes();

    void moveLeftTetrominoes();

    void moveDownTetrominoes(bool isSoftDrop = false);

    ///@brief drop and lock current tetrominoes instantly
    void hardDrop() ;

    void putCurrentTetrominoes();

    void TSpinCheck();

    void resetLockTimer();

    //rotate Right
    void rotateClockwise();

    void judgeSpinPosition(const TetrominoesCoord& rotationPlace, const Rotation directionAfterSpin, const SpinDirection spinDirection);

    //rotate Left
    void rotateCounterClockwise();

    void holdCurrentTetrominoes();

    void addScore(const int score);

    int getScore() const;

    int getLevel() const;

    void newGame();
};
