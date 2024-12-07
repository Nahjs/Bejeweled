/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName("About");
        About->resize(432, 364);
        About->setMinimumSize(QSize(432, 364));
        About->setMaximumSize(QSize(432, 364));
        About->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(About);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 20, 391, 291));
        groupBox->setStyleSheet(QString::fromUtf8("font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 50, 71, 31));
        label->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 50, 71, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(0, 0, 255);"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 100, 71, 41));
        label_3->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(120, 110, 141, 31));
        label_4->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(0, 0, 255);"));
        label_4->setTextFormat(Qt::PlainText);
        label_4->setWordWrap(true);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 160, 71, 51));
        label_5->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(130, 170, 61, 31));
        label_6->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(0, 0, 255);"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 220, 101, 51));
        label_7->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(120, 230, 171, 31));
        label_8->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(0, 0, 255);"));
        About->setCentralWidget(centralwidget);
        menubar = new QMenuBar(About);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 432, 22));
        About->setMenuBar(menubar);
        statusbar = new QStatusBar(About);
        statusbar->setObjectName("statusbar");
        About->setStatusBar(statusbar);

        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QMainWindow *About)
    {
        About->setWindowTitle(QCoreApplication::translate("About", "\345\205\263\344\272\216", nullptr));
        groupBox->setTitle(QCoreApplication::translate("About", "\345\274\200\345\217\221\344\277\241\346\201\257", nullptr));
        label->setText(QCoreApplication::translate("About", "\345\274\200\345\217\221\345\233\242\351\230\237", nullptr));
        label_2->setText(QString());
        label_3->setText(QCoreApplication::translate("About", "\345\274\200\345\217\221\346\210\220\345\221\230", nullptr));
        label_4->setText(QString());
        label_5->setText(QCoreApplication::translate("About", "\347\211\210\346\234\254\344\277\241\346\201\257", nullptr));
        label_6->setText(QCoreApplication::translate("About", "1.0.0", nullptr));
        label_7->setText(QCoreApplication::translate("About", "\346\234\200\345\220\216\346\233\264\346\226\260\346\227\245\346\234\237", nullptr));
        label_8->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
