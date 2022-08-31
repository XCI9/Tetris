#pragma once

#include <QMainWindow>
#include <map>
#include <QAction>
#include <QString>
#include <QGraphicsView>
#include <QWindow>
#include "Tetris.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    friend class KeyBinding;
    enum class Action{
        MoveDown,
        MoveLeft,
        MoveRight,
        RotateClockwise,
        RotateClockwise2,
        RotateCounterClockwise,
        HardDrop,
        Hold,
        VolumeUp,
        VolumeDown,
        Mute,
        Pause
    };

    enumArray<Action,QShortcut*> m_action;

    Q_OBJECT

    std::map<Action, QAction*> m_keyMapping;

    Tetris* scene;

    void actionInit();

protected:
    void keyPressEvent(QKeyEvent *event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setShortcut(const Action action, const QKeySequence& key);

    QKeySequence getShortcut(const Action action) const;

    bool checkShortcutConflit(const QKeySequence& key) const;

private slots:
    void on_action_3_triggered();

private:
    Ui::MainWindow *ui;
};
