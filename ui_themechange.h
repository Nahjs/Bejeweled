/********************************************************************************
** Form generated from reading UI file 'themechange.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THEMECHANGE_H
#define UI_THEMECHANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
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
    QLabel *label;
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

    void setupUi(QWidget *ThemeChange)
    {
        if (ThemeChange->objectName().isEmpty())
            ThemeChange->setObjectName("ThemeChange");
        ThemeChange->resize(757, 693);
        layoutWidget = new QWidget(ThemeChange);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(90, 310, 494, 80));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        ToneButton = new QPushButton(layoutWidget);
        ToneButton->setObjectName("ToneButton");

        verticalLayout->addWidget(ToneButton);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        TtwoButton = new QPushButton(layoutWidget);
        TtwoButton->setObjectName("TtwoButton");

        verticalLayout_2->addWidget(TtwoButton);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        TthreeButton = new QPushButton(layoutWidget);
        TthreeButton->setObjectName("TthreeButton");

        verticalLayout_3->addWidget(TthreeButton);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        verticalLayout_4->addWidget(label_4);

        TfourButton = new QPushButton(layoutWidget);
        TfourButton->setObjectName("TfourButton");

        verticalLayout_4->addWidget(TfourButton);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");

        verticalLayout_6->addWidget(label_5);

        TfiveButton = new QPushButton(layoutWidget);
        TfiveButton->setObjectName("TfiveButton");

        verticalLayout_6->addWidget(TfiveButton);


        horizontalLayout->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");

        verticalLayout_5->addWidget(label_6);

        TsixButton = new QPushButton(layoutWidget);
        TsixButton->setObjectName("TsixButton");

        verticalLayout_5->addWidget(TsixButton);


        horizontalLayout->addLayout(verticalLayout_5);


        retranslateUi(ThemeChange);

        QMetaObject::connectSlotsByName(ThemeChange);
    } // setupUi

    void retranslateUi(QWidget *ThemeChange)
    {
        ThemeChange->setWindowTitle(QCoreApplication::translate("ThemeChange", "ThemeChange", nullptr));
        label->setText(QCoreApplication::translate("ThemeChange", "TextLabel", nullptr));
        ToneButton->setText(QCoreApplication::translate("ThemeChange", "\344\270\273\351\242\2301", nullptr));
        label_2->setText(QCoreApplication::translate("ThemeChange", "TextLabel", nullptr));
        TtwoButton->setText(QCoreApplication::translate("ThemeChange", "\344\270\273\351\242\2302", nullptr));
        label_3->setText(QCoreApplication::translate("ThemeChange", "TextLabel", nullptr));
        TthreeButton->setText(QCoreApplication::translate("ThemeChange", "\344\270\273\351\242\2303", nullptr));
        label_4->setText(QCoreApplication::translate("ThemeChange", "TextLabel", nullptr));
        TfourButton->setText(QCoreApplication::translate("ThemeChange", "\344\270\273\351\242\2304", nullptr));
        label_5->setText(QCoreApplication::translate("ThemeChange", "TextLabel", nullptr));
        TfiveButton->setText(QCoreApplication::translate("ThemeChange", "\344\270\273\351\242\2305", nullptr));
        label_6->setText(QCoreApplication::translate("ThemeChange", "TextLabel", nullptr));
        TsixButton->setText(QCoreApplication::translate("ThemeChange", "\344\270\273\351\242\2306", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThemeChange: public Ui_ThemeChange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THEMECHANGE_H
