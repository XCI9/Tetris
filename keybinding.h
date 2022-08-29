#pragma once


#include "mainwindow.h"

#include <QDialog>
#include <QKeyEvent>
#include <QEvent>
#include <QLineEdit>
#include <map>

namespace Ui {
class KeyBinding;
}

class KeyBinding : public QDialog
{
    Q_OBJECT
    MainWindow* m_mainWindow;

    std::map<QLineEdit*,MainWindow::Action> m_actionMapper{};

protected:
    bool eventFilter(QObject *obj, QEvent *event);//in Dialog header

public:
    explicit KeyBinding(MainWindow* mainWindow);
    ~KeyBinding();

private:
    Ui::KeyBinding *ui;
};

