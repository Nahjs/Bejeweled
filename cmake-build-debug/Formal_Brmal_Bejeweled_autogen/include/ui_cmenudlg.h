/********************************************************************************
** Form generated from reading UI file 'cmenudlg.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMENUDLG_H
#define UI_CMENUDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMenuDlg
{
public:
    QWidget *centralwidget;
    QPushButton *btn_menuToGame;
    QPushButton *btn_menuToSet;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CMenuDlg)
    {
        if (CMenuDlg->objectName().isEmpty())
            CMenuDlg->setObjectName("CMenuDlg");
        CMenuDlg->resize(256, 332);
        CMenuDlg->setMinimumSize(QSize(256, 332));
        CMenuDlg->setMaximumSize(QSize(256, 332));
        centralwidget = new QWidget(CMenuDlg);
        centralwidget->setObjectName("centralwidget");
        btn_menuToGame = new QPushButton(centralwidget);
        btn_menuToGame->setObjectName("btn_menuToGame");
        btn_menuToGame->setGeometry(QRect(80, 160, 93, 41));
        btn_menuToGame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_menuToSet = new QPushButton(centralwidget);
        btn_menuToSet->setObjectName("btn_menuToSet");
        btn_menuToSet->setGeometry(QRect(80, 60, 93, 41));
        btn_menuToSet->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        CMenuDlg->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CMenuDlg);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 256, 26));
        CMenuDlg->setMenuBar(menubar);
        statusbar = new QStatusBar(CMenuDlg);
        statusbar->setObjectName("statusbar");
        CMenuDlg->setStatusBar(statusbar);

        retranslateUi(CMenuDlg);

        QMetaObject::connectSlotsByName(CMenuDlg);
    } // setupUi

    void retranslateUi(QMainWindow *CMenuDlg)
    {
        CMenuDlg->setWindowTitle(QCoreApplication::translate("CMenuDlg", "\350\217\234\345\215\225", nullptr));
        btn_menuToGame->setText(QCoreApplication::translate("CMenuDlg", "\350\277\224\345\233\236\346\270\270\346\210\217", nullptr));
        btn_menuToSet->setText(QCoreApplication::translate("CMenuDlg", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMenuDlg: public Ui_CMenuDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMENUDLG_H
