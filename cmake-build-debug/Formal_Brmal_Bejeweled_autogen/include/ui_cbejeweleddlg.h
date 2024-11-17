/********************************************************************************
** Form generated from reading UI file 'cbejeweleddlg.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CBEJEWELEDDLG_H
#define UI_CBEJEWELEDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CBejeweledDlg
{
public:
    QWidget *centralwidget;
    QPushButton *btn_mainToGame;
    QPushButton *btn_mainToRank;
    QLabel *label_welcome;
    QPushButton *btn_name;
    QPushButton *btn_help;
    QPushButton *btn_about;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CBejeweledDlg)
    {
        if (CBejeweledDlg->objectName().isEmpty())
            CBejeweledDlg->setObjectName("CBejeweledDlg");
        CBejeweledDlg->resize(800, 539);
        CBejeweledDlg->setMinimumSize(QSize(800, 539));
        CBejeweledDlg->setMaximumSize(QSize(800, 539));
        CBejeweledDlg->setStyleSheet(QString::fromUtf8("#CBejeweledDlg{\n"
"border-image: url(:/new/picture/background_2.png);}"));
        centralwidget = new QWidget(CBejeweledDlg);
        centralwidget->setObjectName("centralwidget");
        btn_mainToGame = new QPushButton(centralwidget);
        btn_mainToGame->setObjectName("btn_mainToGame");
        btn_mainToGame->setGeometry(QRect(200, 290, 131, 51));
        btn_mainToGame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_mainToRank = new QPushButton(centralwidget);
        btn_mainToRank->setObjectName("btn_mainToRank");
        btn_mainToRank->setGeometry(QRect(460, 290, 131, 51));
        btn_mainToRank->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_welcome = new QLabel(centralwidget);
        label_welcome->setObjectName("label_welcome");
        label_welcome->setGeometry(QRect(180, 110, 461, 101));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\345\275\251\344\272\221")});
        font.setPointSize(28);
        label_welcome->setFont(font);
        btn_name = new QPushButton(centralwidget);
        btn_name->setObjectName("btn_name");
        btn_name->setGeometry(QRect(330, 210, 131, 51));
        btn_name->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_help = new QPushButton(centralwidget);
        btn_help->setObjectName("btn_help");
        btn_help->setGeometry(QRect(200, 370, 131, 51));
        btn_help->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_about = new QPushButton(centralwidget);
        btn_about->setObjectName("btn_about");
        btn_about->setGeometry(QRect(460, 370, 131, 51));
        btn_about->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(220, 20, 341, 91));
        label->setStyleSheet(QString::fromUtf8("image: url(:/new/picture/title.png);"));
        CBejeweledDlg->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CBejeweledDlg);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        CBejeweledDlg->setMenuBar(menubar);
        statusbar = new QStatusBar(CBejeweledDlg);
        statusbar->setObjectName("statusbar");
        CBejeweledDlg->setStatusBar(statusbar);

        retranslateUi(CBejeweledDlg);

        QMetaObject::connectSlotsByName(CBejeweledDlg);
    } // setupUi

    void retranslateUi(QMainWindow *CBejeweledDlg)
    {
        CBejeweledDlg->setWindowTitle(QCoreApplication::translate("CBejeweledDlg", "\345\256\235\347\237\263\350\277\267\351\230\265", nullptr));
        btn_mainToGame->setText(QCoreApplication::translate("CBejeweledDlg", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        btn_mainToRank->setText(QCoreApplication::translate("CBejeweledDlg", "\346\216\222\350\241\214\346\246\234", nullptr));
        label_welcome->setText(QCoreApplication::translate("CBejeweledDlg", "\346\202\250\345\245\275\357\274\214\350\257\267\345\205\210\350\256\276\347\275\256\345\247\223\345\220\215", nullptr));
        btn_name->setText(QCoreApplication::translate("CBejeweledDlg", "\350\256\276\347\275\256\345\247\223\345\220\215", nullptr));
        btn_help->setText(QCoreApplication::translate("CBejeweledDlg", "\345\270\256\345\212\251", nullptr));
        btn_about->setText(QCoreApplication::translate("CBejeweledDlg", "\345\205\263\344\272\216", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CBejeweledDlg: public Ui_CBejeweledDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CBEJEWELEDDLG_H
