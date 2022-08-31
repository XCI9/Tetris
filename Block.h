#pragma once

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QPoint>
#include <QColor>
#include <array>

#include "EnumArray.h"

namespace Block{
    enum class Type{
        Empty,
        //■ ■ ■
        //■
        J,
        //■
        //■ ■ ■
        L,
        //  ■ ■
        //■ ■
        S,
        //■ ■
        //  ■ ■
        Z,
        //  ■
        //■ ■ ■
        T,
        //■ ■ ■ ■
        I,
        //■ ■
        //■ ■
        O,
        Preview,
        Garbage
    };

    using enum Type;

    enum class SpinDirection : bool{
        Clockwise,
        CounterClockwise,
    };

    enum class SpinType : char{
        OriginalLeft,
        OriginalRight,
        AfterSpinLeft,
        AfterSpinRight
    };

    enum class ISpinType : char{
        SpawnToRight,
        RightToSpawnUpSideDown,
        SpawnUpSideDownToLeft,
        LeftToSpawn
    };

    using TetrominoesCoord = std::array<QPoint, 4>;

    constexpr auto coordinate{ []() constexpr{
        enumArray<Type, TetrominoesCoord> coordinate;
        coordinate[Type::Empty] = {{{0, 0}, {0, 0}, {0, 0}, {0, 0} }};
        coordinate[Type::J]     = {{{0, 0}, {0, 1}, {1, 1}, {2, 1} }};
        coordinate[Type::L]     = {{{2, 0}, {0, 1}, {1, 1}, {2, 1} }};
        coordinate[Type::S]     = {{{1, 0}, {2, 0}, {0, 1}, {1, 1} }};
        coordinate[Type::Z]     = {{{0, 0}, {1, 0}, {1, 1}, {2, 1} }};
        coordinate[Type::T]     = {{{1, 0}, {0, 1}, {1, 1}, {2, 1} }};
        coordinate[Type::I]     = {{{0, 1}, {1, 1}, {2, 1}, {3, 1} }};
        coordinate[Type::O]     = {{{0, 0}, {0, 1}, {1, 0}, {1, 1} }};
        return coordinate;
    }()};

    constexpr auto color{ []() constexpr{
        enumArray<Type, QColor> color;
        color[Type::Empty]   = QColor(  0,   0,   0,   0);  //transparent
        color[Type::J]       = QColor(  0,   0, 255);
        color[Type::L]       = QColor(250, 170,   0);
        color[Type::S]       = QColor(  0, 255,   0);
        color[Type::Z]       = QColor(255,   0,   0);
        color[Type::T]       = QColor(153,   0, 255);
        color[Type::I]       = QColor(  0, 255, 255);
        color[Type::O]       = QColor(250, 255,   0);
        color[Type::Preview] = QColor( 63,  63, 63 );
        color[Type::Garbage] = QColor(150, 150, 150);
        return color;
    }()};

    using coordinateArray = std::array<QPoint, 5>;
    //Spin Table
    /*
            Test 1	Test 2	Test 3	Test 4	Test 5
    0->R	( 0, 0)	(-1, 0)	(-1,+1)	( 0,-2)	(-1,-2)
    2->R	( 0, 0) (-1, 0) (-1,+1)	( 0,-2)	(-1,-2)
    L->2	( 0, 0) (-1, 0) (-1,-1)	( 0,+2)	(-1,+2)
    L->0	( 0, 0) (-1, 0) (-1,-1)	( 0,+2)	(-1,+2)
    R->0	( 0, 0) (+1, 0)	(+1,-1)	( 0,+2)	(+1,+2)
    R->2	( 0, 0) (+1, 0) (+1,-1)	( 0,+2)	(+1,+2)
    0->L	( 0, 0) (+1, 0) (+1,+1)	( 0,-2)	(+1,-2)
    2->L	( 0, 0) (+1, 0) (+1,+1)	( 0,-2)	(+1,-2)
    */
    constexpr auto normalSpinTable{ []() constexpr {
        enumArray<SpinType,coordinateArray> spinTable;
        spinTable[SpinType::OriginalLeft  ] = {{{ 0, 0}, {-1, 0}, {-1, 1}, { 0,-2}, {-1,-2}}};
        spinTable[SpinType::OriginalRight ] = {{{ 0, 0}, { 1, 0}, { 1, 1}, { 0,-2}, { 1,-2}}};
        spinTable[SpinType::AfterSpinLeft ] = {{{ 0, 0}, { 1, 0}, { 1,-1}, { 0, 2}, { 1, 2}}};
        spinTable[SpinType::AfterSpinRight] = {{{ 0, 0}, {-1, 0}, {-1,-1}, { 0, 2}, {-1, 2}}};
        return spinTable;
    }()};

    constexpr auto ISpinTable{ []()constexpr{
        enumArray<ISpinType,coordinateArray> spinTable;
        spinTable[ISpinType::SpawnToRight          ] = {{{ 0, 0}, {-2, 0}, { 1, 0}, {-2, 1}, { 1,-2}}};
        spinTable[ISpinType::RightToSpawnUpSideDown] = {{{ 0, 0}, {-1, 0}, { 2, 0}, {-1,-2}, { 2, 1}}};
        spinTable[ISpinType::SpawnUpSideDownToLeft ] = {{{ 0, 0}, { 2, 0}, {-1, 0}, { 2,-1}, {-1, 2}}};
        spinTable[ISpinType::LeftToSpawn           ] = {{{ 0, 0}, { 1, 0}, {-2, 0}, { 1, 2}, {-2,-1}}};
        return spinTable;
    }()};



    class Tetrominoes : public QGraphicsItemGroup{
        std::array<QGraphicsRectItem*,4> m_block;
        enum Type m_currentBlock{ Type::Empty };

        const float m_unitSize;

    public:
        Tetrominoes(float unitSize);

        void setBlock(enum Type type);

        enum Type getType() const;
    };
}
