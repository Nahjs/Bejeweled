/********************************************************************************
** Form generated from reading UI file 'cmusicdlg.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMUSICDLG_H
#define UI_CMUSICDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMusicDlg
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QTextEdit *textEdit;
    QLabel *label;
    QToolButton *btn_path;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QPushButton *Button_exit;
    QPushButton *Button_sure;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CMusicDlg)
    {
        if (CMusicDlg->objectName().isEmpty())
            CMusicDlg->setObjectName("CMusicDlg");
        CMusicDlg->resize(610, 368);
        CMusicDlg->setMinimumSize(QSize(610, 368));
        CMusicDlg->setMaximumSize(QSize(610, 368));
        centralwidget = new QWidget(CMusicDlg);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(30, 20, 551, 121));
        groupBox->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(120, 30, 101, 19));
        radioButton->setChecked(true);
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(370, 30, 110, 19));
        textEdit = new QTextEdit(groupBox);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(70, 60, 391, 41));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 65, 51, 21));
        btn_path = new QToolButton(groupBox);
        btn_path->setObjectName("btn_path");
        btn_path->setGeometry(QRect(480, 60, 61, 41));
        btn_path->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(30, 170, 551, 80));
        groupBox_2->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setGeometry(QRect(120, 30, 110, 19));
        radioButton_3->setChecked(true);
        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName("radioButton_4");
        radioButton_4->setGeometry(QRect(370, 30, 110, 19));
        Button_exit = new QPushButton(centralwidget);
        Button_exit->setObjectName("Button_exit");
        Button_exit->setGeometry(QRect(362, 260, 121, 51));
        Button_exit->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        Button_sure = new QPushButton(centralwidget);
        Button_sure->setObjectName("Button_sure");
        Button_sure->setGeometry(QRect(110, 260, 121, 51));
        Button_sure->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        CMusicDlg->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CMusicDlg);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 610, 26));
        CMusicDlg->setMenuBar(menubar);
        statusbar = new QStatusBar(CMusicDlg);
        statusbar->setObjectName("statusbar");
        CMusicDlg->setStatusBar(statusbar);

        retranslateUi(CMusicDlg);

        QMetaObject::connectSlotsByName(CMusicDlg);
    } // setupUi

    void retranslateUi(QMainWindow *CMusicDlg)
    {
        CMusicDlg->setWindowTitle(QCoreApplication::translate("CMusicDlg", "\351\237\263\346\225\210\350\256\276\347\275\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CMusicDlg", "\350\203\214\346\231\257\351\237\263\344\271\220", nullptr));
        radioButton->setText(QCoreApplication::translate("CMusicDlg", "\345\274\200\345\220\257", nullptr));
        radioButton_2->setText(QCoreApplication::translate("CMusicDlg", "\345\205\263\351\227\255", nullptr));
        label->setText(QCoreApplication::translate("CMusicDlg", "\350\267\257\345\276\204", nullptr));
        btn_path->setText(QCoreApplication::translate("CMusicDlg", "...", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CMusicDlg", "\351\237\263\346\225\210", nullptr));
        radioButton_3->setText(QCoreApplication::translate("CMusicDlg", "\345\274\200\345\220\257", nullptr));
        radioButton_4->setText(QCoreApplication::translate("CMusicDlg", "\345\205\263\351\227\255", nullptr));
        Button_exit->setText(QCoreApplication::translate("CMusicDlg", "\350\277\224\345\233\236", nullptr));
        Button_sure->setText(QCoreApplication::translate("CMusicDlg", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMusicDlg: public Ui_CMusicDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMUSICDLG_H
