/********************************************************************************
** Form generated from reading UI file 'cthemedlg.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CTHEMEDLG_H
#define UI_CTHEMEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CThemeDlg
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QRadioButton *radioButton_Theme_default;
    QRadioButton *radioButton_Theme_custom;
    QLabel *label;
    QLineEdit *lineEdit_path_backgroundimags;
    QLabel *label_2;
    QToolButton *toolButton_selsect_backgroundiamgs;
    QComboBox *comboBox_gemtype;
    QPushButton *btn_themeToSet;
    QPushButton *btn_theme_confirm;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CThemeDlg)
    {
        if (CThemeDlg->objectName().isEmpty())
            CThemeDlg->setObjectName("CThemeDlg");
        CThemeDlg->resize(611, 358);
        CThemeDlg->setMinimumSize(QSize(611, 358));
        CThemeDlg->setMaximumSize(QSize(611, 358));
        centralwidget = new QWidget(CThemeDlg);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(60, 20, 491, 191));
        groupBox->setStyleSheet(QString::fromUtf8("font: 75 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        radioButton_Theme_default = new QRadioButton(groupBox);
        radioButton_Theme_default->setObjectName("radioButton_Theme_default");
        radioButton_Theme_default->setGeometry(QRect(140, 30, 81, 19));
        radioButton_Theme_default->setChecked(true);
        radioButton_Theme_default->setAutoRepeat(false);
        radioButton_Theme_custom = new QRadioButton(groupBox);
        radioButton_Theme_custom->setObjectName("radioButton_Theme_custom");
        radioButton_Theme_custom->setGeometry(QRect(280, 30, 81, 19));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 70, 72, 31));
        lineEdit_path_backgroundimags = new QLineEdit(groupBox);
        lineEdit_path_backgroundimags->setObjectName("lineEdit_path_backgroundimags");
        lineEdit_path_backgroundimags->setGeometry(QRect(92, 70, 311, 31));
        lineEdit_path_backgroundimags->setReadOnly(true);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 130, 72, 31));
        toolButton_selsect_backgroundiamgs = new QToolButton(groupBox);
        toolButton_selsect_backgroundiamgs->setObjectName("toolButton_selsect_backgroundiamgs");
        toolButton_selsect_backgroundiamgs->setGeometry(QRect(420, 70, 47, 31));
        toolButton_selsect_backgroundiamgs->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);"));
        comboBox_gemtype = new QComboBox(groupBox);
        comboBox_gemtype->setObjectName("comboBox_gemtype");
        comboBox_gemtype->setGeometry(QRect(90, 130, 311, 31));
        btn_themeToSet = new QPushButton(centralwidget);
        btn_themeToSet->setObjectName("btn_themeToSet");
        btn_themeToSet->setGeometry(QRect(370, 240, 141, 51));
        btn_themeToSet->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_theme_confirm = new QPushButton(centralwidget);
        btn_theme_confirm->setObjectName("btn_theme_confirm");
        btn_theme_confirm->setGeometry(QRect(90, 240, 141, 51));
        btn_theme_confirm->setStyleSheet(QString::fromUtf8("border-image: url(:/new/picture/pushbotton_background.png);\n"
"font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        CThemeDlg->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CThemeDlg);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 611, 26));
        CThemeDlg->setMenuBar(menubar);
        statusbar = new QStatusBar(CThemeDlg);
        statusbar->setObjectName("statusbar");
        CThemeDlg->setStatusBar(statusbar);

        retranslateUi(CThemeDlg);

        QMetaObject::connectSlotsByName(CThemeDlg);
    } // setupUi

    void retranslateUi(QMainWindow *CThemeDlg)
    {
        CThemeDlg->setWindowTitle(QCoreApplication::translate("CThemeDlg", "\344\270\273\351\242\230\350\256\276\347\275\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CThemeDlg", "\350\256\276\347\275\256\344\270\273\351\242\230", nullptr));
        radioButton_Theme_default->setText(QCoreApplication::translate("CThemeDlg", "\351\273\230\350\256\244", nullptr));
        radioButton_Theme_custom->setText(QCoreApplication::translate("CThemeDlg", "\350\207\252\345\256\232\344\271\211", nullptr));
        label->setText(QCoreApplication::translate("CThemeDlg", "\350\203\214\346\231\257\345\233\276\347\211\207", nullptr));
        lineEdit_path_backgroundimags->setText(QString());
        label_2->setText(QCoreApplication::translate("CThemeDlg", "\345\256\235\347\237\263\345\233\276\347\211\207", nullptr));
        toolButton_selsect_backgroundiamgs->setText(QCoreApplication::translate("CThemeDlg", "...", nullptr));
        btn_themeToSet->setText(QCoreApplication::translate("CThemeDlg", "\350\277\224\345\233\236\350\256\276\347\275\256", nullptr));
        btn_theme_confirm->setText(QCoreApplication::translate("CThemeDlg", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CThemeDlg: public Ui_CThemeDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CTHEMEDLG_H
