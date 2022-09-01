/********************************************************************************
** Form generated from reading UI file 'keybinding.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBINDING_H
#define UI_KEYBINDING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_KeyBinding
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEditMoveL;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditMoveR;
    QLabel *label_3;
    QLineEdit *lineEditRotateClockwise1;
    QLabel *label_4;
    QLineEdit *lineEditRotateClockwise2;
    QLabel *label_5;
    QLineEdit *lineEditRotateCounterclockwise;
    QLabel *label_6;
    QLineEdit *lineEditHardDrop;
    QLabel *label_7;
    QLineEdit *lineEditMoveDown;
    QLabel *label_8;
    QLineEdit *lineEditHold;
    QLabel *label_9;
    QLineEdit *lineEditVolUp;
    QLabel *label_10;
    QLineEdit *lineEditVolDown;
    QLabel *label_11;
    QLineEdit *lineEditMute;
    QLabel *keyConflitMsg;
    QLineEdit *lineEditPause;
    QLabel *label_12;

    void setupUi(QDialog *KeyBinding)
    {
        if (KeyBinding->objectName().isEmpty())
            KeyBinding->setObjectName(QString::fromUtf8("KeyBinding"));
        KeyBinding->resize(288, 300);
        KeyBinding->setAutoFillBackground(false);
        KeyBinding->setStyleSheet(QString::fromUtf8("QLineEdit:focus{\n"
"  border : 1px solid rgb(49, 142, 253);\n"
"}"));
        buttonBox = new QDialogButtonBox(KeyBinding);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(190, 260, 81, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        lineEditMoveL = new QLineEdit(KeyBinding);
        lineEditMoveL->setObjectName(QString::fromUtf8("lineEditMoveL"));
        lineEditMoveL->setGeometry(QRect(90, 40, 41, 20));
        label = new QLabel(KeyBinding);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 40, 61, 16));
        label_2 = new QLabel(KeyBinding);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 70, 61, 16));
        lineEditMoveR = new QLineEdit(KeyBinding);
        lineEditMoveR->setObjectName(QString::fromUtf8("lineEditMoveR"));
        lineEditMoveR->setGeometry(QRect(90, 70, 41, 20));
        label_3 = new QLabel(KeyBinding);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 100, 61, 16));
        lineEditRotateClockwise1 = new QLineEdit(KeyBinding);
        lineEditRotateClockwise1->setObjectName(QString::fromUtf8("lineEditRotateClockwise1"));
        lineEditRotateClockwise1->setGeometry(QRect(90, 100, 41, 20));
        label_4 = new QLabel(KeyBinding);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 130, 61, 16));
        lineEditRotateClockwise2 = new QLineEdit(KeyBinding);
        lineEditRotateClockwise2->setObjectName(QString::fromUtf8("lineEditRotateClockwise2"));
        lineEditRotateClockwise2->setGeometry(QRect(90, 130, 41, 20));
        label_5 = new QLabel(KeyBinding);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 160, 61, 16));
        lineEditRotateCounterclockwise = new QLineEdit(KeyBinding);
        lineEditRotateCounterclockwise->setObjectName(QString::fromUtf8("lineEditRotateCounterclockwise"));
        lineEditRotateCounterclockwise->setGeometry(QRect(90, 160, 41, 20));
        label_6 = new QLabel(KeyBinding);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 190, 61, 16));
        lineEditHardDrop = new QLineEdit(KeyBinding);
        lineEditHardDrop->setObjectName(QString::fromUtf8("lineEditHardDrop"));
        lineEditHardDrop->setGeometry(QRect(90, 190, 41, 20));
        label_7 = new QLabel(KeyBinding);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(150, 40, 61, 16));
        lineEditMoveDown = new QLineEdit(KeyBinding);
        lineEditMoveDown->setObjectName(QString::fromUtf8("lineEditMoveDown"));
        lineEditMoveDown->setGeometry(QRect(210, 40, 41, 20));
        label_8 = new QLabel(KeyBinding);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(150, 70, 61, 16));
        lineEditHold = new QLineEdit(KeyBinding);
        lineEditHold->setObjectName(QString::fromUtf8("lineEditHold"));
        lineEditHold->setGeometry(QRect(210, 70, 41, 20));
        label_9 = new QLabel(KeyBinding);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(150, 100, 61, 16));
        lineEditVolUp = new QLineEdit(KeyBinding);
        lineEditVolUp->setObjectName(QString::fromUtf8("lineEditVolUp"));
        lineEditVolUp->setGeometry(QRect(210, 100, 41, 20));
        label_10 = new QLabel(KeyBinding);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(150, 130, 61, 16));
        lineEditVolDown = new QLineEdit(KeyBinding);
        lineEditVolDown->setObjectName(QString::fromUtf8("lineEditVolDown"));
        lineEditVolDown->setGeometry(QRect(210, 130, 41, 20));
        label_11 = new QLabel(KeyBinding);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(150, 160, 61, 16));
        lineEditMute = new QLineEdit(KeyBinding);
        lineEditMute->setObjectName(QString::fromUtf8("lineEditMute"));
        lineEditMute->setGeometry(QRect(210, 160, 41, 20));
        keyConflitMsg = new QLabel(KeyBinding);
        keyConflitMsg->setObjectName(QString::fromUtf8("keyConflitMsg"));
        keyConflitMsg->setEnabled(true);
        keyConflitMsg->setGeometry(QRect(100, 220, 91, 16));
        keyConflitMsg->setAutoFillBackground(false);
        keyConflitMsg->setStyleSheet(QString::fromUtf8("*{\n"
"  color : rgb(255, 0, 0)\n"
"}"));
        lineEditPause = new QLineEdit(KeyBinding);
        lineEditPause->setObjectName(QString::fromUtf8("lineEditPause"));
        lineEditPause->setGeometry(QRect(210, 190, 41, 20));
        label_12 = new QLabel(KeyBinding);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(150, 190, 61, 16));

        retranslateUi(KeyBinding);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, KeyBinding, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, KeyBinding, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(KeyBinding);
    } // setupUi

    void retranslateUi(QDialog *KeyBinding)
    {
        KeyBinding->setWindowTitle(QCoreApplication::translate("KeyBinding", "\346\214\211\351\215\265\347\266\201\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("KeyBinding", "\345\267\246\347\247\273", nullptr));
        label_2->setText(QCoreApplication::translate("KeyBinding", "\345\217\263\347\247\273", nullptr));
        label_3->setText(QCoreApplication::translate("KeyBinding", "\351\240\206\346\231\202\351\220\230\346\227\213\350\275\2111", nullptr));
        label_4->setText(QCoreApplication::translate("KeyBinding", "\351\240\206\346\231\202\351\220\230\346\227\213\350\275\2112", nullptr));
        label_5->setText(QCoreApplication::translate("KeyBinding", "\351\200\206\346\231\202\351\220\230\346\227\213\350\275\211", nullptr));
        label_6->setText(QCoreApplication::translate("KeyBinding", "\346\224\276\347\275\256", nullptr));
        label_7->setText(QCoreApplication::translate("KeyBinding", "\344\270\213\347\247\273", nullptr));
        label_8->setText(QCoreApplication::translate("KeyBinding", "\344\277\235\347\225\231", nullptr));
        label_9->setText(QCoreApplication::translate("KeyBinding", "\351\237\263\351\207\217\345\244\247", nullptr));
        label_10->setText(QCoreApplication::translate("KeyBinding", "\351\237\263\351\207\217\345\260\217", nullptr));
        label_11->setText(QCoreApplication::translate("KeyBinding", "\351\235\234\351\237\263", nullptr));
        keyConflitMsg->setText(QCoreApplication::translate("KeyBinding", "\345\277\253\346\215\267\351\215\265\344\270\215\345\217\257\351\207\215\350\244\207!", nullptr));
        label_12->setText(QCoreApplication::translate("KeyBinding", "\346\232\253\345\201\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KeyBinding: public Ui_KeyBinding {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBINDING_H
