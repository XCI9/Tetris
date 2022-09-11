/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionKeyBinding;
    QAction *actionVolumeAdjust;
    QAction *action_9;
    QAction *actionPause;
    QAction *actionRestart;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *menuTetris;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 650);
        MainWindow->setMinimumSize(QSize(600, 600));
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"  background : rgb(32, 32, 32);\n"
"}\n"
"\n"
"QMenuBar{\n"
"    background : rgb(32, 32, 32);\n"
"    color : rgb(208, 208, 208);\n"
"}\n"
"\n"
"/*unknown why*/\n"
"QMenuBar::item:selected{\n"
"    background : rgb(65, 65, 65);\n"
"}\n"
"\n"
"QMenu{\n"
"    background : rgb(32, 32, 32);\n"
"    color : rgb(208, 208, 208);\n"
"}\n"
"QMenu:selected{\n"
"    background : rgb(65, 65, 65);\n"
"}"));
        actionKeyBinding = new QAction(MainWindow);
        actionKeyBinding->setObjectName(QString::fromUtf8("actionKeyBinding"));
        actionVolumeAdjust = new QAction(MainWindow);
        actionVolumeAdjust->setObjectName(QString::fromUtf8("actionVolumeAdjust"));
        action_9 = new QAction(MainWindow);
        action_9->setObjectName(QString::fromUtf8("action_9"));
        actionPause = new QAction(MainWindow);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionRestart = new QAction(MainWindow);
        actionRestart->setObjectName(QString::fromUtf8("actionRestart"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setAutoFillBackground(false);
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout_3->addWidget(graphicsView);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 22));
        menuTetris = new QMenu(menubar);
        menuTetris->setObjectName(QString::fromUtf8("menuTetris"));
        menuTetris->setStyleSheet(QString::fromUtf8(":hover{\n"
"    background-color: rgb(65, 65, 65);\n"
"}"));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuTetris->menuAction());
        menubar->addAction(menu->menuAction());
        menuTetris->addAction(actionKeyBinding);
        menuTetris->addAction(actionVolumeAdjust);
        menu->addAction(actionPause);
        menu->addAction(actionRestart);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Tetris", nullptr));
        actionKeyBinding->setText(QCoreApplication::translate("MainWindow", "\346\214\211\351\215\265\347\266\201\345\256\232", nullptr));
        actionVolumeAdjust->setText(QCoreApplication::translate("MainWindow", "\351\237\263\351\207\217", nullptr));
        action_9->setText(QCoreApplication::translate("MainWindow", "\346\226\260\351\201\212\346\210\262", nullptr));
#if QT_CONFIG(shortcut)
        action_9->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPause->setText(QCoreApplication::translate("MainWindow", "\346\232\253\345\201\234", nullptr));
        actionRestart->setText(QCoreApplication::translate("MainWindow", "\351\207\215\346\226\260\351\226\213\345\247\213", nullptr));
        menuTetris->setTitle(QCoreApplication::translate("MainWindow", "\350\250\255\345\256\232", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\351\201\212\346\210\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
