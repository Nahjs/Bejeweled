/********************************************************************************
** Form generated from reading UI file 'cnamedlg.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CNAMEDLG_H
#define UI_CNAMEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CNameDlg
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_name;
    QPushButton *btn_confirm;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CNameDlg)
    {
        if (CNameDlg->objectName().isEmpty())
            CNameDlg->setObjectName("CNameDlg");
        CNameDlg->resize(632, 204);
        CNameDlg->setMinimumSize(QSize(632, 204));
        CNameDlg->setMaximumSize(QSize(632, 204));
        centralwidget = new QWidget(CNameDlg);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 60, 607, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("\351\232\266\344\271\246")});
        font.setPointSize(18);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        lineEdit_name = new QLineEdit(layoutWidget);
        lineEdit_name->setObjectName("lineEdit_name");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_name->sizePolicy().hasHeightForWidth());
        lineEdit_name->setSizePolicy(sizePolicy);
        lineEdit_name->setFont(font);
        lineEdit_name->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lineEdit_name);

        btn_confirm = new QPushButton(layoutWidget);
        btn_confirm->setObjectName("btn_confirm");
        btn_confirm->setFont(font);

        horizontalLayout->addWidget(btn_confirm);

        CNameDlg->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CNameDlg);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 632, 26));
        CNameDlg->setMenuBar(menubar);
        statusbar = new QStatusBar(CNameDlg);
        statusbar->setObjectName("statusbar");
        CNameDlg->setStatusBar(statusbar);

        retranslateUi(CNameDlg);

        QMetaObject::connectSlotsByName(CNameDlg);
    } // setupUi

    void retranslateUi(QMainWindow *CNameDlg)
    {
        CNameDlg->setWindowTitle(QCoreApplication::translate("CNameDlg", "\350\256\276\347\275\256\345\247\223\345\220\215", nullptr));
        label->setText(QCoreApplication::translate("CNameDlg", "\346\202\250\347\232\204\345\260\212\345\247\223\345\244\247\345\220\215\357\274\232", nullptr));
        lineEdit_name->setText(QCoreApplication::translate("CNameDlg", "\346\234\252\345\221\275\345\220\215", nullptr));
        btn_confirm->setText(QCoreApplication::translate("CNameDlg", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CNameDlg: public Ui_CNameDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CNAMEDLG_H
