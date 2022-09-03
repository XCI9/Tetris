#pragma once

#include "mainwindow.h"

#include <QDialog>
#include <QKeyEvent>
#include <QEvent>
#include <QLineEdit>

namespace Ui {
    class VolumeAdjust;
}

class VolumeAdjust : public QDialog {
    Q_OBJECT
        
    MainWindow* m_mainWindow;

public:
    explicit VolumeAdjust(MainWindow* mainWindow);

    ~VolumeAdjust();

private slots:
    void on_volume_sliderMoved(int value);

    void on_mute_clicked(bool checked);

private:
    Ui::VolumeAdjust* ui;
};


