#include "VolumeAdjust.h"
#include "ui_volumeAdjust.h"

VolumeAdjust::VolumeAdjust(MainWindow* mainWindow) :
    QDialog{},
    m_mainWindow{ mainWindow },
    ui(new Ui::VolumeAdjust)
{
    ui->setupUi(this);

    ui->volume->setValue(m_mainWindow->scene->getVolume());
}


VolumeAdjust::~VolumeAdjust() {
    delete ui;
}

void VolumeAdjust::on_mute_clicked(bool checked) {
    m_mainWindow->mute(checked);
}

void VolumeAdjust::on_volume_sliderMoved(int value) {
    m_mainWindow->setVolume(value);
};
