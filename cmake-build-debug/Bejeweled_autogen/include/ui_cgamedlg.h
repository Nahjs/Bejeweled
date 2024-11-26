/********************************************************************************
** Form generated from reading UI file 'cgamedlg.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CGAMEDLG_H
#define UI_CGAMEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CGameDlg
{
public:
    QWidget *centralwidget;
    QProgressBar *progressBar_time;
    QPushButton *btn_gameToMain;
    QPushButton *pushButton_stop;
    QPushButton *btn_gameToMenu;
    QPushButton *pushButton_continue;
    QPushButton *pushButton_restart;
    QPushButton *pushButton_hint;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_cross;
    QPushButton *pushButton_boom;
    QPushButton *pushButton_color;
    QLabel *label_cross;
    QLabel *label_color;
    QLabel *label_boom;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CGameDlg)
    {
        if (CGameDlg->objectName().isEmpty())
            CGameDlg->setObjectName("CGameDlg");
        CGameDlg->setEnabled(true);
        CGameDlg->resize(642, 484);
        CGameDlg->setMinimumSize(QSize(642, 484));
        CGameDlg->setMaximumSize(QSize(642, 484));
        CGameDlg->setStyleSheet(QString::fromUtf8("#CGameDlg{\n"
"border-image: url(:/new/picture/background.bmp);}"));
        centralwidget = new QWidget(CGameDlg);
        centralwidget->setObjectName("centralwidget");
        progressBar_time = new QProgressBar(centralwidget);
        progressBar_time->setObjectName("progressBar_time");
        progressBar_time->setGeometry(QRect(20, 10, 601, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        progressBar_time->setFont(font);
        progressBar_time->setStyleSheet(QString::fromUtf8("font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        progressBar_time->setMaximum(60);
        progressBar_time->setValue(60);
        progressBar_time->setAlignment(Qt::AlignCenter);
        progressBar_time->setTextVisible(true);
        btn_gameToMain = new QPushButton(centralwidget);
        btn_gameToMain->setObjectName("btn_gameToMain");
        btn_gameToMain->setGeometry(QRect(530, 401, 93, 41));
        btn_gameToMain->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        pushButton_stop = new QPushButton(centralwidget);
        pushButton_stop->setObjectName("pushButton_stop");
        pushButton_stop->setGeometry(QRect(530, 341, 93, 41));
        pushButton_stop->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_gameToMenu = new QPushButton(centralwidget);
        btn_gameToMenu->setObjectName("btn_gameToMenu");
        btn_gameToMenu->setGeometry(QRect(530, 281, 93, 41));
        btn_gameToMenu->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        pushButton_continue = new QPushButton(centralwidget);
        pushButton_continue->setObjectName("pushButton_continue");
        pushButton_continue->setGeometry(QRect(530, 341, 93, 41));
        pushButton_continue->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        pushButton_continue->setCheckable(false);
        pushButton_continue->setAutoDefault(false);
        pushButton_restart = new QPushButton(centralwidget);
        pushButton_restart->setObjectName("pushButton_restart");
        pushButton_restart->setGeometry(QRect(530, 341, 93, 41));
        pushButton_restart->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        pushButton_hint = new QPushButton(centralwidget);
        pushButton_hint->setObjectName("pushButton_hint");
        pushButton_hint->setGeometry(QRect(530, 220, 90, 41));
        pushButton_hint->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"\n"
"font: 75 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(530, 170, 41, 41));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(580, 170, 41, 41));
        pushButton_cross = new QPushButton(centralwidget);
        pushButton_cross->setObjectName("pushButton_cross");
        pushButton_cross->setGeometry(QRect(440, 260, 41, 41));
        pushButton_cross->setStyleSheet(QString::fromUtf8("image: url(:/new/picture/cross.png);"));
        pushButton_cross->setFlat(true);
        pushButton_boom = new QPushButton(centralwidget);
        pushButton_boom->setObjectName("pushButton_boom");
        pushButton_boom->setGeometry(QRect(430, 360, 61, 51));
        pushButton_boom->setStyleSheet(QString::fromUtf8("image: url(:/new/picture/boom.png);"));
        pushButton_boom->setFlat(true);
        pushButton_color = new QPushButton(centralwidget);
        pushButton_color->setObjectName("pushButton_color");
        pushButton_color->setGeometry(QRect(430, 310, 61, 41));
        pushButton_color->setStyleSheet(QString::fromUtf8("image: url(:/new/picture/color.png);"));
        pushButton_color->setFlat(true);
        label_cross = new QLabel(centralwidget);
        label_cross->setObjectName("label_cross");
        label_cross->setGeometry(QRect(490, 260, 41, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\271\274\345\234\206")});
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setItalic(false);
        label_cross->setFont(font1);
        label_cross->setStyleSheet(QString::fromUtf8("font: 20pt \"\345\271\274\345\234\206\";"));
        label_color = new QLabel(centralwidget);
        label_color->setObjectName("label_color");
        label_color->setGeometry(QRect(490, 310, 41, 41));
        label_color->setFont(font1);
        label_color->setStyleSheet(QString::fromUtf8("font: 20pt \"\345\271\274\345\234\206\";"));
        label_boom = new QLabel(centralwidget);
        label_boom->setObjectName("label_boom");
        label_boom->setGeometry(QRect(490, 370, 41, 41));
        label_boom->setFont(font1);
        label_boom->setStyleSheet(QString::fromUtf8("font: 20pt \"\345\271\274\345\234\206\";"));
        CGameDlg->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CGameDlg);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 642, 26));
        CGameDlg->setMenuBar(menubar);
        statusbar = new QStatusBar(CGameDlg);
        statusbar->setObjectName("statusbar");
        CGameDlg->setStatusBar(statusbar);

        retranslateUi(CGameDlg);

        pushButton_continue->setDefault(false);


        QMetaObject::connectSlotsByName(CGameDlg);
    } // setupUi

    void retranslateUi(QMainWindow *CGameDlg)
    {
        CGameDlg->setWindowTitle(QCoreApplication::translate("CGameDlg", "\345\256\235\347\237\263\350\277\267\351\230\265", nullptr));
        progressBar_time->setFormat(QCoreApplication::translate("CGameDlg", " %v\347\247\222", nullptr));
        btn_gameToMain->setText(QCoreApplication::translate("CGameDlg", "\350\277\224\345\233\236\346\240\207\351\242\230", nullptr));
        pushButton_stop->setText(QCoreApplication::translate("CGameDlg", "\346\232\202\345\201\234\346\270\270\346\210\217", nullptr));
        btn_gameToMenu->setText(QCoreApplication::translate("CGameDlg", "\350\217\234\345\215\225", nullptr));
        pushButton_continue->setText(QCoreApplication::translate("CGameDlg", "\347\273\247\347\273\255\346\270\270\346\210\217", nullptr));
        pushButton_restart->setText(QCoreApplication::translate("CGameDlg", "\351\207\215\346\226\260\345\274\200\345\247\213", nullptr));
        pushButton_hint->setText(QCoreApplication::translate("CGameDlg", "\346\217\220\347\244\272", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_cross->setText(QString());
        pushButton_boom->setText(QString());
        pushButton_color->setText(QString());
        label_cross->setText(QCoreApplication::translate("CGameDlg", "0", nullptr));
        label_color->setText(QCoreApplication::translate("CGameDlg", "0", nullptr));
        label_boom->setText(QCoreApplication::translate("CGameDlg", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CGameDlg: public Ui_CGameDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CGAMEDLG_H
