/********************************************************************************
** Form generated from reading UI file 'csetdlg.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSETDLG_H
#define UI_CSETDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CSetDlg
{
public:
    QWidget *centralwidget;
    QPushButton *btn_setToMenu;
    QPushButton *btn_setToTheme;
    QPushButton *btn_setToMusic;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CSetDlg)
    {
        if (CSetDlg->objectName().isEmpty())
            CSetDlg->setObjectName("CSetDlg");
        CSetDlg->resize(256, 332);
        CSetDlg->setMinimumSize(QSize(256, 332));
        CSetDlg->setMaximumSize(QSize(256, 332));
        centralwidget = new QWidget(CSetDlg);
        centralwidget->setObjectName("centralwidget");
        btn_setToMenu = new QPushButton(centralwidget);
        btn_setToMenu->setObjectName("btn_setToMenu");
        btn_setToMenu->setGeometry(QRect(80, 190, 93, 41));
        btn_setToMenu->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_setToTheme = new QPushButton(centralwidget);
        btn_setToTheme->setObjectName("btn_setToTheme");
        btn_setToTheme->setGeometry(QRect(80, 50, 93, 41));
        btn_setToTheme->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_setToMusic = new QPushButton(centralwidget);
        btn_setToMusic->setObjectName("btn_setToMusic");
        btn_setToMusic->setGeometry(QRect(80, 120, 93, 41));
        btn_setToMusic->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        CSetDlg->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CSetDlg);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 256, 26));
        CSetDlg->setMenuBar(menubar);
        statusbar = new QStatusBar(CSetDlg);
        statusbar->setObjectName("statusbar");
        CSetDlg->setStatusBar(statusbar);

        retranslateUi(CSetDlg);

        QMetaObject::connectSlotsByName(CSetDlg);
    } // setupUi

    void retranslateUi(QMainWindow *CSetDlg)
    {
        CSetDlg->setWindowTitle(QCoreApplication::translate("CSetDlg", "\350\256\276\347\275\256", nullptr));
        btn_setToMenu->setText(QCoreApplication::translate("CSetDlg", "\350\277\224\345\233\236\350\217\234\345\215\225", nullptr));
        btn_setToTheme->setText(QCoreApplication::translate("CSetDlg", "\350\256\276\347\275\256\344\270\273\351\242\230", nullptr));
        btn_setToMusic->setText(QCoreApplication::translate("CSetDlg", "\350\256\276\347\275\256\351\237\263\346\225\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CSetDlg: public Ui_CSetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSETDLG_H
