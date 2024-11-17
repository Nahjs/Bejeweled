/********************************************************************************
** Form generated from reading UI file 'chelpdlg.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHELPDLG_H
#define UI_CHELPDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CHelpDlg
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CHelpDlg)
    {
        if (CHelpDlg->objectName().isEmpty())
            CHelpDlg->setObjectName("CHelpDlg");
        CHelpDlg->resize(413, 537);
        CHelpDlg->setMinimumSize(QSize(413, 537));
        CHelpDlg->setMaximumSize(QSize(413, 537));
        CHelpDlg->setStyleSheet(QString::fromUtf8("background-image: url(:/new/picture/background3.jpg);"));
        centralwidget = new QWidget(CHelpDlg);
        centralwidget->setObjectName("centralwidget");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(20, 20, 371, 491));
        textEdit->setReadOnly(true);
        textEdit->setOverwriteMode(false);
        CHelpDlg->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CHelpDlg);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 413, 26));
        CHelpDlg->setMenuBar(menubar);
        statusbar = new QStatusBar(CHelpDlg);
        statusbar->setObjectName("statusbar");
        CHelpDlg->setStatusBar(statusbar);

        retranslateUi(CHelpDlg);

        QMetaObject::connectSlotsByName(CHelpDlg);
    } // setupUi

    void retranslateUi(QMainWindow *CHelpDlg)
    {
        CHelpDlg->setWindowTitle(QCoreApplication::translate("CHelpDlg", "\345\270\256\345\212\251", nullptr));
        textEdit->setHtml(QCoreApplication::translate("CHelpDlg", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:600; color:#00aa00;\">\346\270\270\346\210\217\350\247\204\345\210\231\357\274\232</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt; font-weight:600; color:#00aa00;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600; color:#ff007f;\">1\343\200\201\344\272\222\346\215\242"
                        "</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt; font-weight:600; color:#5500ff;\">\347\216\251\345\256\266\351\200\211\344\270\255\347\233\270\351\202\273\357\274\210\346\250\252\343\200\201\347\253\226\357\274\211\347\232\204\344\270\244\344\270\252\345\256\235\347\237\263\344\275\215\347\275\256\345\217\221\347\224\237\344\272\222\346\215\242\357\274\214\345\246\202\346\236\234\344\272\222\346\215\242\346\210\220\345\212\237\345\210\231\346\266\210\345\216\273\345\256\235\347\237\263\357\274\214\345\220\246\345\210\231\345\217\226\346\266\210\344\275\215\347\275\256\344\272\222\346\215\242\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600; color:#5500ff;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-"
                        "block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600; color:#ff007f;\">2\343\200\201\346\266\210\345\216\273</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt; font-weight:600; color:#5500ff;\">\347\216\251\345\256\266\351\200\211\346\213\251\344\270\244\344\270\252\345\256\235\347\237\263\350\277\233\350\241\214\344\275\215\347\275\256\344\272\222\346\215\242\357\274\214\344\272\222\346\215\242\345\220\216\345\246\202\346\236\234\346\250\252\346\216\222\346\210\226\347\253\226\346\216\222\347\232\204\346\234\2113\344\270\252\346\210\2263\344\270\252\344\273\245\344\270\212\347\232\204\347\233\270\345\220\214\345\256\235\347\237\263 \357\274\214\345\210\231\346\266\210\345\216\273\350\277\231\344\270\252\347\233\270\345\220\214\345\256\235\347\237\263\357\274\214\345\246\202\346\236\234\344\272\222\346\215\242\345\220\216\346\262\241\346\234\211\345\217\257\344\273\245"
                        "\346\266\210\345\216\273\347\232\204\345\256\235\347\237\263\357\274\214\345\210\231\351\200\211\344\270\255\347\232\204\344\270\244\344\270\252\345\256\235\347\237\263\346\215\242\345\233\236\345\216\237\346\235\245\347\232\204\344\275\215\347\275\256\343\200\202\346\266\210\345\216\273\345\220\216\347\232\204\347\251\272\344\275\215\347\224\261\344\270\212\351\235\242\347\232\204\345\256\235\347\237\263\346\216\211\344\270\213\346\235\245\350\241\245\351\275\220\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600; color:#5500ff;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600; color:#ff007f;\">3\343\200\201\350\277\236\351\224\201</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-inden"
                        "t:0; text-indent:0px;\"><span style=\" font-size:11pt; font-weight:600; color:#5500ff;\">\347\216\251\345\256\266\346\266\210\345\216\273\345\256\235\347\237\263\345\220\216\357\274\214\344\270\212\351\235\242\347\232\204\345\256\235\347\237\263\346\216\211\344\270\213\346\235\245\350\241\245\351\275\220\347\251\272\344\275\215\343\200\202\345\246\202\346\236\234\350\277\231\346\227\266\346\270\270\346\210\217\346\261\240\344\270\255\346\234\211\350\277\236\347\273\255\346\221\206\346\224\276\357\274\210\346\250\252\343\200\201\347\253\226\357\274\211\347\232\2043\344\270\252\346\210\2263\344\270\252\344\273\245\344\270\212\347\233\270\345\220\214\345\256\235\347\237\263\357\274\214\345\210\231\345\217\257\344\273\245\346\266\210\345\216\273\350\277\231\344\272\233\345\256\235\347\237\263\357\274\214\350\277\231\345\260\261\346\230\257\344\270\200\346\254\241\350\277\236\351\224\201\343\200\202\347\251\272\344\275\215\350\242\253\346\226\260\347\232\204\345\256\235\347\237\263\345\241\253\345\205\205\357\274\214"
                        "\345\217\210\345\217\257\344\273\245\350\277\233\350\241\214\344\270\213\344\270\200\346\254\241\350\277\236\351\224\201\343\200\202</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CHelpDlg: public Ui_CHelpDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHELPDLG_H
