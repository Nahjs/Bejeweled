/********************************************************************************
** Form generated from reading UI file 'start.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_H
#define UI_START_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Start
{
public:
    QWidget *centralwidget;
    QPushButton *btn_startToGame;
    QPushButton *btn_mainToRank;
    QLabel *label_welcome;
    QPushButton *btn_help;
    QPushButton *btn_about;
    QPushButton *btn_themeChange;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Start)
    {
        if (Start->objectName().isEmpty())
            Start->setObjectName("Start");
        Start->resize(800, 539);
        centralwidget = new QWidget(Start);
        centralwidget->setObjectName("centralwidget");
        btn_startToGame = new QPushButton(centralwidget);
        btn_startToGame->setObjectName("btn_startToGame");
        btn_startToGame->setGeometry(QRect(230, 220, 91, 51));
        btn_mainToRank = new QPushButton(centralwidget);
        btn_mainToRank->setObjectName("btn_mainToRank");
        btn_mainToRank->setGeometry(QRect(160, 290, 91, 51));
        label_welcome = new QLabel(centralwidget);
        label_welcome->setObjectName("label_welcome");
        label_welcome->setGeometry(QRect(40, 60, 350, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217")});
        font.setPointSize(20);
        label_welcome->setFont(font);
        btn_help = new QPushButton(centralwidget);
        btn_help->setObjectName("btn_help");
        btn_help->setGeometry(QRect(440, 290, 91, 51));
        btn_about = new QPushButton(centralwidget);
        btn_about->setObjectName("btn_about");
        btn_about->setGeometry(QRect(310, 290, 91, 51));
        btn_themeChange = new QPushButton(centralwidget);
        btn_themeChange->setObjectName("btn_themeChange");
        btn_themeChange->setGeometry(QRect(360, 220, 91, 51));
        Start->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Start);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        Start->setMenuBar(menubar);
        statusbar = new QStatusBar(Start);
        statusbar->setObjectName("statusbar");
        Start->setStatusBar(statusbar);

        retranslateUi(Start);

        QMetaObject::connectSlotsByName(Start);
    } // setupUi

    void retranslateUi(QMainWindow *Start)
    {
        Start->setWindowTitle(QCoreApplication::translate("Start", "\345\256\235\347\237\263\350\277\267\351\230\265", nullptr));
        btn_startToGame->setText(QCoreApplication::translate("Start", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        btn_mainToRank->setText(QCoreApplication::translate("Start", "\346\216\222\350\241\214\346\246\234", nullptr));
        label_welcome->setText(QString());
        btn_help->setText(QCoreApplication::translate("Start", "\345\270\256\345\212\251", nullptr));
        btn_about->setText(QCoreApplication::translate("Start", "\345\205\263\344\272\216", nullptr));
        btn_themeChange->setText(QCoreApplication::translate("Start", "\350\256\276\347\275\256\344\270\273\351\242\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Start: public Ui_Start {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
