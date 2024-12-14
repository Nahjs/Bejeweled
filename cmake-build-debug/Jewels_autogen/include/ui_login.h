/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit_username;
    QLineEdit *lineEdit_password;
    QPushButton *btn_signin;
    QPushButton *btn_signup;
    QLabel *label_guestTip;
    QPushButton *btn_guest;

    void setupUi(QMainWindow *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(424, 520);
        QIcon icon;
        icon.addFile(QString::fromUtf8("res/images/a11.png"), QSize(), QIcon::Normal, QIcon::Off);
        Login->setWindowIcon(icon);
        Login->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"\n"
""));
        centralwidget = new QWidget(Login);
        centralwidget->setObjectName("centralwidget");
        lineEdit_username = new QLineEdit(centralwidget);
        lineEdit_username->setObjectName("lineEdit_username");
        lineEdit_username->setGeometry(QRect(90, 90, 231, 45));
        lineEdit_username->setMinimumSize(QSize(0, 45));
        lineEdit_username->setStyleSheet(QString::fromUtf8("background-color: rgb(247, 247, 247);\n"
"border:1px groove gray;border-radius:\n"
"7px;padding:2px 4px;\n"
"font: 10pt \"Candara\";"));
        lineEdit_password = new QLineEdit(centralwidget);
        lineEdit_password->setObjectName("lineEdit_password");
        lineEdit_password->setGeometry(QRect(90, 160, 231, 45));
        lineEdit_password->setMinimumSize(QSize(0, 45));
        lineEdit_password->setStyleSheet(QString::fromUtf8("background-color: rgb(247, 247, 247);\n"
"border:1px groove gray;border-radius:\n"
"7px;padding:2px 4px;\n"
"font: 10pt \"Candara\";"));
        lineEdit_password->setEchoMode(QLineEdit::Password);
        btn_signin = new QPushButton(centralwidget);
        btn_signin->setObjectName("btn_signin");
        btn_signin->setGeometry(QRect(100, 250, 71, 40));
        btn_signin->setMinimumSize(QSize(50, 40));
        btn_signin->setStyleSheet(QString::fromUtf8(""));
        btn_signup = new QPushButton(centralwidget);
        btn_signup->setObjectName("btn_signup");
        btn_signup->setGeometry(QRect(230, 250, 71, 40));
        btn_signup->setMinimumSize(QSize(50, 40));
        btn_signup->setStyleSheet(QString::fromUtf8(""));
        label_guestTip = new QLabel(centralwidget);
        label_guestTip->setObjectName("label_guestTip");
        label_guestTip->setGeometry(QRect(70, 340, 191, 111));
        label_guestTip->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        btn_guest = new QPushButton(centralwidget);
        btn_guest->setObjectName("btn_guest");
        btn_guest->setGeometry(QRect(300, 340, 71, 41));
        Login->setCentralWidget(centralwidget);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QMainWindow *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
        lineEdit_username->setPlaceholderText(QCoreApplication::translate("Login", "Username", nullptr));
        lineEdit_password->setPlaceholderText(QCoreApplication::translate("Login", "Password", nullptr));
        btn_signin->setText(QCoreApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
        btn_signup->setText(QCoreApplication::translate("Login", "\346\263\250\345\206\214", nullptr));
        btn_guest->setText(QCoreApplication::translate("Login", "\346\270\270\345\256\242\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
