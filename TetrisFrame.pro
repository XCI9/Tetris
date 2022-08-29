QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Block.cpp \
    Board.cpp \
    ClearText.cpp \
    Core.cpp \
    GameInfo.cpp \
    GamePause.cpp \
    HoldBlock.cpp \
    NextBlock.cpp \
    Tetris.cpp \
    keybinding.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Block.h \
    Board.h \
    ClearText.h \
    Core.h \
    EnumArray.h \
    GameInfo.h \
    GamePause.h \
    HoldBlock.h \
    NextBlock.h \
    Tetris.h \
    Timer.h \
    keybinding.h \
    magic_enum.hpp \
    mainwindow.h

FORMS += \
    keybinding.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
