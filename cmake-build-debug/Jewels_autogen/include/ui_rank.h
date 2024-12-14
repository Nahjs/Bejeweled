/********************************************************************************
** Form generated from reading UI file 'rank.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANK_H
#define UI_RANK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Rank
{
public:
    QAction *actionClear;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *timeLabel;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_27;
    QLabel *label_3;
    QLabel *label_12;
    QLabel *label_22;
    QLabel *label_13;
    QLabel *label_32;
    QLabel *label_28;
    QLabel *label_19;
    QLabel *label_10;
    QLabel *label;
    QLabel *label_1;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_18;
    QLabel *label_15;
    QLabel *label_21;
    QLabel *label_30;
    QLabel *label_25;
    QLabel *label_16;
    QLabel *label_24;
    QMenuBar *menubar;

    void setupUi(QMainWindow *Rank)
    {
        if (Rank->objectName().isEmpty())
            Rank->setObjectName("Rank");
        Rank->resize(441, 549);
        Rank->setMinimumSize(QSize(0, 0));
        Rank->setMaximumSize(QSize(9999, 9999));
        Rank->setStyleSheet(QString::fromUtf8(""));
        actionClear = new QAction(Rank);
        actionClear->setObjectName("actionClear");
        centralwidget = new QWidget(Rank);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        timeLabel = new QLabel(centralwidget);
        timeLabel->setObjectName("timeLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("\351\232\266\344\271\246")});
        font.setPointSize(12);
        timeLabel->setFont(font);
        timeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(timeLabel);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(20, 10, 20, 10);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\351\232\266\344\271\246")});
        font1.setPointSize(18);
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 2, 1, 1, 1);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setFont(font1);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_9, 3, 1, 1, 1);

        label_27 = new QLabel(centralwidget);
        label_27->setObjectName("label_27");
        sizePolicy.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy);
        label_27->setFont(font1);
        label_27->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_27, 9, 1, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 1, 1, 1, 1);

        label_12 = new QLabel(centralwidget);
        label_12->setObjectName("label_12");
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setFont(font1);
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_12, 4, 1, 1, 1);

        label_22 = new QLabel(centralwidget);
        label_22->setObjectName("label_22");
        sizePolicy.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy);
        label_22->setFont(font1);
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_22, 8, 0, 1, 1);

        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);
        label_13->setFont(font1);
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_13, 5, 0, 1, 1);

        label_32 = new QLabel(centralwidget);
        label_32->setObjectName("label_32");
        label_32->setFont(font1);
        label_32->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_32, 0, 1, 1, 1);

        label_28 = new QLabel(centralwidget);
        label_28->setObjectName("label_28");
        sizePolicy.setHeightForWidth(label_28->sizePolicy().hasHeightForWidth());
        label_28->setSizePolicy(sizePolicy);
        label_28->setFont(font1);
        label_28->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_28, 10, 0, 1, 1);

        label_19 = new QLabel(centralwidget);
        label_19->setObjectName("label_19");
        sizePolicy.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy);
        label_19->setFont(font1);
        label_19->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_19, 7, 0, 1, 1);

        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        label_10->setFont(font1);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_10, 4, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_1 = new QLabel(centralwidget);
        label_1->setObjectName("label_1");
        sizePolicy.setHeightForWidth(label_1->sizePolicy().hasHeightForWidth());
        label_1->setSizePolicy(sizePolicy);
        label_1->setFont(font1);
        label_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_1, 1, 0, 1, 1);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_18 = new QLabel(centralwidget);
        label_18->setObjectName("label_18");
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        label_18->setFont(font1);
        label_18->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_18, 6, 1, 1, 1);

        label_15 = new QLabel(centralwidget);
        label_15->setObjectName("label_15");
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);
        label_15->setFont(font1);
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_15, 5, 1, 1, 1);

        label_21 = new QLabel(centralwidget);
        label_21->setObjectName("label_21");
        sizePolicy.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy);
        label_21->setFont(font1);
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_21, 7, 1, 1, 1);

        label_30 = new QLabel(centralwidget);
        label_30->setObjectName("label_30");
        sizePolicy.setHeightForWidth(label_30->sizePolicy().hasHeightForWidth());
        label_30->setSizePolicy(sizePolicy);
        label_30->setFont(font1);
        label_30->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_30, 10, 1, 1, 1);

        label_25 = new QLabel(centralwidget);
        label_25->setObjectName("label_25");
        sizePolicy.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy);
        label_25->setFont(font1);
        label_25->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_25, 9, 0, 1, 1);

        label_16 = new QLabel(centralwidget);
        label_16->setObjectName("label_16");
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);
        label_16->setFont(font1);
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_16, 6, 0, 1, 1);

        label_24 = new QLabel(centralwidget);
        label_24->setObjectName("label_24");
        sizePolicy.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy);
        label_24->setFont(font1);
        label_24->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_24, 8, 1, 1, 1);

        gridLayout->setColumnStretch(0, 4);
        gridLayout->setColumnStretch(1, 4);

        verticalLayout->addLayout(gridLayout);

        Rank->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Rank);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 441, 22));
        Rank->setMenuBar(menubar);

        retranslateUi(Rank);

        QMetaObject::connectSlotsByName(Rank);
    } // setupUi

    void retranslateUi(QMainWindow *Rank)
    {
        Rank->setWindowTitle(QCoreApplication::translate("Rank", "\345\256\236\346\227\266\346\216\222\350\241\214\346\246\234", nullptr));
        actionClear->setText(QCoreApplication::translate("Rank", "Clear", nullptr));
        label_6->setText(QString());
        label_9->setText(QString());
        label_27->setText(QString());
        label_3->setText(QString());
        label_12->setText(QString());
        label_22->setText(QString());
        label_13->setText(QString());
        label_32->setText(QCoreApplication::translate("Rank", "\345\276\227\345\210\206", nullptr));
        label_28->setText(QString());
        label_19->setText(QString());
        label_10->setText(QString());
        label->setText(QCoreApplication::translate("Rank", "\345\247\223\345\220\215", nullptr));
        label_1->setText(QString());
        label_7->setText(QString());
        label_4->setText(QString());
        label_18->setText(QString());
        label_15->setText(QString());
        label_21->setText(QString());
        label_30->setText(QString());
        label_25->setText(QString());
        label_16->setText(QString());
        label_24->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Rank: public Ui_Rank {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANK_H
