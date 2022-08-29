#include "keybinding.h"
#include "ui_keybinding.h"
#include <iostream>

KeyBinding::KeyBinding(MainWindow *mainWindow) :
    QDialog{},
    m_mainWindow{ mainWindow },
    ui(new Ui::KeyBinding)
{
    ui->setupUi(this);

    m_actionMapper[ui->lineEditMoveR] = MainWindow::Action::MoveRight;
    m_actionMapper[ui->lineEditMoveL] = MainWindow::Action::MoveLeft;
    m_actionMapper[ui->lineEditMoveDown] = MainWindow::Action::MoveDown;
    m_actionMapper[ui->lineEditRotateClockwise1] = MainWindow::Action::RotateClockwise;
    m_actionMapper[ui->lineEditRotateClockwise2] = MainWindow::Action::RotateClockwise2;
    m_actionMapper[ui->lineEditRotateCounterclockwise] = MainWindow::Action::RotateCounterClockwise;
    m_actionMapper[ui->lineEditHardDrop] = MainWindow::Action::HardDrop;
    m_actionMapper[ui->lineEditHold] = MainWindow::Action::Hold;
    m_actionMapper[ui->lineEditVolUp] = MainWindow::Action::VolumeUp;
    m_actionMapper[ui->lineEditVolDown] = MainWindow::Action::VolumeDown;
    m_actionMapper[ui->lineEditMute] = MainWindow::Action::Mute;

    for(auto& [lineEdit, action] : m_actionMapper){
        lineEdit->installEventFilter(this);
        lineEdit->setReadOnly(true);
        lineEdit->setText(m_mainWindow->getShortcut(action).toString());
    }
}

bool KeyBinding::eventFilter(QObject *obj, QEvent *event) {
    QLineEdit *qLineEdit = qobject_cast<QLineEdit*>(obj);
    if (event->type() == QEvent::FocusIn) {
        qLineEdit->setText("");
        ui->keyConflitMsg->hide();
    }
    if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent{ static_cast<QKeyEvent *>(event) };
        this->setFocus();       //unFocus current LineEdit

        //assign same key as original
        if (keyEvent->key() == m_mainWindow->getShortcut(m_actionMapper[qLineEdit])) {
            qLineEdit->setText(m_mainWindow->getShortcut(m_actionMapper[qLineEdit]).toString());
            return QObject::eventFilter(obj, event);
        }

        if (!m_mainWindow->checkShortcutConflit(keyEvent->key())) {
            m_mainWindow->setShortcut(m_actionMapper[qLineEdit], keyEvent->key());
            qLineEdit->setText(m_mainWindow->getShortcut(m_actionMapper[qLineEdit]).toString());
        }
        else {  //key conflit
            qLineEdit->setText(m_mainWindow->getShortcut(m_actionMapper[qLineEdit]).toString());
            ui->keyConflitMsg->show();
        }
    }
    return QObject::eventFilter(obj, event);
}

KeyBinding::~KeyBinding() {
    delete ui;
}
