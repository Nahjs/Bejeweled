/********************************************************************************
** Form generated from reading UI file 'setup.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUP_H
#define UI_SETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThemeChange
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label1;
    QPushButton *ToneButton;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QPushButton *TtwoButton;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QPushButton *TthreeButton;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QPushButton *TfourButton;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_5;
    QPushButton *TfiveButton;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_6;
    QPushButton *TsixButton;
    QPushButton *musicSetButton;
    QPushButton *sizeSetButton;
    QLabel *label;
    QLabel *label_7;
    QWidget *widget;
    QVBoxLayout *verticalLayout_7;
    QLineEdit *rowLineEdit;
    QLineEdit *colLineEdit;

    void setupUi(QWidget *ThemeChange)
    {
        if (ThemeChange->objectName().isEmpty())
            ThemeChange->setObjectName("ThemeChange");
        ThemeChange->resize(747, 341);
        layoutWidget = new QWidget(ThemeChange);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(110, 190, 494, 111));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label1 = new QLabel(layoutWidget);
        label1->setObjectName("label1");
        label1->setPixmap(QPixmap(QString::fromUtf8("C:/Users/17914/Desktop/\345\256\235\347\237\263\350\277\267\351\230\265/image/theme/a-theme/a1.png")));
        label1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label1);

        ToneButton = new QPushButton(layoutWidget);
        ToneButton->setObjectName("ToneButton");

        verticalLayout->addWidget(ToneButton);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        TtwoButton = new QPushButton(layoutWidget);
        TtwoButton->setObjectName("TtwoButton");

        verticalLayout_2->addWidget(TtwoButton);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);

        TthreeButton = new QPushButton(layoutWidget);
        TthreeButton->setObjectName("TthreeButton");

        verticalLayout_3->addWidget(TthreeButton);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_4);

        TfourButton = new QPushButton(layoutWidget);
        TfourButton->setObjectName("TfourButton");

        verticalLayout_4->addWidget(TfourButton);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_5);

        TfiveButton = new QPushButton(layoutWidget);
        TfiveButton->setObjectName("TfiveButton");

        verticalLayout_6->addWidget(TfiveButton);


        horizontalLayout->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_6);

        TsixButton = new QPushButton(layoutWidget);
        TsixButton->setObjectName("TsixButton");

        verticalLayout_5->addWidget(TsixButton);


        horizontalLayout->addLayout(verticalLayout_5);

        musicSetButton = new QPushButton(ThemeChange);
        musicSetButton->setObjectName("musicSetButton");
        musicSetButton->setGeometry(QRect(200, 100, 75, 24));
        sizeSetButton = new QPushButton(ThemeChange);
        sizeSetButton->setObjectName("sizeSetButton");
        sizeSetButton->setGeometry(QRect(370, 100, 75, 24));
        label = new QLabel(ThemeChange);
        label->setObjectName("label");
        label->setGeometry(QRect(460, 80, 31, 31));
        label_7 = new QLabel(ThemeChange);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(460, 110, 31, 31));
        widget = new QWidget(ThemeChange);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(490, 90, 134, 48));
        verticalLayout_7 = new QVBoxLayout(widget);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        rowLineEdit = new QLineEdit(widget);
        rowLineEdit->setObjectName("rowLineEdit");

        verticalLayout_7->addWidget(rowLineEdit);

        colLineEdit = new QLineEdit(widget);
        colLineEdit->setObjectName("colLineEdit");

        verticalLayout_7->addWidget(colLineEdit);


        retranslateUi(ThemeChange);

        QMetaObject::connectSlotsByName(ThemeChange);
    } // setupUi

    void retranslateUi(QWidget *ThemeChange)
    {
        ThemeChange->setWindowTitle(QCoreApplication::translate("ThemeChange", "ThemeChange", nullptr));
        label1->setText(QString());
        ToneButton->setText(QCoreApplication::translate("ThemeChange", "\344\270\273\351\242\2301", nullptr));
        label_2->setText(QString());
        TtwoButton->setText(QCoreApplication::translate("ThemeChange", "\344\270\273\351\242\2302", nullptr));
        label_3->setText(QString());
        TthreeButton->setText(QCoreApplication::translate("ThemeChange", "\344\270\273\351\242\2303", nullptr));
        label_4->setText(QString());
        TfourButton->setText(QCoreApplication::translate("ThemeChange", "\344\270\273\351\242\2304", nullptr));
        label_5->setText(QString());
        TfiveButton->setText(QCoreApplication::translate("ThemeChange", "\344\270\273\351\242\2305", nullptr));
        label_6->setText(QString());
        TsixButton->setText(QCoreApplication::translate("ThemeChange", "\344\270\273\351\242\2306", nullptr));
        musicSetButton->setText(QCoreApplication::translate("ThemeChange", "\351\237\263\351\207\217\345\244\247\345\260\217", nullptr));
        sizeSetButton->setText(QCoreApplication::translate("ThemeChange", "\347\225\214\351\235\242\345\244\247\345\260\217", nullptr));
        label->setText(QCoreApplication::translate("ThemeChange", "\350\241\214", nullptr));
        label_7->setText(QCoreApplication::translate("ThemeChange", "\345\210\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThemeChange: public Ui_ThemeChange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUP_H
