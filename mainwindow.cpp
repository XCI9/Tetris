#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keybinding.h"
#include "VolumeAdjust.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , scene{ new Tetris{} }
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(scene);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setBackgroundBrush(Qt::black);
    ui->graphicsView->show();

    actionInit();

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_action_3_triggered() {
    scene->pause();
    KeyBinding keyBinding{this};
    keyBinding.installEventFilter(this);
    keyBinding.setModal(true);   //獨佔模式
    keyBinding.exec();
    scene->resume();
}

void MainWindow::on_action_7_triggered() {
    scene->pause();
    VolumeAdjust volumeAdjust{ this };
    volumeAdjust.installEventFilter(this);
    volumeAdjust.setModal(true);   //獨佔模式
    volumeAdjust.exec();
    scene->resume();
}

void MainWindow::actionInit() {
    for(auto& action : m_action)
        action = new QShortcut(this);

    setShortcut(Action::MoveDown,               Qt::Key_Down);
    setShortcut(Action::MoveLeft,               Qt::Key_Left);
    setShortcut(Action::MoveRight,              Qt::Key_Right);
    setShortcut(Action::Hold,                   Qt::Key_C);
    setShortcut(Action::HardDrop,               Qt::Key_Space);
    setShortcut(Action::RotateClockwise,        Qt::Key_Z);
    setShortcut(Action::RotateClockwise2,       Qt::Key_Up);
    setShortcut(Action::RotateCounterClockwise, Qt::Key_X);
    setShortcut(Action::VolumeUp,               Qt::Key_Equal);
    setShortcut(Action::VolumeDown,             Qt::Key_Minus);
    setShortcut(Action::Mute,                   Qt::Key_M);
    setShortcut(Action::Pause,                  Qt::Key_P);

    connect(m_action[Action::MoveDown],               &QShortcut::activated, this, [&]{scene->moveDown();});
    connect(m_action[Action::MoveLeft],               &QShortcut::activated, this, [&]{scene->moveLeft();});
    connect(m_action[Action::MoveRight],              &QShortcut::activated, this, [&]{scene->moveRight();});
    connect(m_action[Action::Hold],                   &QShortcut::activated, this, [&]{scene->hold();});
    connect(m_action[Action::HardDrop],               &QShortcut::activated, this, [&]{scene->hardDrop();});
    connect(m_action[Action::RotateClockwise],        &QShortcut::activated, this, [&]{scene->rotateClockwise();});
    connect(m_action[Action::RotateClockwise2],       &QShortcut::activated, this, [&]{scene->rotateClockwise();});
    connect(m_action[Action::RotateCounterClockwise], &QShortcut::activated, this, [&]{scene->rotateCounterClockwise();});
    connect(m_action[Action::VolumeDown],             &QShortcut::activated, this, [&]{scene->volumeDown(); });
    connect(m_action[Action::VolumeUp],               &QShortcut::activated, this, [&]{scene->volumeUp(); });
    connect(m_action[Action::Mute],                   &QShortcut::activated, this, [&]{scene->volumeMute(); });

    //for any key handle, we need to disable all shortcut temperary/
    connect(m_action[Action::Pause],                  &QShortcut::activated, this, [&]{scene->switchPlayStop(); setEnabledShortcut(false); });
    connect(scene, &Tetris::gameOverSignal, this, [&] {setEnabledShortcut(false); });
}

void MainWindow::setShortcut(const Action action, const QKeySequence& key) {
    m_action[action]->setKey(key);
}

QKeySequence MainWindow::getShortcut(const Action action) const {
    return m_action[action]->key();
}

void MainWindow::setEnabledShortcut(bool enable) {
    for (auto& shortcut : m_action)
        shortcut->setEnabled(enable);
}

bool MainWindow::checkShortcutConflit(const QKeySequence& key) const {
    for (const auto& shortcut : m_action) {
        if (key == shortcut->key())
            return true;
    }
    return false;
}

void MainWindow::setVolume(const int value) {
    scene->setVolume(value);
}

void MainWindow::mute(bool mute) {
    scene->volumeMute(mute);
};

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_F11) {
        if (this->windowState() == Qt::WindowFullScreen) {
            this->setWindowState(Qt::WindowMaximized);
            ui->menubar->show();
        }
        else {
            this->setWindowState(Qt::WindowFullScreen);
            ui->menubar->hide();
        }
    }

    if (scene->isNeedAnyKeyHandle()) {
        setEnabledShortcut(true);
        scene->anyKeyHandle();
    }
}
