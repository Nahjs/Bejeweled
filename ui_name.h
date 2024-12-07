/********************************************************************************
** Form generated from reading UI file 'name.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAME_H
#define UI_NAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Name
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit_name;
    QPushButton *btn_confirm;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Name)
    {
        if (Name->objectName().isEmpty())
            Name->setObjectName("Name");
        Name->resize(451, 211);
        Name->setMinimumSize(QSize(0, 0));
        Name->setMaximumSize(QSize(9999, 9999));
        centralwidget = new QWidget(Name);
        centralwidget->setObjectName("centralwidget");
        lineEdit_name = new QLineEdit(centralwidget);
        lineEdit_name->setObjectName("lineEdit_name");
        lineEdit_name->setGeometry(QRect(210, 40, 161, 41));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_name->sizePolicy().hasHeightForWidth());
        lineEdit_name->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamilies({QString::fromUtf8("\351\232\266\344\271\246")});
        font.setPointSize(18);
        lineEdit_name->setFont(font);
        lineEdit_name->setAlignment(Qt::AlignCenter);
        btn_confirm = new QPushButton(centralwidget);
        btn_confirm->setObjectName("btn_confirm");
        btn_confirm->setGeometry(QRect(140, 90, 101, 32));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217")});
        font1.setPointSize(18);
        btn_confirm->setFont(font1);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 40, 161, 41));
        label->setFont(font1);
        Name->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Name);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 451, 22));
        Name->setMenuBar(menubar);
        statusbar = new QStatusBar(Name);
        statusbar->setObjectName("statusbar");
        Name->setStatusBar(statusbar);

        retranslateUi(Name);

        QMetaObject::connectSlotsByName(Name);
    } // setupUi

    void retranslateUi(QMainWindow *Name)
    {
        Name->setWindowTitle(QCoreApplication::translate("Name", "\350\256\276\347\275\256\345\247\223\345\220\215", nullptr));
        lineEdit_name->setText(QString());
        btn_confirm->setText(QCoreApplication::translate("Name", "\347\241\256\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("Name", "\350\276\223\345\205\245\344\275\240\347\232\204\345\244\247\345\220\215\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Name: public Ui_Name {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAME_H
