/********************************************************************************
** Form generated from reading UI file 'evoluteform.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVOLUTEFORM_H
#define UI_EVOLUTEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "evolute2dwidget.h"
#include "evolutetable.h"

QT_BEGIN_NAMESPACE

class Ui_evoluteform
{
public:
    QGridLayout *gridLayout;
    Evolute2dWidget *graphic_widget;
    QGroupBox *gridGroupBox;
    QGridLayout *gridLayout_2;
    QCheckBox *cBshowCircle;
    EvoluteTable *evolutetable;
    QSlider *sliderCircle;
    QCheckBox *cBshowEvolute;

    void setupUi(QWidget *evoluteform)
    {
        if (evoluteform->objectName().isEmpty())
            evoluteform->setObjectName(QString::fromUtf8("evoluteform"));
        evoluteform->resize(1064, 588);
        gridLayout = new QGridLayout(evoluteform);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphic_widget = new Evolute2dWidget(evoluteform);
        graphic_widget->setObjectName(QString::fromUtf8("graphic_widget"));

        gridLayout->addWidget(graphic_widget, 0, 1, 1, 1);

        gridGroupBox = new QGroupBox(evoluteform);
        gridGroupBox->setObjectName(QString::fromUtf8("gridGroupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gridGroupBox->sizePolicy().hasHeightForWidth());
        gridGroupBox->setSizePolicy(sizePolicy);
        gridGroupBox->setMinimumSize(QSize(150, 0));
        gridLayout_2 = new QGridLayout(gridGroupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        cBshowCircle = new QCheckBox(gridGroupBox);
        cBshowCircle->setObjectName(QString::fromUtf8("cBshowCircle"));

        gridLayout_2->addWidget(cBshowCircle, 2, 1, 1, 1);

        evolutetable = new EvoluteTable(gridGroupBox);
        if (evolutetable->columnCount() < 1)
            evolutetable->setColumnCount(1);
        if (evolutetable->rowCount() < 5)
            evolutetable->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        evolutetable->setVerticalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        evolutetable->setVerticalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        evolutetable->setVerticalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        evolutetable->setVerticalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        evolutetable->setVerticalHeaderItem(4, __qtablewidgetitem4);
        evolutetable->setObjectName(QString::fromUtf8("evolutetable"));
        evolutetable->setColumnCount(1);
        evolutetable->horizontalHeader()->setVisible(false);
        evolutetable->horizontalHeader()->setStretchLastSection(true);
        evolutetable->verticalHeader()->setVisible(false);

        gridLayout_2->addWidget(evolutetable, 0, 1, 1, 1);

        sliderCircle = new QSlider(gridGroupBox);
        sliderCircle->setObjectName(QString::fromUtf8("sliderCircle"));
        sliderCircle->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(sliderCircle, 3, 1, 1, 1);

        cBshowEvolute = new QCheckBox(gridGroupBox);
        cBshowEvolute->setObjectName(QString::fromUtf8("cBshowEvolute"));

        gridLayout_2->addWidget(cBshowEvolute, 1, 1, 1, 1);


        gridLayout->addWidget(gridGroupBox, 0, 2, 1, 1);


        retranslateUi(evoluteform);

        QMetaObject::connectSlotsByName(evoluteform);
    } // setupUi

    void retranslateUi(QWidget *evoluteform)
    {
        evoluteform->setWindowTitle(QCoreApplication::translate("evoluteform", "\320\255\320\262\320\276\320\273\321\216\321\202\320\260", nullptr));
        gridGroupBox->setTitle(QString());
        cBshowCircle->setText(QCoreApplication::translate("evoluteform", "\320\241\320\276\320\277\321\200\320\270\320\272\320\260\321\201\320\260\321\216\321\211\320\260\321\217\321\201\321\217 \320\276\320\272\321\200\321\203\320\266\320\275\320\276\321\201\321\202\321\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem = evolutetable->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("evoluteform", "x(t)", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = evolutetable->verticalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("evoluteform", "y(t)", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = evolutetable->verticalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("evoluteform", "step", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = evolutetable->verticalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("evoluteform", "from", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = evolutetable->verticalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("evoluteform", "to", nullptr));
        cBshowEvolute->setText(QCoreApplication::translate("evoluteform", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\215\320\262\320\276\320\273\321\216\321\202\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class evoluteform: public Ui_evoluteform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVOLUTEFORM_H
