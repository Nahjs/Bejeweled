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
    QPushButton *btn_name;
    QPushButton *btn_help;
    QPushButton *btn_about;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Start)
    {
        if (Start->objectName().isEmpty())
            Start->setObjectName("Start");
        Start->resize(800, 539);
        Start->setMinimumSize(QSize(0, 0));
        Start->setMaximumSize(QSize(9999, 9999));
        Start->setStyleSheet(QString::fromUtf8("#CBejeweledDlg{\n"
"border-image: url(:/res/images/background_2.png);}"));
        centralwidget = new QWidget(Start);
        centralwidget->setObjectName("centralwidget");
        btn_startToGame = new QPushButton(centralwidget);
        btn_startToGame->setObjectName("btn_startToGame");
        btn_startToGame->setGeometry(QRect(190, 210, 131, 51));
        btn_startToGame->setStyleSheet(QString::fromUtf8("border-image: url(:/res/images/pushbotton_background.png);\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_mainToRank = new QPushButton(centralwidget);
        btn_mainToRank->setObjectName("btn_mainToRank");
        btn_mainToRank->setGeometry(QRect(190, 290, 131, 51));
        btn_mainToRank->setStyleSheet(QString::fromUtf8("border-image: url(:/res/images/pushbotton_background.png);\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_welcome = new QLabel(centralwidget);
        label_welcome->setObjectName("label_welcome");
        label_welcome->setGeometry(QRect(40, 60, 231, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217")});
        font.setPointSize(20);
        label_welcome->setFont(font);
        btn_name = new QPushButton(centralwidget);
        btn_name->setObjectName("btn_name");
        btn_name->setGeometry(QRect(280, 60, 91, 41));
        btn_name->setStyleSheet(QString::fromUtf8("border-image: url(:/res/images/pushbotton_background.png);\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_help = new QPushButton(centralwidget);
        btn_help->setObjectName("btn_help");
        btn_help->setGeometry(QRect(430, 210, 131, 51));
        btn_help->setStyleSheet(QString::fromUtf8("border-image: url(:res/images/pushbotton_background.png);\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_about = new QPushButton(centralwidget);
        btn_about->setObjectName("btn_about");
        btn_about->setGeometry(QRect(430, 290, 131, 51));
        btn_about->setStyleSheet(QString::fromUtf8("border-image: url(:/res/images/pushbotton_background.png);\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 440, 341, 51));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("image: url(:/res/images/title.png);"));
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
        label_welcome->setText(QCoreApplication::translate("Start", "\350\257\267\345\221\212\347\237\245\344\275\240\347\232\204\345\244\247\345\220\215\357\274\232", nullptr));
        btn_name->setText(QCoreApplication::translate("Start", "\350\256\276\347\275\256\345\247\223\345\220\215", nullptr));
        btn_help->setText(QCoreApplication::translate("Start", "\345\270\256\345\212\251", nullptr));
        btn_about->setText(QCoreApplication::translate("Start", "\345\205\263\344\272\216", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Start: public Ui_Start {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
