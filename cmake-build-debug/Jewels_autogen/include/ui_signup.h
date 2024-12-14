/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Signup
{
public:
    QPushButton *pushButton_2;
    QPushButton *btn_return;
    QFrame *verificationFrame;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *lineEdit_username;
    QLabel *label_5;
    QLineEdit *lineEdit_passwd;
    QLabel *label_4;
    QLineEdit *lineEdit_surepasswd;
    QComboBox *verificationMethodBox;
    QLabel *label_verification;
    QLineEdit *lineEdit_verification;

    void setupUi(QWidget *Signup)
    {
        if (Signup->objectName().isEmpty())
            Signup->setObjectName("Signup");
        Signup->resize(562, 691);
        Signup->setStyleSheet(QString::fromUtf8(""));
        pushButton_2 = new QPushButton(Signup);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(300, 310, 91, 40));
        pushButton_2->setMinimumSize(QSize(0, 40));
        pushButton_2->setStyleSheet(QString::fromUtf8(""));
        btn_return = new QPushButton(Signup);
        btn_return->setObjectName("btn_return");
        btn_return->setGeometry(QRect(410, 620, 91, 40));
        btn_return->setMinimumSize(QSize(0, 40));
        btn_return->setStyleSheet(QString::fromUtf8(""));
        verificationFrame = new QFrame(Signup);
        verificationFrame->setObjectName("verificationFrame");
        verificationFrame->setGeometry(QRect(170, 430, 201, 191));
        verificationFrame->setFrameShape(QFrame::Box);
        verificationFrame->setFrameShadow(QFrame::Raised);
        gridLayoutWidget = new QWidget(Signup);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(150, 70, 251, 221));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(0, 41));
        label_3->setStyleSheet(QString::fromUtf8("font: 10pt \"Arial\";"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        lineEdit_username = new QLineEdit(gridLayoutWidget);
        lineEdit_username->setObjectName("lineEdit_username");
        lineEdit_username->setMinimumSize(QSize(0, 41));

        gridLayout->addWidget(lineEdit_username, 1, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(0, 41));
        label_5->setStyleSheet(QString::fromUtf8("font: 10pt \"Arial\";"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        lineEdit_passwd = new QLineEdit(gridLayoutWidget);
        lineEdit_passwd->setObjectName("lineEdit_passwd");
        lineEdit_passwd->setMinimumSize(QSize(0, 41));

        gridLayout->addWidget(lineEdit_passwd, 2, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(0, 41));
        label_4->setStyleSheet(QString::fromUtf8("font: 10pt \"Arial\";"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        lineEdit_surepasswd = new QLineEdit(gridLayoutWidget);
        lineEdit_surepasswd->setObjectName("lineEdit_surepasswd");
        lineEdit_surepasswd->setMinimumSize(QSize(0, 41));

        gridLayout->addWidget(lineEdit_surepasswd, 3, 1, 1, 1);

        verificationMethodBox = new QComboBox(Signup);
        verificationMethodBox->setObjectName("verificationMethodBox");
        verificationMethodBox->setGeometry(QRect(350, 370, 91, 31));
        label_verification = new QLabel(Signup);
        label_verification->setObjectName("label_verification");
        label_verification->setGeometry(QRect(100, 360, 65, 41));
        label_verification->setMinimumSize(QSize(0, 41));
        lineEdit_verification = new QLineEdit(Signup);
        lineEdit_verification->setObjectName("lineEdit_verification");
        lineEdit_verification->setGeometry(QRect(160, 360, 121, 41));
        lineEdit_verification->setMinimumSize(QSize(0, 41));

        retranslateUi(Signup);

        QMetaObject::connectSlotsByName(Signup);
    } // setupUi

    void retranslateUi(QWidget *Signup)
    {
        Signup->setWindowTitle(QCoreApplication::translate("Signup", "\346\263\250\345\206\214", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Signup", "\347\241\256\350\256\244or\351\252\214\350\257\201", nullptr));
        btn_return->setText(QCoreApplication::translate("Signup", "\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
        label_3->setText(QCoreApplication::translate("Signup", "\347\224\250 \346\210\267 \345\220\215\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("Signup", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("Signup", " \345\257\206    \347\240\201\357\274\232", nullptr));
        label_verification->setText(QCoreApplication::translate("Signup", "\351\252\214 \350\257\201 \347\240\201\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Signup: public Ui_Signup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
