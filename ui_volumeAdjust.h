/********************************************************************************
** Form generated from reading UI file 'volumeAdjust.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLUMEADJUST_H
#define UI_VOLUMEADJUST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_VolumeAdjust
{
public:
    QSlider *volume;
    QLabel *label;
    QLabel *label_2;
    QCheckBox *mute;

    void setupUi(QDialog *VolumeAdjust)
    {
        if (VolumeAdjust->objectName().isEmpty())
            VolumeAdjust->setObjectName(QString::fromUtf8("VolumeAdjust"));
        VolumeAdjust->resize(222, 100);
        volume = new QSlider(VolumeAdjust);
        volume->setObjectName(QString::fromUtf8("volume"));
        volume->setGeometry(QRect(30, 30, 151, 20));
        volume->setOrientation(Qt::Horizontal);
        label = new QLabel(VolumeAdjust);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 16, 20));
        label_2 = new QLabel(VolumeAdjust);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(190, 30, 21, 16));
        mute = new QCheckBox(VolumeAdjust);
        mute->setObjectName(QString::fromUtf8("mute"));
        mute->setGeometry(QRect(10, 60, 79, 20));

        retranslateUi(VolumeAdjust);

        QMetaObject::connectSlotsByName(VolumeAdjust);
    } // setupUi

    void retranslateUi(QDialog *VolumeAdjust)
    {
        VolumeAdjust->setWindowTitle(QCoreApplication::translate("VolumeAdjust", "Volume", nullptr));
        label->setText(QCoreApplication::translate("VolumeAdjust", "0", nullptr));
        label_2->setText(QCoreApplication::translate("VolumeAdjust", "100", nullptr));
        mute->setText(QCoreApplication::translate("VolumeAdjust", "Mute", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VolumeAdjust: public Ui_VolumeAdjust {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLUMEADJUST_H
